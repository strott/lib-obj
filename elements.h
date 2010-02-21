/*
 *  elements.h
 *  lib-obj
 *
 *  Created by claudio beatrice on 2/21/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "elements/face.h"
#include "elements/geometric_vertex.h"
#include "elements/vertex_normal.h"

// remember to increment this to match the number of included elements
#define OBJ_ELEMENTS_COUNT 3

// max length for name of an element
#define OBJ_ELEMENT_NAME_MAX_LENGTH 10

// max number of elements in a list 
#define OBJ_ELEMENT_LIST_MAX_LENGTH 100