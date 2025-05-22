#include "fumo/fumo_c_definitions.h"
#include "fumo/fumo_type_name.h"
#define else else
#define _ _default

Result get_input();

int main() {

    int x = 123;
    PRINTF("this is x: ", x);

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var =
        (Variant) {.value = (union T_value)rect,
                   .type_id = (enum T_id) _Generic(rect,
                       Position: ___type_id_Position,
                       Shape: ___type_id_Shape,
                       Body: ___type_id_Body,
                       Rectangle: ___type_id_Rectangle,
                       Position_ptr: ___type_id_Position_ptr,
                       Shape_ptr: ___type_id_Shape_ptr,
                       Body_ptr: ___type_id_Body_ptr,
                       Rectangle_ptr: ___type_id_Rectangle_ptr,
                       Position_ptr_ptr: ___type_id_Position_ptr_ptr,
                       Shape_ptr_ptr: ___type_id_Shape_ptr_ptr,
                       Body_ptr_ptr: ___type_id_Body_ptr_ptr,
                       Rectangle_ptr_ptr: ___type_id_Rectangle_ptr_ptr,
                       _Bool: ___type_id__Bool,
                       char: ___type_id_char,
                       signed_char: ___type_id_signed_char,
                       unsigned_char: ___type_id_unsigned_char,
                       short: ___type_id_short,
                       int: ___type_id_int,
                       long: ___type_id_long,
                       long_long: ___type_id_long_long,
                       unsigned_short: ___type_id_unsigned_short,
                       unsigned_int: ___type_id_unsigned_int,
                       unsigned_long: ___type_id_unsigned_long,
                       unsigned_long_long: ___type_id_unsigned_long_long,
                       float: ___type_id_float,
                       double: ___type_id_double,
                       long_double: ___type_id_long_double,
                       char_ptr: ___type_id_char_ptr,
                       char_const_ptr: ___type_id_char_const_ptr,
                       wchar_t_ptr: ___type_id_wchar_t_ptr,
                       wchar_t_const_ptr: ___type_id_wchar_t_const_ptr,
                       void_ptr: ___type_id_void_ptr,
                       void_const_ptr: ___type_id_void_const_ptr)(rect)};

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
