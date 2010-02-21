/*
 *  face.h
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "base.h"
#define OBJ_ELEMENT_FACE "f"

/**
 * face vertex
 */
typedef struct face_vertex_s {
    int v, vt, vn;
} face_vertex;

/**
 * face (f)
 *
 * Polygonal geometry statement.
 */
typedef struct face_s {
    face_vertex fv[3];
} face;

int _face_read(FILE *, face *);
int _face_vertex_read(FILE *, face_vertex *, int);