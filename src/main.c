#include "fumo/fumo_type_name.h"
#include "structs.h"
Result get_input();
#define else else
#define _ _default

typedef union e {
    Position pos;
    Rectangle rect;
} e;

int main() {

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect);
    is_same_t((Rectangle) {}, var) ? printf("true\n") : printf("false\n");

    let inner_value = get_if(Shape, var) {
        inner_value->shape_id = 123123;
    }
    else {
        printf("failed, type: %s\n", type_name(var));
    }

    Shape s = {.shape_id = 123123};
    Variant var1 = Variant(s);
    match(var1) {
        case(Shape) _Shape->shape_id = 213;
        _ {
            match(var1) {
                case(Shape) 
                    printf("found shape %d.", _Shape->shape_id);
                _ {
                match(var) {
                    _ printf("%s this is valid syntax", "wow");
                    }
                }
            }
        }
    }

    return 0;
}

Result get_input() {
    Shape s = {.shape_id = 12};
    Result res = Ok(s);
    int n = 0;

    if (scanf("%d", &n)) {
        return Ok(n);
    }
    return Err("couldnt get input.\n");
}

            // void func() {
            //     match(get_input()) {
            //         _Ok(var) as(int) {
            //             printf("what happened %d", var);
            //         }
            //         _Err(errval) as(char*) {
            //             printf("what the hell %s", errval);
            //         }
            //     }
            // }
