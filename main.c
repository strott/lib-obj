#include <stdio.h>
#import "obj.h"

int main (int argc, const char * argv[]) {
    const char *elements[OBJ_ELEMENT_NAME_MAX_LENGTH] = {"v", "vn", "f"};
    int i = 0;
    obj model;
    obj_process_file(&model, "cube.obj", elements);
    printf("Vertices: \n");

    for (i = 0; i < model.v_count; ++i) {
        printf("v %d: %f %f %f\n", i, model.v[i].x, model.v[i].y, model.v[i].z);
    }
    
    printf("Faces: \n");
    
    for (i = 0; i < model.f_count; ++i) {
        printf("f %d: %d/%d/%d %d/%d/%d %d/%d/%d\n", i, 
               model.f[i].fv[0].v, model.f[i].fv[0].vt, model.f[i].fv[0].vn, 
               model.f[i].fv[1].v, model.f[i].fv[1].vt, model.f[i].fv[1].vn, 
               model.f[i].fv[2].v, model.f[i].fv[2].vt, model.f[i].fv[2].vn);
    }
    
    return 0;
}
