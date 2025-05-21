#pragma once
#include <stdbool.h>
#include <wchar.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
#pragma clang diagnostic ignored "-Waddress-of-packed-member"
// NOTE: this might cause insanely hard to find undebuggable issues

#define __split(e) e
#define ALL_DATA_TYPES_VARIABLE(E, F, ...)                            \
    _Bool              __split(E)F##_Bool               __VA_ARGS__   \
    char               __split(E)F##char                __VA_ARGS__   \
    signed char        __split(E)F##signed_char         __VA_ARGS__   \
    unsigned char      __split(E)F##unsigned_char       __VA_ARGS__   \
    short              __split(E)F##short               __VA_ARGS__   \
    int                __split(E)F##int                 __VA_ARGS__   \
    long               __split(E)F##long                __VA_ARGS__   \
    long long          __split(E)F##long_long           __VA_ARGS__   \
    unsigned short     __split(E)F##unsigned_short      __VA_ARGS__   \
    unsigned int       __split(E)F##unsigned_int        __VA_ARGS__   \
    unsigned long      __split(E)F##unsigned_long       __VA_ARGS__   \
    unsigned long long __split(E)F##unsigned_long_long  __VA_ARGS__   \
    float              __split(E)F##float               __VA_ARGS__   \
    double             __split(E)F##double              __VA_ARGS__   \
    long double        __split(E)F##long_double         __VA_ARGS__   \
    char*              __split(E)F##char_ptr            __VA_ARGS__   \
    char const*        __split(E)F##char_const_ptr      __VA_ARGS__   \
    wchar_t*           __split(E)F##wchar_t_ptr         __VA_ARGS__   \
    wchar_t const*     __split(E)F##wchar_t_const_ptr   __VA_ARGS__   \
    void*              __split(E)F##void_ptr            __VA_ARGS__   \
    void const*        __split(E)F##void_const_ptr      __VA_ARGS__

#define ALL_DATA_TYPES(F)    \
    F(_Bool              )   \
    F(char               )   \
    F(signed char        )   \
    F(unsigned char      )   \
    F(short              )   \
    F(int                )   \
    F(long               )   \
    F(long long          )   \
    F(unsigned short     )   \
    F(unsigned int       )   \
    F(unsigned long      )   \
    F(unsigned long long )   \
    F(float              )   \
    F(double             )   \
    F(long double        )   \
    F(char*              )   \
    F(char const*        )   \
    F(wchar_t*           )   \
    F(wchar_t const*     )   \
    F(void*              )   \
    F(void const*        )

#define ALL_DATA_TYPE_NAMES(F)   \
    F(_Bool             )       \
    F(char              )       \
    F(signed_char       )       \
    F(unsigned_char     )       \
    F(short             )       \
    F(int               )       \
    F(long              )       \
    F(long_long         )       \
    F(unsigned_short    )       \
    F(unsigned_int      )       \
    F(unsigned_long     )       \
    F(unsigned_long_long)       \
    F(float             )       \
    F(double            )       \
    F(long_double       )       \
    F(char_ptr          )       \
    F(char_const_ptr    )       \
    F(wchar_t_ptr       )       \
    F(wchar_t_const_ptr )       \
    F(void_ptr          )       \
    F(void_const_ptr    )

#define ALL_DATA_TYPES_V(F, Variant)  \
    F(_Bool             , Variant)   \
    F(char              , Variant)   \
    F(signed_char       , Variant)   \
    F(unsigned_char     , Variant)   \
    F(short             , Variant)   \
    F(int               , Variant)   \
    F(long              , Variant)   \
    F(long_long         , Variant)   \
    F(unsigned_short    , Variant)   \
    F(unsigned_int      , Variant)   \
    F(unsigned_long     , Variant)   \
    F(unsigned_long_long, Variant)   \
    F(float             , Variant)   \
    F(double            , Variant)   \
    F(long_double       , Variant)   \
    F(char_ptr          , Variant)   \
    F(char_const_ptr    , Variant)   \
    F(wchar_t_ptr       , Variant)   \
    F(wchar_t_const_ptr , Variant)   \
    F(void_ptr          , Variant)   \
    F(void_const_ptr    , Variant)
// ----------------------------------------------------------------

// clang-format off

typedef    _Bool              __Bool             ; 
typedef    char               _char              ; 
typedef    signed char        _signed_char       ; 
typedef    unsigned char      _unsigned_char     ; 
typedef    short              _short             ; 
typedef    int                _int               ; 
typedef    long               _long              ; 
typedef    long long          _long_long         ; 
typedef    unsigned short     _unsigned_short    ; 
typedef    unsigned int       _unsigned_int      ; 
typedef    unsigned long      _unsigned_long     ; 
typedef    unsigned long long _unsigned_long_long; 
typedef    float              _float             ; 
typedef    double             _double            ; 
typedef    long double        _long_double       ; 
typedef    char*              char_ptr          ; 
typedef    char const*        char_const_ptr    ; 
typedef    wchar_t*           wchar_t_ptr       ; 
typedef    wchar_t const*     wchar_t_const_ptr ; 
typedef    void*              void_ptr          ; 
typedef    void const*        void_const_ptr    ;

#define type_to_name(T)\
_Generic(typeof(*(T*)0),\
    _Bool             : __Bool               ,  \
    char              : _char                ,  \
    signed char       : _signed_char         ,  \
    unsigned char     : _unsigned_char       ,  \
    short             : _short               ,  \
    int               : _int                 ,  \
    long              : _long                ,  \
    long long         : _long_long           ,  \
    unsigned short    : _unsigned_short      ,  \
    unsigned int      : _unsigned_int        ,  \
    unsigned long     : _unsigned_long       ,  \
    unsigned long long: _unsigned_long_long  ,  \
    float             : _float               ,  \
    double            : _double              ,  \
    long double       : _long_double         ,  \
    char*             : _char_ptr            ,  \
    char const*       : _char_const_ptr      ,  \
    wchar_t*          : _wchar_t_ptr         ,  \
    wchar_t const*    : _wchar_t_const_ptr   ,  \
    void*             : _void_ptr            ,  \
    void const*       : _void_const_ptr)

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

#define T_UNREGISTERED -420
#define auto __auto_type
#define let auto

static bool ___inner_fumo_cookie___ = false;

static inline bool ___check_and_reset_cookie___() {
    return !(!___inner_fumo_cookie___ || (___inner_fumo_cookie___ = false));
}

//---------------------------------------------------------
//---------------------------------------------------------
// NOTE: fumo_c syntax and useful operator definitions

#define XMACRO1(Type) Type : T_id_##Type,
#define get_type_id(var) (enum T_id)            \
    _Generic(var,                                    \
             ALL_VARIANT_TYPES(XMACRO1)              \
             ALL_DATA_TYPES_VARIABLE(:, T_id_, ,)    \
            default: T_UNREGISTERED)

//---------------------------------------------------------

#define _UNDERLYING_VALUE(T, Variant)                        \
case T_id_##T:                                               \
    (void)0;                                                 \
    typeof(Variant.value._##T) val_##T = Variant.value._##T; \
    result = &val_##T;                                       \
    break;

#define get_if(T, Variant) (T*) ({                      \
    auto result = NULL;                                 \
    switch (Variant.type_id) {                          \
        ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant) \
        ALL_DATA_TYPES_V(_UNDERLYING_VALUE, Variant)    \
    }                                                   \
    result;                                             \
}); if ((get_type_id(*(T*)0) == Variant.type_id))

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
            && (get_type_id(*(T*)0) == ____value____->type_id))

#define _Err(T, _varname)                                       \
});                                                             \
    let _varname = &____value____->value._##T;                  \
    if (____value____->was_err                                  \
        && (get_type_id(*(T*)0) == ____value____->type_id))



#define __valuething                                                \
    auto ____value____ = (union T_value *)({                        \
        auto result = NULL;                                         \
        switch (Variant.type_id) {                                  \
            ALL_VARIANT_TYPES_V(_UNDERLYING_VALUE, Variant)         \
            ALL_DATA_TYPES_V(_UNDERLYING_VALUE, Variant)            \
        }                                                           \
        result;                                                     \
    });

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

//---------------------------------------------------------
// #define autofree __attribute__((__cleanup__(autofree_impl)))
// static inline void autofree_impl(void* p) {
//     free(*((void**)p));
// }
#include <stdio.h> // IWYU pragma: export
#define PRINTF_FORMAT(T)                       \
  _Generic( (T),                               \
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

#define PRINTF(X)  printf( PRINTF_FORMAT( (X) ), (X) )
