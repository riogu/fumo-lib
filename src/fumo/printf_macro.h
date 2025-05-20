// clang-format off
#pragma  once
#include <stdio.h> // IWYU pragma: export
#define PRINTF_FORMAT(T)        \
  _Generic( (T),                \
    _Bool             : "%d",   \
    char              : "%c",   \
    signed char       : "%hhd", \
    unsigned char     : "%hhu", \
    short             : "%hd",  \
    int               : "%d",   \
    long              : "%ld",  \
    long long         : "%lld", \
    unsigned short    : "%hu",  \
    unsigned int      : "%u",   \
    unsigned long     : "%lu",  \
    unsigned long long: "%llu", \
    float             : "%f",   \
    double            : "%f",   \
    long double       : "%Lf",  \
    char*             : "%s",   \
    char const*       : "%s",   \
    wchar_t*          : "%ls",  \
    wchar_t const*    : "%ls",  \
    void*             : "%p",   \
    void const*       : "%p",    \
    default           : "Type not defined. %p" \
  )

#define PRINTF(X)  printf( PRINTF_FORMAT( (X) ), (X) )
// IWYU pragma: export
