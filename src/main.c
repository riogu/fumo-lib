#include "fumo/fumo_type_name.h"
#include "structs.h"
Result get_input();

int main() {

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect);

    match(var) {
        _case(Shape) _Shape->shape_id = 123;
        _default printf("wasnt one of the stated types.\n");
    }

    Shape s = {.shape_id = 123123};
    Variant var1 = Variant(s);

    match(var) {
        _case(Shape) _Shape->shape_id = 213;
        _default {
            match(var1) {
                _case(Shape) {
                    printf("found shape %d.", _Shape->shape_id);
                }
                _default printf("found no shape\n.");
            }
        }
    }

    return 0;
}

// let inner_value = get_if(Shape, var) {
//     inner_value->shape_id = 123123;
// }
// else {
//     // printf("failed, type: %s\n", type_name((Position){});
// }
// is_same_t((Position) {}, var) ? printf("true\n") : printf("false\n");

// Result get_input() {
//     Shape s = {.shape_id = 12};
//     Result res = Ok(s);
//     int n = 0;
//
//     if (scanf("%d", &n)) {
//         return Ok(n);
//     }
//     return Err("couldnt get input.\n");
//
// }

// void func() {
//    match(get_input()) {
//         _Ok(var) {
//             printf("what happened %d", var);
//         }
//         _Err(errval) {
//             printf("what the hell %s", errval);
//         }
//     }
// }
