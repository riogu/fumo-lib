#pragma once
#include "../structs.h" // IWYU pragma: export
#include "fumo/for_each_macro.h"
#include <stdbool.h>
#include <wchar.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
// #pragma clang diagnostic ignored "-Waddress-of-packed-member"
// NOTE: this might cause insanely hard to find undebuggable issues

// clang-format off
typedef  signed char        signed_char        ;
typedef  unsigned char      unsigned_char      ;
typedef  long long          long_long          ; 
typedef  unsigned short     unsigned_short     ; 
typedef  unsigned int       unsigned_int       ; 
typedef  unsigned long      unsigned_long      ; 
typedef  unsigned long long unsigned_long_long ; 
typedef  long double        long_double        ; 
typedef  char*              char_ptr           ; 
typedef  char const*        char_const_ptr     ; 
typedef  wchar_t*           wchar_t_ptr        ; 
typedef  wchar_t const*     wchar_t_const_ptr  ; 
typedef  void*              void_ptr           ; 
typedef  void const*        void_const_ptr     ;
// clang-format on

#define all_data_types_v(F, ...)         \
    F(_Bool             , __VA_ARGS__)   \
    F(char              , __VA_ARGS__)   \
    F(signed_char       , __VA_ARGS__)   \
    F(unsigned_char     , __VA_ARGS__)   \
    F(short             , __VA_ARGS__)   \
    F(int               , __VA_ARGS__)   \
    F(long              , __VA_ARGS__)   \
    F(long_long         , __VA_ARGS__)   \
    F(unsigned_short    , __VA_ARGS__)   \
    F(unsigned_int      , __VA_ARGS__)   \
    F(unsigned_long     , __VA_ARGS__)   \
    F(unsigned_long_long, __VA_ARGS__)   \
    F(float             , __VA_ARGS__)   \
    F(double            , __VA_ARGS__)   \
    F(long_double       , __VA_ARGS__)   \
    F(char_ptr          , __VA_ARGS__)   \
    F(char_const_ptr    , __VA_ARGS__)   \
    F(wchar_t_ptr       , __VA_ARGS__)   \
    F(wchar_t_const_ptr , __VA_ARGS__)   \
    F(void_ptr          , __VA_ARGS__)   \
    F(void_const_ptr    , __VA_ARGS__)
// ----------------------------------------------------------------

// #define user_inputed_types Position, Shape, Body, Rectangle
// #define map_types(T) F(T, __VA_ARGS__)
// #define all_types_with_v(F, ptr, ...)           \
//     FOR_EACH(map_types, user_inputed_types)
//
#define all_types_with_v(F, ptr, ...)                    \
    F(Position##ptr,             __VA_ARGS__)            \
    F(Shape##ptr,                __VA_ARGS__)            \
    F(Body##ptr,                 __VA_ARGS__)            \
    F(Rectangle##ptr,            __VA_ARGS__)

#define all_user_types_v(F, ...)                     \
    all_types_with_v(F,       ,   __VA_ARGS__)       \
    all_types_with_v(F, _ptr,     __VA_ARGS__)       \
    all_types_with_v(F, _ptr_ptr, __VA_ARGS__)

#define typedefs_user_types_ptr(T, ...) typedef T* T##_ptr;
all_user_types_v(typedefs_user_types_ptr);
#undef typedefs_user_types_ptr

//---------------------------------------------------------
#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto
static bool ___inner_fumo_cookie___ = false;

static inline bool ___check_and_reset_cookie___() {
    return !(!___inner_fumo_cookie___ || (___inner_fumo_cookie___ = false));
}

//---------------------------------------------------------
// NOTE: fumo_c syntax and useful operator definitions

#define _UNDERLYING_VALUE(T, Variant)                        \
case T_id_##T:                                               \
    (void)0;                                                 \
    typeof(Variant.value._##T) val_##T = Variant.value._##T; \
    result = &val_##T;                                       \
    break;

#define get_if(T, Variant) (T*) ({                      \
    auto result = NULL;                                 \
    switch (Variant.type_id) {                          \
        all_user_types_v(_UNDERLYING_VALUE,Variant) \
        all_data_types_v(_UNDERLYING_VALUE, Variant)   \
    }                                                   \
    result;                                             \
}); if ((get_type_id((T){}) == Variant.type_id))

//---------------------------------------------------------

#define case(T, varname) break;}); case T_id_##T: ({ T* varname = &____value____->value._##T;

#define match(Variant)                                              \
({                                                                  \
    let __inner_ = Variant;                                         \
    let ____value____ = &__inner_;                                  \
    switch(__inner_.type_id) { /* switch gets closed by case labels later */

#define _default                                    \
    });                                             \
        /*finish previous case statement*/          \
        default: {                                  \
            extern bool ___inner_fumo_cookie___;    \
            ___inner_fumo_cookie___++;              \
            break;                                  \
        }                                           \
    }                                               \
    if(___check_and_reset_cookie___())  /* start user code block */

#define _Ok(T, _varname)                                        \
    });                                                         \
    default:                                                    \
        break;                                                  \
    }                                                           \
({                                                              \
    T* _varname = &____value____->value._##T;                    \
    if(!____value____->was_err                                  \
            && (get_type_id((T){}) == ____value____->type_id))

#define _Err(T, _varname)                                       \
});                                                             \
    let _varname = &____value____->value._##T;                  \
    if (____value____->was_err                                  \
        && (get_type_id((T){}) == ____value____->type_id))

//---------------------------------------------------------
//---------------------------------------------------------
// type comparison macro

#define _IS_SAME_TYPE(T, U) _Generic(typeof(T), typeof(U): 1, default: 0)

#define is_same_t(X, Y)                                                  \
    (({                                                                  \
         let is_x_v = _Generic(typeof(X), Variant: 1, default: 0);       \
         let is_y_v = _Generic(typeof(Y), Variant: 1, default: 0);       \
         let is_same_t =                                                 \
            (is_x_v && is_y_v)                                           \
            ? ( (*(Variant*)&X).type_id == (*(Variant*)&Y).type_id )     \
            : (is_x_v && !is_y_v)                                        \
            ? ( (*(Variant*)&X).type_id == get_type_id(typeof(Y)) )      \
            : (!is_x_v && is_y_v)                                        \
            ? ( get_type_id(typeof(X)) == (*(Variant*)&Y).type_id )      \
            : (!is_x_v && !is_y_v)                                       \
            ? ( _IS_SAME_TYPE(X, Y) )                                    \
            : 0;                                                         \
        is_same_t;                                                       \
    }))
