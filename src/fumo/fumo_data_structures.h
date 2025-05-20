#pragma once
#include "../structs.h" // IWYU pragma: export
#include "fumo_c_definitions.h" // IWYU pragma: export
#include <stdbool.h>
#include <wchar.h> // IWYU pragma: export

//---------------------------------------------------------
// fumo primitive data types for type safety
#define XMACRO(Type) T_id_##Type,

typedef enum T_id {
    ALL_DATA_TYPE_NAMES(XMACRO) //
    ALL_VARIANT_TYPES(XMACRO)
} T_id;

#undef XMACRO

#define XMACRO(Type) Type _##Type;

typedef union value_t {
    ALL_VARIANT_TYPES(XMACRO) //
    ALL_DATA_TYPES_VARIABLE(, _, ;)
} T_value;

#undef XMACRO

//---------------------------------------------------------
// fumo Variant implementation

typedef struct Variant {
    T_value value;
    T_id type_id;
} Variant;

#define Variant(var) (Variant) {    \
    .type_id = fumo$get_type_id(var), \
    .value = (union value_t) var      \
}

//---------------------------------------------------------
// fumo result type, like the Rust result type

typedef struct Result {
    T_value Ok;
    T_value Err;
    T_id type_id;

    bool was_err;

} Result;

#define Ok(_v) (Result) {.Ok = _v, .was_err = 0}
#define Err(_v) (Result) {.Err = _v, .was_err = 1}

#define _ 0
#define _Ok(x)
#define _Err(x)

// #define optional_t(T) typedef struct { T value; _Bool nullopt_t;}
//
// #define Some(_v) (optional_t) {.value = (typeof(_v)*)& _v}
//
// #define None(T)
