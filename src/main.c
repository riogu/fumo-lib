#include "fumo_variant/fumo_variant.h"
#include "structs.h"
#include <stdio.h>

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    // NOTE: not working yet
    // need to check if the type_id of rectangle
    // matches the type_id inside the variant

    // int e・ = 321;

    // printf("%d", 🧐);
    // clang-format off

    auto result1 = fumo$get( Rectangle, variant) {
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
