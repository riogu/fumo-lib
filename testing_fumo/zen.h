/**

	@file		zen.h
	@brief		C preprocessor utilities
	@author		madmurphy
	@copyright	GNU Public License v3
	@date		2018
	@see		Source code at https://github.com/madmurphy/zen.h

**/



/*  PRIVATE ENVIRONMENT  */


/*  Abstract utilities */

#define __ZEN_REDIRECT__(CALLBACK, ...) CALLBACK(__VA_ARGS__)
#define __ZEN_STRINGIFY__(ARG) #ARG

#define __ZEN_TRIM32__(X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, \
	X17, X18, X19, X20, X21, X22, X23, X24, X25, X26, X27, X28, X29, X30, X31, X32, ...) \
	X1, X2, X3, X4, X5, X6, X7, X8, X9, X10, X11, X12, X13, X14, X15, X16, \
	X17, X18, X19, X20, X21, X22, X23, X24, X25, X26, X27, X28, X29, X30, X31, X32


/*  Reverse binary and hexadecimal literals  */

#define __ZEN_HEX_0__ 0, 0, 0, 0
#define __ZEN_HEX_1__ 1, 0, 0, 0
#define __ZEN_HEX_2__ 0, 1, 0, 0
#define __ZEN_HEX_3__ 1, 1, 0, 0
#define __ZEN_HEX_4__ 0, 0, 1, 0
#define __ZEN_HEX_5__ 1, 0, 1, 0
#define __ZEN_HEX_6__ 0, 1, 1, 0
#define __ZEN_HEX_7__ 1, 1, 1, 0
#define __ZEN_HEX_8__ 0, 0, 0, 1
#define __ZEN_HEX_9__ 1, 0, 0, 1
#define __ZEN_HEX_A__ 0, 1, 0, 1
#define __ZEN_HEX_B__ 1, 1, 0, 1
#define __ZEN_HEX_C__ 0, 0, 1, 1
#define __ZEN_HEX_D__ 1, 0, 1, 1
#define __ZEN_HEX_E__ 0, 1, 1, 1
#define __ZEN_HEX_F__ 1, 1, 1, 1

#define __ZEN_BIN_0000__ 0
#define __ZEN_BIN_1000__ 1
#define __ZEN_BIN_0100__ 2
#define __ZEN_BIN_1100__ 3
#define __ZEN_BIN_0010__ 4
#define __ZEN_BIN_1010__ 5
#define __ZEN_BIN_0110__ 6
#define __ZEN_BIN_1110__ 7
#define __ZEN_BIN_0001__ 8
#define __ZEN_BIN_1001__ 9
#define __ZEN_BIN_0101__ A
#define __ZEN_BIN_1101__ B
#define __ZEN_BIN_0011__ C
#define __ZEN_BIN_1011__ D
#define __ZEN_BIN_0111__ E
#define __ZEN_BIN_1111__ F


/*  Increment macros  */

#define __ZEN_ADD_TO_0__(BITPOS) __ZEN_NON_OVERFLOW__
#define __ZEN_ADD_TO_1__(BITPOS) __ZEN_BIT_##BITPOS##_OVERFLOW__
#define __ZEN_INCREASE_BIT__(BITPOS, BITVAL) __ZEN_ADD_TO_##BITVAL##__(BITPOS)

#define __ZEN_NON_OVERFLOW__(...) 1, __VA_ARGS__ ,
#define __ZEN_BIT_2_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(3, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_3_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(4, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_4_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(5, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_5_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(6, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_6_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(7, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_7_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(8, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_8_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(9, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_9_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(10, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_10_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(11, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_11_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(12, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_12_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(13, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_13_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(14, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_14_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(15, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_15_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(16, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_16_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(17, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_17_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(18, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_18_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(19, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_19_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(20, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_20_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(21, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_21_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(22, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_22_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(23, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_23_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(24, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_24_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(25, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_25_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(26, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_26_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(27, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_27_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(28, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_28_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(29, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_29_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(30, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_30_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(31, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_31_OVERFLOW__(BITVAL, ...) 0, __ZEN_INCREASE_BIT__(32, BITVAL)(__VA_ARGS__)
#define __ZEN_BIT_32_OVERFLOW__(BITVAL, ...) 0, 0,


/*  Initialize increment  */

#define __ZEN_PLUS_ONE__(FIRSTBIT, ...) __ZEN_INCREASE_BIT__(2, FIRSTBIT)(__VA_ARGS__) 0


/*  Concat utilities  */

#define __ZEN_MAKE_NIBBLE__(BIT1, BIT2, BIT3, BIT4) __ZEN_BIN_##BIT4##BIT3##BIT2##BIT1##__

#define __ZEN_HEX_MAKE_ID__(PREFIX, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7, HEX8) \
	PREFIX##HEX1##HEX2##HEX3##HEX4##HEX5##HEX6##HEX7##HEX8

#define __ZEN_COUNTER_MAKE_ID__(PREFIX, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15, B16, \
	B17, B18, B19, B20, B21, B22, B23, B24, B25, B26, B27, B28, B29, B30, B31, B32) \
	__ZEN_REDIRECT__(__ZEN_HEX_MAKE_ID__, PREFIX, __ZEN_MAKE_NIBBLE__(B32, B31, B30, B29), \
	__ZEN_MAKE_NIBBLE__(B28, B27, B26, B25), __ZEN_MAKE_NIBBLE__(B24, B23, B22, B21), \
	__ZEN_MAKE_NIBBLE__(B20, B19, B18, B17), __ZEN_MAKE_NIBBLE__(B16, B15, B14, B13), \
	__ZEN_MAKE_NIBBLE__(B12, B11, B10, B9), __ZEN_MAKE_NIBBLE__(B8, B7, B6, B5), \
	__ZEN_MAKE_NIBBLE__(B4, B3, B2, B1))



/*  PUBLIC ENVIRONMENT  */


/*  Creates a new zen counter set to a given value  */
#define ZEN_COUNTER_PARSE_HEX(HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7, HEX8) __ZEN_HEX_##HEX8##__, __ZEN_HEX_##HEX7##__, __ZEN_HEX_##HEX6##__, __ZEN_HEX_##HEX5##__, __ZEN_HEX_##HEX4##__, __ZEN_HEX_##HEX3##__, __ZEN_HEX_##HEX2##__, __ZEN_HEX_##HEX1##__

/*  Returns a new zen counter set to zero  */
#define ZEN_COUNTER_NEW() ZEN_COUNTER_PARSE_HEX(0, 0, 0, 0, 0, 0, 0, 0)

/*  Returns a new zen counter that equals the zen counter passed as argument plus one  */
#define ZEN_COUNTER_NEXT(COUNTER) __ZEN_REDIRECT__(__ZEN_TRIM32__, __ZEN_REDIRECT__(__ZEN_PLUS_ONE__, COUNTER))

/*  Converts a zen counter to a literal unsigned integer  */
#define ZEN_COUNTER_AS_NUMBER(COUNTER) __ZEN_COUNTER_MAKE_ID__(0x, COUNTER)

/*  Concatenates a zen counter to an identifier  */
#define ZEN_COUNTER_AS_IDENTIFIER(COUNTER, PREFIX) __ZEN_COUNTER_MAKE_ID__(PREFIX, COUNTER)

/*  Converts a zen counter to a hexadecimal string  */
#define ZEN_COUNTER_AS_HEX_STRING(COUNTER) __ZEN_REDIRECT__(__ZEN_STRINGIFY__, __ZEN_COUNTER_MAKE_ID__(, COUNTER))


/*  EOF  */

