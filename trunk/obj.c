/*
 *  obj.c
 *  libObj
 *
 *  Created by claudio beatrice on 11/13/09.
 *  Copyright 2009 claudio beatrice. All rights reserved.
 *
 */
#include "obj.h"

obj obj_process_file(const char *fname, const char **elements_requested) {
    obj O;
    FILE *fp = NULL;
    int buff_size = 80;
    char *buff = calloc(buff_size, sizeof(char)), 
         item[OBJ_ELEMENT_NAME_MAX_LENGTH];

    fp = obj_file_open(fname);
    obj_init(&O);

    // until I haven't finished to read the file
    while (!feof(fp)) {
        // I read a line from the file. If it exceeds OBJ_ELEMENT_NAME_MAX_LENGTH allocate some more memory
        while (fgets(buff, OBJ_ELEMENT_NAME_MAX_LENGTH, fp)) {
            if (strlen(buff) >= buff_size) {
                buff_size *= 2;
                realloc(buff, sizeof(char) * buff_size);
            }
        }
        
        //TODO: scan for item's name

        if (item != NULL) {
            #ifdef OBJ_ELEMENT_FACE
                if (strncmp(OBJ_ELEMENT_FACE, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                    face f;
                    if (_face_read(fp, &f)) {
                        // TODO: store face into obj and 
                        // check if there's still space for further storing
                    }
                    continue;
                }
            #endif

            #ifdef OBJ_ELEMENT_GEOMETRIC_VERTEX
                if (strncmp(OBJ_ELEMENT_GEOMETRIC_VERTEX, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                    geometric_vertex g;
                    if (_geometric_vertex_read(fp, &g)) {
                        // TODO: store geometric_vertex into obj and 
                        // check if there's still space for further storing, 
                        // check following commented piece of old code as reference  
                        /*
                         int _geometric_vertex_read(FILE *fp, obj *O) {
                             if (++O->v_count >= O->v_size) {
                             _obj_update_data_struct(O, OBJ_ELEMENT_GEOMETRIC_VERTEX);
                             }
                             if (fscanf(fp, "%f%f%f", &O->v[O->v_count].x, &O->v[O->v_count].y, &O->v[O->v_count].z) != 3) {
                                 return 0;
                             }
                             return 1;
                         }
                        */
                    }
                    continue;
                }
            #endif

            #ifdef OBJ_ELEMENT_VERTEX_NORMAL
                if (strncmp(OBJ_ELEMENT_VERTEX_NORMAL, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                    vertex_normal vn;
                    if (_vertex_normal_read(fp, &vn)) {
                        // TODO: store vertex_normal into obj and 
                        // check if there's still space for further storing
                    }
                    continue;
                }
            #endif
        }
    }

    obj_optimize(&O);
    obj_file_close(fp);
    return O;
}

/**
 * Perform memory allocation for object's supported elements
 */
void obj_init(obj *O) {
    #ifdef OBJ_ELEMENT_FACE
        O->f_count = 0;
        O->f_size  = OBJ_ELEMENT_LIST_MAX_LENGTH;
        O->f       = calloc(O->f_size, sizeof(face));
    #endif

    #ifdef OBJ_ELEMENT_GEOMETRIC_VERTEX
        O->v_count = 0;
        O->v_size  = OBJ_ELEMENT_LIST_MAX_LENGTH;
        O->v       = calloc(O->v_size, sizeof(geometric_vertex));
    #endif

    #ifdef OBJ_ELEMENT_VERTEX_NORMAL
        O->vn_count = 0;
        O->vn_size  = OBJ_ELEMENT_LIST_MAX_LENGTH;
        O->vn       = calloc(O->vn_size, sizeof(vertex_normal));
    #endif
}

/**
 * Perform memory reallocation for object's supported elements
 * 
 * This function is called when more space is required for storing data read from given file 
 */
void obj_realloc(obj *O, const char *name) {
    #ifdef OBJ_ELEMENT_FACE
        if (strncmp(OBJ_ELEMENT_FACE, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
            O->f_size *= 2;
            O->f = realloc(O->f, O->f_size * sizeof(face));
        }
    #endif

    #ifdef OBJ_ELEMENT_GEOMETRIC_VERTEX
        if (strncmp(OBJ_ELEMENT_GEOMETRIC_VERTEX, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
            O->v_size *= 2;
            O->v = realloc(O->v, O->v_size * sizeof(geometric_vertex));
        }
    #endif

    #ifdef OBJ_ELEMENT_VERTEX_NORMAL
        if (strncmp(OBJ_ELEMENT_VERTEX_NORMAL, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
            O->vn_size *= 2;
            O->vn = realloc(O->vn, O->vn_size * sizeof(vertex_normal));
        }
    #endif
}

/**
 * Perform memory optimization on object's supported elements
 * 
 * This function is called when the data loading is finished to deallocate unused memory 
 */
void obj_optimize(obj *O) {
    #ifdef OBJ_ELEMENT_FACE
        O->f_size = O->f_count;
        O->f = realloc(O->f, O->f_size * sizeof(face));
    #endif

    #ifdef OBJ_ELEMENT_GEOMETRIC_VERTEX
        O->v_size = O->v_count;
        O->v = realloc(O->v, O->v_size * sizeof(geometric_vertex));
    #endif

    #ifdef OBJ_ELEMENT_VERTEX_NORMAL
        O->vn_size = O->vn_count;
        O->vn = realloc(O->vn, O->vn_size * sizeof(vertex_normal));
    #endif
}

/**
 * Open a file and perform basic check
 */
FILE* obj_file_open(const char *fname) {
    FILE *fp = NULL;
    if (!(fp = fopen(fname, "r"))) {
        printf("Error opening file '%s'", fname);
        exit(1);
    }
    return fp;
}

/**
 * Close a file
 */
void obj_file_close(FILE *fp) {
    if (fclose(fp) == EOF) {
        printf("Error closing file");
        exit(ferror(fp));    
    }
}
