#include "fumo_variant/fumo_variant.h"
#include <stdio.h>

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    auto result1 = fumo$if_get(Rectangle, variant) {
        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
    }
    else {
        printf("didnt have a rectangle!\n");
    }
    printf("type_name: %s", fumo$variant_type_name(variant));
    return 0;
}

//
// if (fumo$is_same_t(Rectangle, var)) {
//     auto rect = fumo$get(Rectangle, var);
//     rect.width = 123;
// }
//
// fumo$is_same_t(Position, var) ? printf("true\n") : printf("false\n"); // true
// fumo$is_same_t(rect, var) ? printf("true\n") : printf("false\n"); // false
// fumo$is_same_t(pos, var) ? printf("true\n") : printf("false\n"); // true
//
