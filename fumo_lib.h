#pragma once
#include <stdbool.h>
#include <wchar.h>
// map-macro implementation is from:
// https://github.com/swansontec/map-macro

/*
 * map-macro by William R Swanson is marked with CC0 1.0 Universal.
 *
 * To view a copy of this license,
 * visit https://creativecommons.org/publicdomain/zero/1.0/
 */

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL5(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL(...)  EVAL5(__VA_ARGS__)
#define MAP_END(...)
#define MAP_OUT
#define EMPTY() 
#define DEFER(id) id EMPTY()
#define MAP_GET_END2() 0, MAP_END
#define MAP_GET_END1(...) MAP_GET_END2
#define MAP_GET_END(...) MAP_GET_END1
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) DEFER ( MAP_NEXT0 ) ( test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1(MAP_GET_END test, next)
#define MAP_INC(X) MAP_INC_ ## X
#define MAP0(f, x, peek, ...) f(x) DEFER ( MAP_NEXT(peek, MAP1) ) ( f, peek, __VA_ARGS__ ) 
#define MAP1(f, x, peek, ...) f(x) DEFER ( MAP_NEXT(peek, MAP0) ) ( f, peek, __VA_ARGS__ )
#define MAP0_UD(f, userdata, x, peek, ...) f(x,userdata) DEFER ( MAP_NEXT(peek, MAP1_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 
#define MAP1_UD(f, userdata, x, peek, ...) f(x,userdata) DEFER ( MAP_NEXT(peek, MAP0_UD) ) ( f, userdata, peek, __VA_ARGS__ ) 
#define MAP0_UD_I(f, userdata, index, x, peek, ...) f(x,userdata,index) DEFER ( MAP_NEXT(peek, MAP1_UD_I) ) ( f, userdata, MAP_INC(index), peek, __VA_ARGS__ ) 
#define MAP1_UD_I(f, userdata, index, x, peek, ...) f(x,userdata,index) DEFER ( MAP_NEXT(peek, MAP0_UD_I) ) ( f, userdata, MAP_INC(index), peek, __VA_ARGS__ ) 
#define MAP_LIST0(f, x, peek, ...) , f(x) DEFER ( MAP_NEXT(peek, MAP_LIST1) ) ( f, peek, __VA_ARGS__ ) 
#define MAP_LIST1(f, x, peek, ...) , f(x) DEFER ( MAP_NEXT(peek, MAP_LIST0) ) ( f, peek, __VA_ARGS__ ) 
#define MAP_LIST2(f, x, peek, ...)   f(x) DEFER ( MAP_NEXT(peek, MAP_LIST1) ) ( f, peek, __VA_ARGS__ ) 

#define MAP(f, ...) EVAL(MAP1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_LIST(f, ...) EVAL(MAP_LIST2(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
#define MAP_UD(f, userdata, ...) EVAL(MAP1_UD(f, userdata, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

#define standard_c_types                \
    _Bool                  ,            \
    char                   ,            \
    signed_char            ,            \
    unsigned_char          ,            \
    short                  ,            \
    int                    ,            \
    long                   ,            \
    long_long              ,            \
    unsigned_short         ,            \
    unsigned_int           ,            \
    unsigned_long          ,            \
    unsigned_long_long     ,            \
    float                  ,            \
    double                 ,            \
    long_double            ,            \
    char_const_ptr         ,            \
    void_ptr               ,            \
    void_const_ptr                     

// we must typedef standard c types as a single identifier for internal usage.
// it is theoretically possible to not provide special handling for these,
// but the main issue lies with the fact that these types have more than one identifier.
// for example "long long" is hard to distinguish from 2 separate calls to a long.
// for this reason, these types have special handling so we can add them
// in a generic way to the fumo type system.
typedef  signed char         signed_char            ;
typedef  unsigned char       unsigned_char          ;
typedef  long long           long_long              ; 
typedef  unsigned short      unsigned_short         ; 
typedef  unsigned int        unsigned_int           ; 
typedef  unsigned long       unsigned_long          ; 
typedef  unsigned long long  unsigned_long_long     ; 
typedef  long double         long_double            ; 

typedef  _Bool              *bool_ptr               ; 
typedef  signed_char        *signed_char_ptr        ; 
typedef  unsigned_char      *unsigned_char_ptr      ; 
typedef  short              *short_ptr              ; 
typedef  int                *int_ptr                ; 
typedef  long               *long_ptr               ;
typedef  long_long          *long_long_ptr          ;
typedef  unsigned_short     *unsigned_short_ptr     ;
typedef  unsigned_int       *unsigned_int_ptr       ;
typedef  unsigned_long      *unsigned_long_ptr      ;
typedef  unsigned_long_long *unsigned_long_long_ptr ;
typedef  long_double        *long_double_ptr        ;
typedef  float              *float_ptr              ;
typedef  double             *double_ptr             ;
typedef  long_double        *long_double_ptr        ;

typedef  char*              char_ptr                ; 
typedef  char const*        char_const_ptr          ; 
typedef  wchar_t*           wchar_t_ptr             ; 
typedef  wchar_t const*     wchar_t_const_ptr       ; 
typedef  void*              void_ptr                ; 
typedef  void const*        void_const_ptr          ;

// NOTE: due to conversions between wchar and char and other reasons
// they arent included in some of the pointer definitions

//---------------------------------------------------------
// small helpful printf utility macro
#include <stdio.h> // IWYU pragma: export
#define PRINTF_FORMAT(T)                       \
  _Generic( T,                                 \
    _Bool             : "%d",                  \
    char              : "%c",                  \
    signed char       : "%hhd",                \
    unsigned char     : "%hhu",                \
    short             : "%hd",                 \
    int               : "%d",                  \
    long              : "%ld",                 \
    long long         : "%lld",                \
    unsigned short    : "%hu",                 \
    unsigned int      : "%u",                  \
    unsigned long     : "%lu",                 \
    unsigned long long: "%llu",                \
    float             : "%f",                  \
    double            : "%f",                  \
    long double       : "%Lf",                 \
    char*             : "%s",                  \
    char const*       : "%s",                  \
    wchar_t*          : "%ls",                 \
    wchar_t const*    : "%ls",                 \
    void*             : "%p",                  \
    void const*       : "%p",                  \
    default           : "Type not defined. %p" \
  )

#define print(fmt, X)           \
printf("%s", fmt);              \
printf( PRINTF_FORMAT( X ), X );\
printf("\n");

// ----------------------------------------------------------------
// fumo_lib implementation starts here
// ----------------------------------------------------------------
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
}); if ((get_type_id((T){0}) == Variant.type_id))

//---------------------------------------------------------

#define match(Variant)                                  \
{                                                       \
    let __inner_ = Variant;                             \
    let _value_ = &__inner_;

#define holds(T, varname)                               \
}                                                       \
{                                                       \
    let varname = (T*)&_value_->value;                  \
    bool temp = _value_->___inner_cookie___;            \
    if(get_type_id((T){0}) == _value_->type_id) {        \
        _value_->___inner_cookie___ = true;             \
    }                                                   \
    if (!temp && _value_->___inner_cookie___)

#define _                                               \
}                                                       \
    if(!_value_->___inner_cookie___)

#define _Ok(T, _varname)                                \
}                                                       \
{                                                       \
    let _varname = (T*) &_value_->value;                \
    if (!_value_->was_err                               \
        && (get_type_id((T){0}) == _value_->type_id))

#define _Err(T, _varname)                               \
}                                                       \
    let _varname = (T*) &_value_->value;                \
    if (_value_->was_err                                \
        && (get_type_id((T){0}) == _value_->type_id))

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
    bool ___inner_cookie___; 
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
