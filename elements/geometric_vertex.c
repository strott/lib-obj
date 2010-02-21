/*
 *  geometric_vertex.c
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "geometric_vertex.h"

int _geometric_vertex_read(FILE *fp, geometric_vertex *g) {
    if (fscanf(fp, "%f%f%f", &g->x, &g->y, &g->z) != 3) {
        return 0;
    }
    return 1;
}