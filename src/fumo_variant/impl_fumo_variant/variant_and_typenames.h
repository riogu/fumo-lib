#pragma once
#include "../../structs.h"
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
//---------------------------------------------------------
#define TypeName(Type) #Type,
static const char* all_type_names[] = {ALL_VARIANT_TYPES(TypeName)};
#undef TypeName

static inline const char* fumo$variant_type_name(fumo$variant any) {
    return all_type_names[any.type_id];
}

typedef struct fumo$optional {} fumo$optional ;



