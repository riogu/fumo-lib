typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Shape {
    int shape_id;
} Shape;

typedef struct Body {
    Position position;
    float radius;
} Body;

typedef struct Rectangle {
    int width;
    int height;
} Rectangle;

#define ALL_VARIANT_TYPES(F) \
    F(Position) \
    F(Shape) \
    F(Body) \
    F(Rectangle)

#define ALL_VARIANT_TYPES_V(F, Variant) \
    F(Position, Variant) \
    F(Shape, Variant) \
    F(Body, Variant) \
    F(Rectangle, Variant)

#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto

// clang-format off
//---------------------------------------------------------
//---------------------------------------------------------
typedef struct fumo$variant { 

#define XMACRO(Type) Type _##Type;
    union value_t { ALL_VARIANT_TYPES(XMACRO) } value;
#undef XMACRO

#define XMACRO(Type) T_id_##Type,
      enum T_id { ALL_VARIANT_TYPES(XMACRO) } type_id;
#undef XMACRO

} fumo$variant;

#define XMACRO1(Type) Type : T_id_##Type,
#define fumo$get_type_id(var) (enum T_id)\
    _Generic(var, \
             ALL_VARIANT_TYPES(XMACRO1)\
            default: T_UNREGISTERED) 

#define fumo$variant(var) (fumo$variant) {\
    .type_id = fumo$get_type_id(var),\
    .value = (union value_t) var\
} 
//---------------------------------------------------------
//---------------------------------------------------------
#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName)};
#undef TypeName

static inline const char* fumo$variant_type_name(fumo$variant any) {
    return all_type_names[any.type_id];
}

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define fumo$get_underlying(T, Variant) \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)}

#define fumo$get_if(T, Variant) (T*) ({ \
    void* result = NULL; \
    if ((fumo$get_type_id(*(T*)0) == Variant.type_id)) fumo$get_underlying(T, Variant); \
    result; \
}); if ((fumo$get_type_id(*(T*)0) == Variant.type_id))

//---------------------------------------------------------
//---------------------------------------------------------

#define _IS_SAME_TYPE(T, U) _Generic(typeof(T), typeof(U): 1, default: 0)

#define fumo$is_same_t(X, Y) \
    (({ \
        int is_x_v = _Generic(typeof(X), fumo$variant: 1, default: 0); \
        int is_y_v = _Generic(typeof(Y), fumo$variant: 1, default: 0); \
        int is_same_t =  \
            (is_x_v && is_y_v) \
            ? ( (*(fumo$variant*)&X).type_id == (*(fumo$variant*)&Y).type_id ) \
            : (is_x_v && !is_y_v) \
            ? ( (*(fumo$variant*)&X).type_id == fumo$get_type_id(typeof(Y)) ) \
            : (!is_x_v && is_y_v) \
            ? ( fumo$get_type_id(typeof(X)) == (*(fumo$variant*)&Y).type_id ) \
            : (!is_x_v && !is_y_v) \
            ? ( _IS_SAME_TYPE(X, Y) ) \
            : 0; \
        is_same_t; \
    }))

#include <stdio.h>

typedef struct NewStruct {} NewStruct;

int main() {
    Rectangle rect = {.width = 123, .height = 1231};
    fumo$variant variant = fumo$variant(rect);

    fumo$is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
    // false
    fumo$is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
    // true
    fumo$is_same_t((NewStruct) {}, rect) ? printf("true\n") : printf("false\n");
    // false

    auto result1 = fumo$get_if(Rectangle, variant) {

        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
        printf("type_name: %s\n\n", fumo$variant_type_name(variant));
    }
    else {
        printf("didnt have a rectangle!\n");
    }

    Position pos = {.x = 69420};
    variant = fumo$variant(pos);

    auto result2 = fumo$get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;
    }
    else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", fumo$variant_type_name(variant));
    }
    return 0;
}
