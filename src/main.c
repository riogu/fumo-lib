#include "fumo/fumo_c_definitions.h"
#include "fumo/fumo_data_structures.h"
#include <stdio.h>
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
        // printf("failed, type: %s\n", variant_type_name(var));
    }

    if (is_same_t((Shape) {}, var)) {}

    match(var) {
        case(Shape) _Shape->shape_id = 123;
        case(Rectangle) {
            _Rectangle->height = 222;
        }
        _default printf("we dont get a value here");
    }

    
    return 0;
}

Result get_input() {

    int n = 10;
    if (scanf("%d", &n)) {
        return Ok(n);
    }
    return Err((Position) {.x = 213});
}
