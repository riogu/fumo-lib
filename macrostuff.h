#pragma once
#include "structs.h"
// random structs to test
#define _INNER_ALL_TYPES \
    XMACRO1(Position) \
    XMACRO1(Circle) \
    XMACRO1(Shape) \
    XMACRO1(Body) \
    XMACRO1(Piece) \
    XMACRO1(Camera) \
    XMACRO1(Rectangle) \
    XMACRO1(Board)

// clang-format off
//---------------------------------------------------------
typedef struct Any { 

#define XMACRO1(Type) Type Type;
    union value_t { _INNER_ALL_TYPES } value;
#undef XMACRO1

#define XMACRO1(Type) T_##Type,
      enum t_name { _INNER_ALL_TYPES } type_id;
#undef XMACRO1

} Any;
//---------------------------------------------------------
#define XMACRO1(Type) #Type,
static const char* all_type_names[] = {_INNER_ALL_TYPES};
#undef XMACRO1
static inline const char* type_name(Any any) {
return all_type_names[any.type_id];
}
//---------------------------------------------------------

#define XMACRO1(Type) Type : T_##Type,
#define _MAKE_ANY_UNION(var) \
    _Generic((var), \
             _INNER_ALL_TYPES\
            default: 0) 

#define Any(var) (Any) {\
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


#define _GET_ANY_TYPE(var)



#define _TRY_OTHER_TYPE(var1, var2) \
    _Generic(typeof(var2),\
             Any: _INNER_IS_SAME_TYPE(var1, var2)\
             default: _TRY_OTHER_TYPE(var2)

#define IS_SAME_TYPE(var1, var2) \
    _Generic(typeof(var1),\
             Any: _INNER_IS_SAME_TYPE(_GET_ANY_TYPE(var1), var2)\
             default: _TRY_OTHER_TYPE(var1, var2)


    // _INNER_IS_SAME_TYPE(typeof(var1), typeof(var2.value))
