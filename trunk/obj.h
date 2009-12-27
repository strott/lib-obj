/*
 *  obj.h
 *  libObj
 *
 *  Created by claudio beatrice on 11/13/09.
 *  Copyright 2009 claudio beatrice. All rights reserved.
 *
 */
#include "objt.h"

#define OBJ_ELEMENT_NAME_MAX_LENGTH 10
#define OBJ_ELEMENT_LIST_MAX_LENGTH 100

#define OBJ_ELEMENT_FACE             "f"
#define OBJ_ELEMENT_GEOMETRIC_VERTEX "v"
#define OBJ_ELEMENT_VERTEX_NORMAL    "vn"
//#define OBJ_ELEMENT_TEXTURE_VERTEX "vt"

#define OBJ_ELEMENTS_COUNT 3

typedef struct globals_s {
    FILE *fp;
} global;

typedef struct obj_s {
    face *f;
    int f_count, f_size;
    
    geometric_vertex *v;
    int v_count, v_size;

    vertex_normal *vn;
    int vn_count, vn_size;

    //    texture_vertex *vt;
    //    int vt_count, vt_size;    
} obj;

// Function to be used for loading the file
obj obj_process_file(const char *, const char **);

// Data structures helpers
int  _obj_init_elements(const char **, const char **);
void _obj_init_data_struct(obj *);
void _obj_update_data_struct(obj *, const char *);
void _obj_optimize_data_struct(obj *);

// File handling helpers
void _obj_open_file(const char *);
void _obj_close_file(void);

// Data reading helpers
int _obj_read_face(obj *);
int _obj_read_face_vertex(obj *, int);
int _obj_read_geometric_vertex(obj *);
int _obj_read_vertex_normal(obj *);
//int _obj_read_texture_vertex();
