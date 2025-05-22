#include "fumo/fumo_c_definitions.h"
#include "fumo/fumo_type_name.h"

// Basic usage
int main() {
    int x = 123;
    PRINTF("this is x: ", x);

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect);

    let inner_value = get_if(Shape, var) {
        inner_value->shape_id = 123123;
    }
    else {
        printf("failed, type: %s\n", type_name(var));
    }

    match(var) ({
        case(Shape, var) var->shape_id = 213;
        case(Rectangle, rect) {
            rect->height = 123;
        }
        _default {
            printf("unknown type\n");
        }
    });

    return 0;
}
