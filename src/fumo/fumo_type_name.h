#pragma once
#include "fumo_c_definitions.h" // IWYU pragma: export
#include "fumo_data_structures.h" // IWYU pragma: export

/// fumo type_name implementation
// clang-format off
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

#define TypeName(Type, ...) #Type,
const char* all_type_names[] = {all_user_types_v(TypeName) //
                                ALL_DATA_TYPES(TypeName)};
#undef TypeName

static inline T_id ___type_id_Variant(Variant variant) {
    return variant.type_id;
}

static inline T_id ___type_id_Result(Result result) {
    return result.type_id;
}

static inline const char* ___type_name_Variant(Variant variant) {
    return all_type_names[variant.type_id];
}

static inline const char* ___type_name_Result(Result result) {
    return all_type_names[result.type_id];
}

#define ___each_type_name_(T, ...)                    \
static inline const char* ___type_name_##T(T t){ \
return all_type_names[T_id_##T];                 \
}
all_user_types_v(___each_type_name_)

all_data_types_v(___each_type_name_)

#undef ___each_type_name_

#define ___each_type_id_(T, ...)              \
static inline T_id ___type_id_##T(T t){  \
    return T_id_##T;                     \
}
all_user_types_v(___each_type_id_) all_data_types_v(___each_type_id_)

static inline T_id __type_unregistered_id(void) {return T_UNREGISTERED;}

#undef ___each_type_id_

#define __get_function_of_type_name(T, ...), T : ___type_name_##T

#define type_name(_v)                                               \
    _Generic(typeof(_v),                                            \
                Variant: ___type_name_Variant,                      \
                Result: ___type_name_Result                         \
                all_data_types_v(__get_function_of_type_name)       \
                all_user_types_v(__get_function_of_type_name))(_v)

#define __get_function_of_type_id(T, ...), T : ___type_id_##T

#define get_type_id(var) (enum T_id)                             \
    _Generic(var                                                 \
             all_user_types_v(__get_function_of_type_id)        \
             all_data_types_v(__get_function_of_type_id))(var)

//---------------------------------------------------------
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

#define PRINTF(fmt, X)          \
printf("%s", fmt);              \
printf( PRINTF_FORMAT( X ), X );\
printf("\n");

// #define autofree __attribute__((__cleanup__(autofree_impl)))
// static inline void autofree_impl(void* p) {
//     free(*((void**)p));
// }
