#pragma once
#define EXPAND1(...)      __VA_ARGS__
#define EXPAND2(...)        EXPAND1(    EXPAND1(  EXPAND1 (EXPAND1 (__VA_ARGS__))))
#define EXPAND3(...)        EXPAND2(    EXPAND2(  EXPAND2 (EXPAND2 (__VA_ARGS__))))
#define EXPAND(...)        EXPAND3(    EXPAND3(  EXPAND3 (EXPAND3 (__VA_ARGS__))))
// #define EXPAND(...)        EXPAND4(    EXPAND4(  EXPAND4 (EXPAND4 (__VA_ARGS__))))
// #define EXPAND6(...)        EXPAND5(    EXPAND5(  EXPAND5 (EXPAND5 (__VA_ARGS__))))
#define PARENS ()
#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
