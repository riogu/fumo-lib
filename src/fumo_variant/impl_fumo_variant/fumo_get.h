#pragma once
// clang-format off
#include "variant_and_typenames.h" // IWYU pragma: export

#define _CHECK_TYPE_SAFETY(T) , T : 1
#define _TYPE_SAFETY(T) \
    _Generic( *(T*)0\
             ALL_VARIANT_TYPES(_CHECK_TYPE_SAFETY),\
             default: 0)

#define _UNDERLYING_VALUE(T, Variant) case T_id_##T: result = &Variant.value._##T;

#define fumo$get_underlying(T, Variant) \
    switch (Variant.type_id) {ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)}

#define fumo$get(T, Variant) (T*) ({ \
    void* result = NULL; \
    if (_TYPE_SAFETY(T)) fumo$get_underlying(T, Variant); \
    result; \
}); if (({ _Generic(*(T*)0, T : 1, default: 0);\
}))

#define fumo🔨get fumo$get

// #define wow : : :

// /D<Wow>{=|#}<Position>

// clang-format off
//---------------------------------------------------------
#define fumo$is_same_t(X, Y) _INNER_IS_SAME_TYPE(STORED_TYPE(X), STORED_TYPE(Y))
//---------------------------------------------------------

#define _INNER_IS_SAME_TYPE(T, U)\
    _Generic(*(T*)0,\
             typeof(U): 1, \
             default: 0)
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
