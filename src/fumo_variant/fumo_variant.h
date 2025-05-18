#pragma once
#include "../structs.h"
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
#define fumo$get_type_id(var) \
    _Generic((var), \
             ALL_VARIANT_TYPES(XMACRO1)\
            default: -69) 

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

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T;

#define fumo$get_underlying(T, Variant) \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)}

#define fumo$get_if(T, Variant) (T*) ({ \
    void* result = NULL; \
    if ((fumo$get_type_id(*(T*)0) == Variant.type_id)) fumo$get_underlying(T, Variant); \
    result; \
}); if ((fumo$get_type_id(*(T*)0) == Variant.type_id))

//---------------------------------------------------------
//---------------------------------------------------------

// int static inline both_are_variants(fumo$variant X, fumo$variant Y) {
//     return (X.type_id == Y.type_id)
// }

// #define _X_isnt_variant(X, Y)\
//     _Generic(typeof(Y),\
//             fumo$variant: (fumo$get_type_id(typeof(X)) == Y.type_id)),\
//             default: (typeof(X) == typeof(Y))
//
// #define _X_is_variant(X, Y) \
//     _Generic(typeof(Y),\
//             fumo$variant: (X.type_id == ((fumo$variant)Y).type_id), \
//             default: (X.type_id == fumo$get_type_id(typeof(Y))))

#define fumo$is_same_t(X, Y) ({\
})

//
// #define IS_SAME_TYPE(T, U) _Generic(typeof(T), typeof(U): 1, default: 0)
//---------------------------------------------------------
// NOTE: this one isnt very useful
// #define GET_TYPE_INSTANCE(T) \
//     static inline T instance_of_##T(T type) { \
//         return (T) {}; \
//     }
// ALL_VARIANT_TYPES(GET_TYPE_INSTANCE)
// #define INSTANCE_OF(T) , T: instance_of_##T
// #define fumo$make_instance_of(var) \
//     (typeof(var))((_Generic(typeof(var) ALL_VARIANT_TYPES(INSTANCE_OF))(var)))
//---------------------------------------------------------
//
// #define STATIC_IF(EXPR,THEN,ELSE)     \
//   _Generic( &(char[1 + !!(EXPR)]){0}, \
//     char (*)[2]: (THEN),              \
//     char (*)[1]: (ELSE)               \
//   )
//
// #define _CHECK_TYPE_SAFETY(T) , T : 1
// #define _TYPE_SAFE(T) \
//     _Generic( *(T*)0\
//              ALL_VARIANT_TYPES(_CHECK_TYPE_SAFETY),\
//              default: 0)
//
// #define fumo🔨get fumo$get

// #define autofree __attribute__((__cleanup__(autofree_impl)))
// static inline void autofree_impl(void* p) {
//     free(*((void**)p));
// }
