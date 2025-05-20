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

// random structs to test
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

// clang-format off
//---------------------------------------------------------
//---------------------------------------------------------
#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto

typedef struct _variant { 

#define XMACRO(Type) Type _##Type;
    union value_t { ALL_VARIANT_TYPES(XMACRO) } value;
#undef XMACRO

#define XMACRO(Type) T_id_##Type,
      enum T_id { ALL_VARIANT_TYPES(XMACRO) } type_id;
#undef XMACRO

} _variant;

#define XMACRO1(Type) Type : T_id_##Type,
#define fumo$get_type_id(var) (enum T_id)\
    _Generic(var, \
             ALL_VARIANT_TYPES(XMACRO1)\
            default: T_UNREGISTERED) 

#define _variant(var) (_variant) {\
    .type_id = fumo$get_type_id(var),\
    .value = (union value_t) var\
} 
//---------------------------------------------------------
//---------------------------------------------------------
#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName)};
#undef TypeName

static inline const char* variant_type_name(_variant any) {
    return all_type_names[any.type_id];
}

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define _GET_UNDERLYING(T, Variant) \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)}

#define get_if(T, Variant) (T*) ({ \
    void* result = NULL; \
    _GET_UNDERLYING(T, Variant); \
    result; \
}); if ((fumo$get_type_id(*(T*)0) == Variant.type_id))


#define _CASE_VAL_(T, Variant) case T_id_##T: result = &Variant.value._##T; break;

#define case(T) break;}); case T_id_##T: ({ T* _##T = &____value____->_##T; 

#define match(Variant) auto ____value____ = (union value_t *)({ \
    auto result = NULL; \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_CASE_VAL_, Variant)}\
    result; \
}); switch(Variant.type_id) {(

#define _default break;}); default:

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------

#define _IS_SAME_TYPE(T, U) _Generic(typeof(T), typeof(U): 1, default: 0)

#define is_same_t(X, Y) \
    (({ \
         let is_x_v = _Generic(typeof(X), _variant: 1, default: 0); \
         let is_y_v = _Generic(typeof(Y), _variant: 1, default: 0); \
         let is_same_t =  \
            (is_x_v && is_y_v) \
            ? ( (*(_variant*)&X).type_id == (*(_variant*)&Y).type_id ) \
            : (is_x_v && !is_y_v) \
            ? ( (*(_variant*)&X).type_id == fumo$get_type_id(typeof(Y)) ) \
            : (!is_x_v && is_y_v) \
            ? ( fumo$get_type_id(typeof(X)) == (*(_variant*)&Y).type_id ) \
            : (!is_x_v && !is_y_v) \
            ? ( _IS_SAME_TYPE(X, Y) ) \
            : 0; \
        is_same_t; \
    }))
#include <stdio.h>

typedef struct NewStruct {} NewStruct;

int main() {

    Rectangle rect = {.width = 123, .height = 1231};
    _variant variant = _variant(rect);
    
    Shape shape = {.shape_id = 13};
    _variant var = _variant(shape); // making variant struct

    // variables are only avaible inside the case label
    match(var) {
        case(Shape) _Shape->shape_id = 123; // goes here
        case(Rectangle) //etc...
        _default printf("we dont get a value here");
    }



    is_same_t((Position) {}, variant) ? printf("true\n") : printf("false\n");
    is_same_t(rect, variant) ? printf("true\n") : printf("false\n");
    is_same_t((NewStruct) {}, rect) ? printf("true\n") : printf("false\n");

    let result1 = get_if(Rectangle, variant) {

        printf("width before: %d \n", result1->width);
        result1->width = 213123;
        printf("there was a rectangle, width: %d\n", result1->width);
        printf("type_name: %s\n\n", variant_type_name(variant));
    }
    else {
        printf("didnt have a rectangle!\n");
    }

    Position pos = {.x = 69420};
    variant = _variant(pos);

    auto result2 = get_if(Shape, variant) {
        // is never reached
        result2->shape_id = 213;
    }
    else {
        // fails to get the value, result2 is NULL
        printf("couldn't get shape from variant.\n");
        printf("type in variant: %s\n", variant_type_name(variant));
    }

    return 0;
}
