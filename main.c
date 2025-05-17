#include "macrostuff.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

// Call it whatever you want, just for variables with type inference.
#define auto __auto_type
// Automatically frees a value at the end of scope.

#define autofree __attribute__((__cleanup__(autofree_impl)))

/* __cleanup__ gives void** not void* so can't pass free directly */
void autofree_impl(void* p) {
    free(*((void**)p));
}

int main() {
    Rectangle rect = {};

    Any var = Any(rect);

    printf("type_name: %s\n", type_name(var)); // type_name: Position

    IS_SAME_TYPE(Position, var) ? printf("true\n") : printf("false\n"); // false
    IS_SAME_TYPE(rect, var) ? printf("true\n") : printf("false\n"); // true
    IS_SAME_TYPE(Rectangle, var) ? printf("true\n") : printf("false\n"); // true

    return 0;
}
