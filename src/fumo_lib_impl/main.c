#include "fumo_type_name.h"
#define else else
#define _ _default

Result get_input();

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

    is_same_t((Position) {}, var) ? printf("true\n") : printf("false\n");

    Shape s = {.shape_id = 123123};
    Variant var1 = Variant(s);

    match(var) ({
        case(Shape, var) var->shape_id = 213;
        case(Rectangle, rect) {
            rect->height = 123;
        }
        case(Position, pos) {
            pos->x = 123;
            printf("%d sucessfully updated pos.\n", pos->x);
            pos->y = 123;
            printf("%d sucessfully updated pos.\n", pos->y);
        }
        _ {
            printf("unknown type.\n");
        }
    });






    return 0;
}
