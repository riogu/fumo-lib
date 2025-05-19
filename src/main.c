#include "fumo/optional_t.h"
#include "fumo/variant.h"
#include "structs.h"
#include <inttypes.h>
#include <stdio.h>

// optional_t(float) opt_float;
// const auto e = (optional_t) {.value = (typeof()*)&};

int main() {

    // optional_epic some = optional_epic((epic) {});

    // int var = 13;
    // optional_t opt = (optional_t) {.value = (typeof(1)*)&1};

    // return 0;

    Rectangle rect = {.width = 123, .height = 1231};
    _variant var = _variant(rect); // making variant struct

    is_same_t((Position) {}, var) ? printf("true\n") : printf("false\n");
    is_same_t(rect, var) ? printf("true\n") : printf("false\n");
    is_same_t((Shape) {}, rect) ? printf("true\n") : printf("false\n");

    let inner_value = get_if(Shape, var) {}

    inner_value->shape_id = 123123;

    if (is_same_t((Shape) {}, var)) {}

    match(var) {
        case(Shape) _Shape->shape_id = 123;
        _default printf("we dont get a value here");
    }
    



    return 0;
}

            // int main() {
            //
            //     Rectangle rect = {.width = 123, .height = 1231};
            //     fumo$variant variant = fumo$variant(rect);
            //
            //     fumo$is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
            //     // false
            //     fumo$is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
            //     // true
            //     fumo$is_same_t((Shape) {}, rect) ? printf("true\n") : printf("false\n");
            //     // false
            //
            //     auto result1 = fumo$get_if(Rectangle, variant) {
            //         printf("width before: %d \n", result1->width);
            //
            //         result1->width = 213123;
            //         printf("there was a rectangle, width: %d\ntype_name: %s\n\n",
            //                result1->width,
            //                fumo$variant_type_name(variant));
            //     }
            //     else {
            //         printf("didnt have a rectangle!\n");
            //     }
            //
            //     Position pos = {.x = 69420};
            //     variant = fumo$variant(pos);
            //
            //     auto result2 = fumo$get_if(Shape, variant) {
            //         // is never reached
            //         result2->shape_id = 213;
            //     }
            //     else {
            //         // fails to get the value, result2 is NULL
            //         printf("couldn't get shape from variant.\n");
            //         printf("type in variant: %s\n", fumo$variant_type_name(variant));
            //     }
            //
            //     // does nothing
            //     auto shape = fumo$get_if(Shape, variant) {
            //         printf("my shape id: %d\n", shape->shape_id);
            //         // you can write the code assuming you have the right type
            //         // but its only ran if the stored type matches Shape
            //
            //     } // the else{} is optional
            //
            //     return 0;
            // }

            //
            // *(volatile char*)0 = 0;
            // if (fumo$is_same_t(Rectangle, var)) {
            //     auto rect = fumo$get(Rectangle, var);
            //     rect.width = 123;
            // }
            //
            //
