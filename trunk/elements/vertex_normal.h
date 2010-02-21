/*
 *  vertex_normal.h
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "base.h"
#define OBJ_ELEMENT_VERTEX_NORMAL "vn"

/**
 * vertex normals (vn)
 *
 * Polygonal and free-form geometry statement.
 */
typedef struct vertex_normal_s {
    float i, j, k;
} vertex_normal;

int _vertex_normal_read(FILE *, vertex_normal *);