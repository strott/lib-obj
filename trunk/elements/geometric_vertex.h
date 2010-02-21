/*
 *  geometric_vertex.h
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "base.h"
#define OBJ_ELEMENT_GEOMETRIC_VERTEX "v"

/**
 * geometric vertices (v)
 *
 * Polygonal and free-form geometry statement.
 */
typedef struct geometric_vertex_s {
    float x, y, z, w;
} geometric_vertex;

int _geometric_vertex_read(FILE *, geometric_vertex *);