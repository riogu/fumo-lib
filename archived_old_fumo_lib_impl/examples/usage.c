#include "fumo_lib.h"

// Basic usage
int main() {
    int x = 123;
    PRINTF("safe print no specifier, this is x: ", x);

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect);

    let inner_value = get_if(Shape, var) {
        inner_value->shape_id = 123123;
    }
    else {
        printf("failed, type: %s\n", type_name(var));
    }

    if (is_same_t((Rectangle) {}, var)) {
        printf("yes this is a rectangle\n");
    } else {
        printf("no this is not a rectangle\n");
    }

    match(var) ({
        case(Shape, var) var->shape_id = 213;
        case(Rectangle, rect) {
            rect->height = 123;
        }
        _ {
            printf("unknown type\n");
        }
    });

    return 0;
}
