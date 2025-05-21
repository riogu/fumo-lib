#include "fumo/fumo_c_definitions.h"
#include "fumo/fumo_type_name.h"
#define else else
#define _ _default

Result get_input();

int main() {

    Result r = get_input();
    match(r)({
        _Ok(int, var) printf("_Ok: %d.\n", *var);

        _Err(char_ptr, errval) {
            printf("what the hell, %s", *errval);
        }
    });

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
        _ {}
    });

    int x = 123213;

    return 0;
}

#define as
#define end

Result get_input() {
    int n = 0;
    if (scanf("%d", &n)) {
        return Ok(n);
    }
    return Err("scanf failed bruh.\n");
}
