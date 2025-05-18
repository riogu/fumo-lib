#include "fumo_variant/fumo_variant.h"
#include <stdio.h>

int main() {

    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    fumo$is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
    // false
    fumo$is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
    // true
    fumo$is_same_t((Shape) {}, rect) ? printf("true\n") : printf("false\n");
    // false

    auto result1 = fumo$get_if(Rectangle, variant) {
        printf("width before: %d \n", result1->width);

        result1->width = 213123;
        printf("there was a rectangle, width: %d\ntype_name: %s\n\n",
               result1->width,
               fumo$variant_type_name(variant));
    }
    else {
        printf("didnt have a rectangle!\n");
    }

    Position pos = {.x = 69420};
    variant = fumo$variant(pos);

    auto result2 = fumo$get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;
    }
    else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", fumo$variant_type_name(variant));
    }

    // does nothing
    //
    auto shape = fumo$get_if(Shape, variant) {
        printf("my shape id: %d\n", shape->shape_id);
        // you can write the code assuming you have the right type
        // but its only ran if the stored type matches Shape

    } // the else{} is optional

    return 0;
}

//
// *(volatile char*)0 = 0;
// if (fumo$is_same_t(Rectangle, var)) {
//     auto rect = fumo$get(Rectangle, var);
//     rect.width = 123;
// }
//
//
