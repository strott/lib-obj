/*
 *  obj.h
 *  libObj
 *
 *  Created by claudio beatrice on 11/13/09.
 *  Copyright 2009 claudio beatrice. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elements.h"

// prototype declarations for private functions.
#define _PROTOTYPE(function, params) function params
#define PRIVATE static

typedef struct obj_s {
    #ifdef OBJ_ELEMENT_FACE
        face *f;
        int f_count, f_size;
        int (*face_read) (FILE *, struct obj_s *);
    #endif
        
    #ifdef OBJ_ELEMENT_GEOMETRIC_VERTEX
        geometric_vertex *v;
        int v_count, v_size;
        int (*geometric_vertex_read) (FILE *, struct obj_s *);
    #endif

    #ifdef OBJ_ELEMENT_VERTEX_NORMAL
        vertex_normal *vn;
        int vn_count, vn_size;
        int (*vertex_normal_read) (FILE *, struct obj_s *);
    #endif
} obj;

// Function to be used for loading the file
obj obj_process_file(const char *, const char **);

// Data structures helpers
PRIVATE _PROTOTYPE(void obj_init, (obj *));
PRIVATE _PROTOTYPE(void obj_realloc, (obj *, const char *));
PRIVATE _PROTOTYPE(void obj_optimize, (obj *));

// File handling private functions
PRIVATE _PROTOTYPE(FILE * obj_file_open, (const char *));
PRIVATE _PROTOTYPE(void obj_file_close, (FILE *));
