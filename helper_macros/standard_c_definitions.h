// clang-format off
#pragma once
#include <stdbool.h>
#include <wchar.h>

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
