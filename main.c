#include <stdio.h>
#import "obj.h"

int main (int argc, const char * argv[]) {
    const char elements[][OBJ_ELEMENT_NAME_MAX_LENGTH] = {"v", "vn", "f"};
    obj model = obj_process_file("cube.obj", elements);
    printf("Hello OBJ");
    return 0;
}
