#pragma once
#include "structs.h"
// random structs to test
#define ALL_VARIANT_TYPES(F) \
    F(Position) \
    F(Circle) \
    F(Shape) \
    F(Body) \
    F(Piece) \
    F(Camera) \
    F(Rectangle) \
    F(Board)

// clang-format off
//---------------------------------------------------------
typedef struct Fumo$Variant { 

#define XMACRO(Type) Type Type;
    union value_t { ALL_VARIANT_TYPES(XMACRO) } value;
#undef XMACRO

#define XMACRO(Type) T_id_##Type,
      enum t_name { ALL_VARIANT_TYPES(XMACRO) } type_id;
#undef XMACRO

} Fumo$Variant;
//---------------------------------------------------------
#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName)};
#undef TypeName
static inline const char* type_name(Fumo$Variant any) {
return all_type_names[any.type_id];
}
//---------------------------------------------------------

#define XMACRO1(Type) Type : T_id_##Type,
#define _MAKE_ANY_UNION(var) \
    _Generic((var), \
             ALL_VARIANT_TYPES(XMACRO1)\
            default: 0) 

#define Fumo$Variant(var) (Fumo$Variant) {\
    .type_id = _MAKE_ANY_UNION(var),\
    .value = (union value_t) var\
} \
//---------------------------------------------------------
// #define _IS_SAME_ANY_TYPE(T, U)\
  // _Generic( *(T*)0,       \

//---------------------------------------------------------
#define _INNER_IS_SAME_TYPE(T,U) \
  _Generic( *(T*)0,       \
    typeof(U): 1,  \
    default         : 0)

//---------------------------------------------------------
#define GET_TYPE_NAME(Type) Type : (Type){},
#define TYPE_NAME(var) \
    _Generic((typeof(var)), \
              ALL_VARIANT_TYPES(GET_TYPE_NAME) \
              )
//---------------------------------------------------------




#define each_typeid(Type) \
    case T_id_##Type: {\
        return (Type){};\
  }

#define _GET_ANY_TYPE(var) \
    ({ \
    switch (var.type_id): ALL_VARIANT_TYPES(each_typeid); \
     }) 

#define _TRY_OTHER_TYPE(var1, var2) \
    _Generic(typeof(var2),\
             Fumo$Variant: _INNER_IS_SAME_TYPE(_GET_ANY_TYPE(var1), var2)\
             default: _INNER_IS_SAME_TYPE(var1, var2)\

#define IS_SAME_TYPE(var1, var2) \
    _Generic(typeof(var1),\
             Fumo$Variant: _INNER_IS_SAME_TYPE(_GET_ANY_TYPE(var1), var2)\
             default: _TRY_OTHER_TYPE(var1, var2)


    // _INNER_IS_SAME_TYPE(typeof(var1), typeof(var2.value))
