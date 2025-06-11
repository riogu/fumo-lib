#pragma once

// clang-format off
// ----------------------------------------------------------------
// example structs for testing, unnecessary for usage
// structs should be included before the macros.
typedef struct Position {int x;int y;} Position;
typedef struct Shape {int shape_id;} Shape;
typedef struct Body {Position position;float radius;} Body;
typedef struct Rectangle {int width;int height;} Rectangle;
typedef struct Circle {float radius;} Circle;
typedef struct Piece {} Piece;
typedef struct Camera {} Camera;
typedef struct Board {} Board;

// NOTE: structs should be typedef'd. we want them in the global namespace for this lib.
// implementation can be changed to allow for using the struct keyword too.

// ----------------------------------------------------------------
// write your user made structs here in the macro, in this format
#define user_types Position, Shape, Body, Rectangle
// ----------------------------------------------------------------

// fumo_lib implementation starts here
// ----------------------------------------------------------------
#include "helper_macros/map_macro.h"
#include "helper_macros/standard_c_definitions.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
// creating pointer typedefs for all user structs.
// also creates a single macro that all the code uses for getting the user types.
#define make_ptr(T) T##_ptr
#define make_ptr_ptr(T) T##_ptr_ptr
// NOTE: __VA_ARGS__ is for potentially passing a variant.
// its used by get_if() macro to pass recursively more than one argument

#define map_to_all_types(macro, ...)                    \
    MAP_UD(macro, __VA_ARGS__,                          \
           user_types,                                  \
           MAP_LIST(make_ptr, user_types),              \
           MAP_LIST(make_ptr_ptr, user_types),          \
           standard_c_types,                            \
           MAP_LIST(make_ptr, standard_c_types)         \
           )

// ----------------------------------------------------------------
// create all the pointers for all types

#define typedefs_all_types_ptr(T, ...) typedef T* T##_ptr;
map_to_all_types(typedefs_all_types_ptr)
#undef typedefs_all_types_ptr

//---------------------------------------------------------
#define T_UNREGISTERED -420
#define let __auto_type

//---------------------------------------------------------
// NOTE: fumo_c syntax and useful operator definitions

#define UNDERLYING_VALUE(T, Variant)                    \
case T_id_##T: {                                        \
    (void)0;                                            \
    let _varname = (T*) &_value_->value;                \
    result = &_varname;                                 \
    break;                                              \
}

#define get_if(T, Variant) (T*) ({                      \
    let result = NULL;                                  \
    let __inner_ = Variant;                             \
    let _value_ = &__inner_;                            \
    switch (Variant.type_id) {                          \
        map_to_all_types(UNDERLYING_VALUE, Variant)     \
    }                                                   \
    _value_;                                            \
}); if ((get_type_id((T){}) == Variant.type_id))

//---------------------------------------------------------

#define match(Variant)                                  \
{                                                       \
    let __inner_ = Variant;                             \
    let _value_ = &__inner_;

#define case(T, varname)                                \
}                                                       \
{                                                       \
    let varname = (T*)&_value_->value;                  \
    bool temp = _value_->___inner_cookie___;            \
    if(get_type_id((T){}) == _value_->type_id) {        \
        _value_->___inner_cookie___ = true;             \
    }                                                   \
    if (!temp && _value_->___inner_cookie___)

#define _default                                        \
}                                                       \
    if(!_value_->___inner_cookie___)

#define _Ok(T, _varname)                                \
}                                                       \
{                                                       \
    let _varname = (T*) &_value_->value;                \
    if (!_value_->was_err                               \
        && (get_type_id((T){}) == _value_->type_id))

#define _Err(T, _varname)                               \
}                                                       \
    let _varname = (T*) &_value_->value;                \
    if (_value_->was_err                                \
        && (get_type_id((T){}) == _value_->type_id))

//---------------------------------------------------------
//---------------------------------------------------------
// type comparison macro

#define get_type_id_same(var) (T_id)                                \
    _Generic(var,                                                   \
             Variant: ___type_id_Variant,                           \
             Result: ___type_id_Result                              \
             map_to_all_types(__get_function_of_type_id))(var)      \

#define _IS_SAME_TYPE(T, U) _Generic((typeof(T)*)0, typeof(U)*: 1, default: 0)

#define is_compatible_t(X, Y)                                            \
    (({                                                                  \
         let is_x_v = _Generic(typeof(X), Variant: 1, default: 0);       \
         let is_y_v = _Generic(typeof(Y), Variant: 1, default: 0);       \
         let is_same_t =                                                 \
            (is_x_v && is_y_v)                                           \
            ? ( (*(Variant*)&X).type_id == (*(Variant*)&Y).type_id )     \
            : (is_x_v && !is_y_v)                                        \
            ? ( (*(Variant*)&X).type_id == get_type_id_same(Y) )         \
            : (!is_x_v && is_y_v)                                        \
            ? ( get_type_id_same(X) == (*(Variant*)&Y).type_id )         \
            : (!is_x_v && !is_y_v)                                       \
            ? ( _IS_SAME_TYPE(X, Y) )                                    \
            : 0;                                                         \
        is_same_t;                                                       \
    }))

//---------------------------------------------------------
// fumo primitive data types for type safety
#define make_t_ids(Type, ...) T_id_##Type,
typedef enum T_id {
    map_to_all_types(make_t_ids)
} T_id;
#undef make_t_ids

#define make_t_values(Type, ...) Type _##Type;
typedef union T_value {
    map_to_all_types(make_t_values) 
} T_value;
#undef make_t_values

//---------------------------------------------------------
// fumo Variant implementation

typedef struct Variant {
    T_value value;
    T_id type_id;
    bool ___inner_cookie___; // not needed
    // only used in the case of changing the type the variant held inside of a case label while matching on that variant.
} Variant;

#define Variant(var) (Variant) {     \
    .value = (union T_value) var,    \
    .type_id = get_type_id(var)      \
}

//---------------------------------------------------------
// fumo result type, inspired by the Rust result type
typedef struct Result {
    T_value value; // is Ok() or Err()
    T_id type_id;
    bool was_err;

} Result;

#define Ok(_v) (Result) {.value = (union T_value) _v, .type_id = get_type_id(_v), .was_err = 0}
#define Err(_v) (Result) {.value =(union T_value) _v, .type_id = get_type_id(_v), .was_err = 1}

//---------------------------------------------------------
/// fumo type_name implementation

#define TypeName(Type, ...) #Type,
static const char* all_type_names[] = { map_to_all_types(TypeName) };
// similar to how __FUNCTION__ provides the function name as a variable, fumo-lib provides type names as a variable too.
#undef TypeName
// separate cases for the Variant and Result types
static inline T_id ___type_id_Variant(Variant variant) {return variant.type_id;}
static inline T_id ___type_id_Result(Result result) {return result.type_id;}
static inline const char* ___type_name_Variant(Variant variant) {return all_type_names[variant.type_id];}
static inline const char* ___type_name_Result(Result result) {return all_type_names[result.type_id];}
static inline const T_id ___type_unregistered_id(void) {return (T_id)T_UNREGISTERED;} // not used
// this is mainly for if the user wants error handling on unknown types to the fumo type system

#define ___each_type_name_(T, ...)               \
static inline const char* ___type_name_##T(T t){ \
    return all_type_names[T_id_##T];             \
}
map_to_all_types(___each_type_name_)
#undef ___each_type_name_

#define __get_function_of_type_name(T, ...), T : ___type_name_##T
#define type_name(_v)                                               \
    _Generic(typeof(_v),                                            \
                Variant: ___type_name_Variant,                      \
                Result: ___type_name_Result                         \
                map_to_all_types(__get_function_of_type_name))(_v)

//---------------------------------------------------------
// fumo type_id implementation
#define ___each_type_id_(T, ...)                \
static inline const T_id ___type_id_##T(T t){   \
    return T_id_##T;                            \
}
map_to_all_types(___each_type_id_) 
#undef ___each_type_id_

#define __get_function_of_type_id(T, ...), T : ___type_id_##T
#define get_type_id(var) (enum T_id)                             \
    _Generic(var                                                 \
             map_to_all_types(__get_function_of_type_id))(var)
