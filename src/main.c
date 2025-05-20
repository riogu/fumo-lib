#include "fumo/fumo_type_name.h"
Result get_input();

int main() {

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect); // making variant struct

    is_same_t((Position) {}, var) ? printf("true\n") : printf("false\n");
    is_same_t(rect, var) ? printf("true\n") : printf("false\n");
    is_same_t((Shape) {}, rect) ? printf("true\n") : printf("false\n");

    let inner_value = get_if(Shape, var) {
        inner_value->shape_id = 123123;
    }
    else {
        printf("failed, type: %s\n", type_name(var));
    }

    if (is_same_t((Shape) {}, var)) {}

    match(var) {
        case(Shape) _Shape->shape_id = 123;
        case(Rectangle) {
            _Rectangle->height = 222;
        }
        _default printf("we dont get a value here");
    }

    // match(get_input()) {
    //     _Ok(var) {
    //         printf("what happened", var);
    //     }
    //     _Err(errval) {
    //         printf("what the hell %s", errval);
    //     }
    // }
    
    return 0;
}

Result get_input() {

    Shape s = {.shape_id = 12};
    Result res = Ok(s);
    int n = 10;

    if (scanf("%d", &n)) {
        return Ok(n);
    }
    return Err((Position) {.x = 213});

}
