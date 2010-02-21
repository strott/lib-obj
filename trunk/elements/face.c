/*
 *  face.c
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "face.h"

/**
 * read data for a face
 */
int _face_read(FILE *fp, face *f) {
    int i;
    for (i = 0; i < 3; ++i) {
        if (!_face_vertex_read(fp, &f->fv[i], i)) {
            return 0;
        }
    }
    return 1;
}

/**
 * read data for a face vertex
 *
 * @todo: improve error checking since now it's not used
 */
int _face_vertex_read(FILE *fp, face_vertex *v, int i) {
    fscanf(fp, "%d", &v->v);
    if (fscanf(fp, "/") == 1) {
        fscanf(fp, "%d", &v->vt);
        fscanf(fp, "/%d", &v->vn);
    }
    return 1;
}
