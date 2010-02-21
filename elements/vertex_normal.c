/*
 *  vertex_normal.c
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "vertex_normal.h"

int _vertex_normal_read(FILE *fp, vertex_normal *v) {
    if (fscanf(fp, "%f%f%f", &v->i, &v->j, &v->k) != 3) {
        return 0;
    }
    return 1;
}
