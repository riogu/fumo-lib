// clang-format off
#pragma once
#include "fumo_c_definitions.h" // IWYU pragma: export
#include "structs.h" // IWYU pragma: export
#include <stdbool.h>
#include <wchar.h> // IWYU pragma: export

//---------------------------------------------------------
// fumo primitive data types for type safety
#define XMACRO(Type) T_id_##Type,
typedef enum T_id { 
        ALL_DATA_TYPE_NAMES(XMACRO)
        ALL_VARIANT_TYPES(XMACRO)
} T_id;
#undef XMACRO

#define XMACRO(Type) Type _##Type;
typedef union value_t {
    ALL_VARIANT_TYPES(XMACRO) 
    ALL_DATA_TYPES_VARIABLE(,_,;)
} T_value;
#undef XMACRO
//---------------------------------------------------------
// fumo variant implementation

typedef struct _variant { 
    T_value value;
    T_id type_id;
} _variant;

#define _variant(var) (_variant) {    \
    .type_id = fumo$get_type_id(var), \
    .value = (union value_t) var      \
} 

#define TypeName(Type) #Type,
static const char* all_type_names[] = {
    ALL_VARIANT_TYPES(TypeName)
    ALL_DATA_TYPES(TypeName)
};
#undef TypeName

static inline const char* __variant_type_name(_variant any) {
    return all_type_names[any.type_id];
}

//---------------------------------------------------------

typedef struct Result {
    T_value Ok;
    T_value Err;
    T_id type_id;

    bool was_err;

} Result;

#define Ok(_v) (Result) {._Ok = _v, .was_err = 0}
#define Err(_v) (Result) {._Err = (union Err)_v, .was_err = 1}

#define _ 0
#define _Ok(x)
#define _Err(x)


/// fumo type_name for any variable implementation
#define type_name(Var) \
    _Generic(typeof(*(Var*)0), \
