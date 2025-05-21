#pragma once
#include "../structs.h" // IWYU pragma: export
#include "fumo_c_definitions.h" // IWYU pragma: export
#include <stdbool.h>
#include <wchar.h> // IWYU pragma: export

//---------------------------------------------------------
// fumo primitive data types for type safety
#define XMACRO(Type) T_id_##Type,

typedef enum T_id {
    ALL_VARIANT_TYPES(XMACRO) //
    ALL_DATA_TYPE_NAMES(XMACRO)
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
} __attribute__((packed)) Variant;

#define Variant(var) (Variant) {     \
    .value = (union value_t) var,    \
    .type_id = get_type_id(var)      \
}

//---------------------------------------------------------
// fumo result type, inspired by the Rust result type
typedef struct Result {
    T_value value; // is Ok() or Err()
    T_id type_id;

    bool was_err;

} __attribute__((packed)) Result;

#define Ok(_v) (Result) {.value = (union value_t) _v, .was_err = 0}
#define Err(_v) (Result) {.value =(union value_t) _v, .was_err = 1}

#define _Ok(T)                              \
}); default: break;}                        \
T* _##T = &____value____->_##T;             \
}})

#define _Err(_v)

#define as(T)

// #define optional_t(T) typedef struct { T value; _Bool nullopt_t;}
//
// #define Some(_v) (optional_t) {.value = (typeof(_v)*)& _v}
//
// #define None(T)
