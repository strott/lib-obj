/*
 *  obj.c
 *  libObj
 *
 *  Created by claudio beatrice on 11/13/09.
 *  Copyright 2009 claudio beatrice. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj.h"

obj obj_process_file(const char *fname, const char **elements_requested) {
    obj O;
    FILE *fp = NULL;
    char *buff = NULL, *item = NULL;
    const char **elements_enabled = NULL;
    int buff_size = 80;

    fp = _obj_open_file(fname);
    _obj_init_data_struct(&O);
    _obj_init_elements(elements_enabled, elements_requested);

//    qsort(elements_enabled, 
//          OBJ_ELEMENTS_COUNT, 
//          OBJ_ELEMENT_NAME_MAX_LENGTH * sizeof(char), 
//          (int(*)(const void*, const void*)) strcmp);

    while (!feof(fp)) {
        while (fgets(buff, OBJ_ELEMENT_NAME_MAX_LENGTH, fp)) {
            realloc(buff, sizeof(char) * buff_size);    
        }
        fscanf(fp, "%10c", buff);
        item = (char*) bsearch (buff, elements_enabled, 
                                OBJ_ELEMENTS_COUNT, 
                                OBJ_ELEMENT_NAME_MAX_LENGTH * sizeof(char), 
                                (int(*)(const void*, const void*)) strcmp);

        if (item != NULL) {
            if (strncmp(OBJ_ELEMENT_FACE, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                _obj_read_face(fp, &O);
                continue;
            }
            if (strncmp(OBJ_ELEMENT_GEOMETRIC_VERTEX, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                _obj_read_geometric_vertex(fp, &O);
                continue;
            }
            if (strncmp(OBJ_ELEMENT_VERTEX_NORMAL, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
                _obj_read_vertex_normal(fp, &O);
                continue;
            }
//            if (strncmp(OBJ_ELEMENT_TEXTURE_VERTEX, item, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
//                _obj_read_texture_vertex(&O);
//                continue;
//            }
        }
    }

    _obj_optimize_data_struct(&O);
    _obj_close_file(fp);
    return O;
}

int _obj_init_elements(const char **elements_enabled, const char **elements_requested) {
    int i, j = 0;
    
    for (i = 0; i < OBJ_ELEMENTS_COUNT; j += elements_enabled[i++] ? 1 : 0) {
        elements_enabled[i] = (char*) bsearch (elements_enabled[i], elements_requested, 
                                               OBJ_ELEMENTS_COUNT, 
                                               OBJ_ELEMENT_NAME_MAX_LENGTH * sizeof(char), 
                                               (int(*)(const void*, const void*)) strcmp);
    }
    
    return j;
}

void _obj_init_data_struct(obj *O) {
    O->f_count = 0;
    O->f_size  = 100;
    O->f  = calloc(O->f_size, sizeof(face));
    
    O->v_count = 0;
    O->v_size  = 100;
    O->v       = calloc(O->v_size, sizeof(geometric_vertex));
    
    O->vn_count = 0;
    O->vn_size  = 100;
    O->vn = calloc(O->vn_size, sizeof(vertex_normal));
    
//    O->vt_count = 0;
//    O->vt_size  = 100;
//    O->vt = calloc(O->vt_size, sizeof(texture_vertex));
}

void _obj_update_data_struct(obj *O, const char *name) {
    if (strncmp(OBJ_ELEMENT_FACE, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
        O->f_size *= 2;
        O->f = realloc(O->f, O->f_size * sizeof(face));
    }
    
    if (strncmp(OBJ_ELEMENT_GEOMETRIC_VERTEX, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
        O->v_size *= 2;
        O->v = realloc(O->v, O->v_size * sizeof(geometric_vertex));
    }

    if (strncmp(OBJ_ELEMENT_VERTEX_NORMAL, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
        O->vn_size *= 2;
        O->vn = realloc(O->vn, O->vn_size * sizeof(vertex_normal));
    }
    
//    if (strncmp(OBJ_ELEMENT_TEXTURE_VERTEX, name, OBJ_ELEMENT_NAME_MAX_LENGTH) == 0) {
//      O->vt_size *= 2;
//      O->vt = realloc(O->vt, O->vt_size * sizeof(texture_vertex));
//    }
}

void _obj_optimize_data_struct(obj *O) {
    O->f_size = O->f_count;
    O->f = realloc(O->f, O->f_size * sizeof(face));
    
    O->v_size = O->v_count;
    O->v = realloc(O->v, O->v_size * sizeof(geometric_vertex));

    O->vn_size = O->vn_count;
    O->vn = realloc(O->vn, O->vn_size * sizeof(vertex_normal));

//    O->vt_size = O->vt_count;
//    O->vt = realloc(O->vt, O->vt_size * sizeof(texture_vertex));
}

FILE* _obj_open_file(const char *fname) {
    FILE *fp = NULL;
    if (!(fp = fopen(fname, "r"))) {
        exit(1);
    }
    return fp;
}

void _obj_close_file(FILE *fp) {
    if (fclose(fp) == EOF) {
        exit(ferror(fp));    
    }
}

int _obj_read_face(FILE *fp, obj *O) {
    if (++O->f_count >= O->f_size) {
        _obj_update_data_struct(O, OBJ_ELEMENT_FACE);
    }
    for (int i = 0; i < 3; ++i) {
        if (!_obj_read_face_vertex(fp, O, i)) {
            return 0;
        }
    }
    return 1;
}

int _obj_read_face_vertex(FILE *fp, obj *O, int i) {
    fscanf(fp, "%d", &(O->f[O->f_count].fv[i].v));
    if (fscanf(fp, "/") == 1) {
        fscanf(fp, "%d", &(O->f[O->f_count].fv[i].vt));
        fscanf(fp, "/%d", &(O->f[O->f_count].fv[i].vn));
    }
    return 1;
}

int _obj_read_geometric_vertex(FILE *fp, obj *O) {
    if (++O->v_count >= O->v_size) {
        _obj_update_data_struct(O, OBJ_ELEMENT_GEOMETRIC_VERTEX);
    }
    if (fscanf(fp, "%f%f%f", &O->v[O->v_count].x, &O->v[O->v_count].y, &O->v[O->v_count].z) != 3) {
        return 0;
    }
    return 1;
}

int _obj_read_vertex_normal(FILE *fp, obj *O) {
    if (++O->vn_count >= O->vn_size) {
        _obj_update_data_struct(O, OBJ_ELEMENT_VERTEX_NORMAL);
    }
    if (fscanf(fp, "%f%f%f", &O->vn[O->vn_count].i, &O->vn[O->vn_count].j, &O->vn[O->vn_count].k) != 3) {
        return 0;
    }
    return 1;
}

//int _obj_read_texture_vertex() {
//    //TODO implement
//    return 1;
//}
