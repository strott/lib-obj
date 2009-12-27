/*
 *  objt.h
 *  libObj
 *
 *  Created by claudio beatrice on 11/13/09.
 *  Copyright 2009 claudio beatrice. All rights reserved.
 *
 */

/*
supported elements
- geometric vertices (v)
- vertex normals (vn)
- texture vertices (vt)
- face (f)
unsupported
- smoothing group (s)
- material library (mtllib)
- material name (usemtl)
*/

/**
 * geometric vertices (v)
 *
 * Polygonal and free-form geometry statement.
 */
typedef struct geometric_vertex_s {
    float x, y, z, w;
} geometric_vertex;

/**
 * texture vertices (vt)
 *
 * Vertex statement for both polygonal and free-form geometry.
 */
typedef struct texture_vertex_s {
    float u, v, w;
} texture_vertex;

/**
 * vertex normals (vn)
 *
 * Polygonal and free-form geometry statement.
 */
typedef struct vertex_normal_s {
    float i, j, k;
} vertex_normal;

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
