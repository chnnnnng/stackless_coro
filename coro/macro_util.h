#ifndef __FW_MACRO_UTIL_H
#define __FW_MACRO_UTIL_H


/**
 * 计算 __VA_ARGS__ 参数个数,最大支持64个参数
 * FL_ARG_COUNT(...)
*/
#define FL_ARG_COUNT(...) FL_INTERNAL_ARG_COUNT_PRIVATE(0, ##__VA_ARGS__,\
	64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0)
#define FL_INTERNAL_ARG_COUNT_PRIVATE(\
	 _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, _64, N, ...) N


/**
 * 参数拼接: FL_CONCAT(l, r)
*/
#define FL_CONCAT_(l, r) l ## r
#define FL_CONCAT(l, r) FL_CONCAT_(l, r)


/**
 *  FL_FOREACH(sepatator,fun,funarg,...)
 *  为动态参数 __VA_ARGS__ 每一个参数调用 fun 宏,最大支持64个参数
    sepatator 分隔符
    fun 函数宏
    funarg 函数宏的参数 
    例如：FL_FOREACH( || ， isSame , 3 , 1,2,3 ) 等效于 isSame(3,1) || isSame(3,2) || isSame(3,3)
    例如: FL_FOREACH( +  , square  ,   , 1,2,3)  等效于 square(1) + square(2) + square(3)
    例如：FL_FOREACH( ;  , USING   , NODE_ , 1,2,3 ) 等效于 USING(NODE_1); USING(NODE_2); USING(NODE_3)
*/
#define FL_DOARG0(s,f,a,o)
#define FL_DOARG1(s,f,a,v,...) f(a##v)
#define FL_DOARG2(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG1(s,f,a,__VA_ARGS__)
#define FL_DOARG3(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG2(s,f,a,__VA_ARGS__)
#define FL_DOARG4(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG3(s,f,a,__VA_ARGS__)
#define FL_DOARG5(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG4(s,f,a,__VA_ARGS__)
#define FL_DOARG6(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG5(s,f,a,__VA_ARGS__)
#define FL_DOARG7(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG6(s,f,a,__VA_ARGS__)
#define FL_DOARG8(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG7(s,f,a,__VA_ARGS__)
#define FL_DOARG9(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG8(s,f,a,__VA_ARGS__)
#define FL_DOARG10(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG9(s,f,a,__VA_ARGS__)
#define FL_DOARG11(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG10(s,f,a,__VA_ARGS__)
#define FL_DOARG12(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG11(s,f,a,__VA_ARGS__)
#define FL_DOARG13(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG12(s,f,a,__VA_ARGS__)
#define FL_DOARG14(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG13(s,f,a,__VA_ARGS__)
#define FL_DOARG15(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG14(s,f,a,__VA_ARGS__)
#define FL_DOARG16(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG15(s,f,a,__VA_ARGS__)
#define FL_DOARG17(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG16(s,f,a,__VA_ARGS__)
#define FL_DOARG18(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG17(s,f,a,__VA_ARGS__)
#define FL_DOARG19(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG18(s,f,a,__VA_ARGS__)
#define FL_DOARG20(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG19(s,f,a,__VA_ARGS__)
#define FL_DOARG21(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG20(s,f,a,__VA_ARGS__)
#define FL_DOARG22(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG21(s,f,a,__VA_ARGS__)
#define FL_DOARG23(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG22(s,f,a,__VA_ARGS__)
#define FL_DOARG24(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG23(s,f,a,__VA_ARGS__)
#define FL_DOARG25(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG24(s,f,a,__VA_ARGS__)
#define FL_DOARG26(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG25(s,f,a,__VA_ARGS__)
#define FL_DOARG27(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG26(s,f,a,__VA_ARGS__)
#define FL_DOARG28(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG27(s,f,a,__VA_ARGS__)
#define FL_DOARG29(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG28(s,f,a,__VA_ARGS__)
#define FL_DOARG30(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG29(s,f,a,__VA_ARGS__)
#define FL_DOARG31(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG30(s,f,a,__VA_ARGS__)
#define FL_DOARG32(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG31(s,f,a,__VA_ARGS__)
#define FL_DOARG33(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG32(s,f,a,__VA_ARGS__)
#define FL_DOARG34(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG33(s,f,a,__VA_ARGS__)
#define FL_DOARG35(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG34(s,f,a,__VA_ARGS__)
#define FL_DOARG36(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG35(s,f,a,__VA_ARGS__)
#define FL_DOARG37(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG36(s,f,a,__VA_ARGS__)
#define FL_DOARG38(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG37(s,f,a,__VA_ARGS__)
#define FL_DOARG39(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG38(s,f,a,__VA_ARGS__)
#define FL_DOARG40(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG39(s,f,a,__VA_ARGS__)
#define FL_DOARG41(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG40(s,f,a,__VA_ARGS__)
#define FL_DOARG42(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG41(s,f,a,__VA_ARGS__)
#define FL_DOARG43(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG42(s,f,a,__VA_ARGS__)
#define FL_DOARG44(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG43(s,f,a,__VA_ARGS__)
#define FL_DOARG45(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG44(s,f,a,__VA_ARGS__)
#define FL_DOARG46(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG45(s,f,a,__VA_ARGS__)
#define FL_DOARG47(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG46(s,f,a,__VA_ARGS__)
#define FL_DOARG48(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG47(s,f,a,__VA_ARGS__)
#define FL_DOARG49(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG48(s,f,a,__VA_ARGS__)
#define FL_DOARG50(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG49(s,f,a,__VA_ARGS__)
#define FL_DOARG51(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG50(s,f,a,__VA_ARGS__)
#define FL_DOARG52(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG51(s,f,a,__VA_ARGS__)
#define FL_DOARG53(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG52(s,f,a,__VA_ARGS__)
#define FL_DOARG54(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG53(s,f,a,__VA_ARGS__)
#define FL_DOARG55(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG54(s,f,a,__VA_ARGS__)
#define FL_DOARG56(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG55(s,f,a,__VA_ARGS__)
#define FL_DOARG57(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG56(s,f,a,__VA_ARGS__)
#define FL_DOARG58(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG57(s,f,a,__VA_ARGS__)
#define FL_DOARG59(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG58(s,f,a,__VA_ARGS__)
#define FL_DOARG60(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG59(s,f,a,__VA_ARGS__)
#define FL_DOARG61(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG60(s,f,a,__VA_ARGS__)
#define FL_DOARG62(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG61(s,f,a,__VA_ARGS__)
#define FL_DOARG63(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG62(s,f,a,__VA_ARGS__)
#define FL_DOARG64(s,f,a,v,...) FL_DOARG1(s,f,a,v) s FL_DOARG63(s,f,a,__VA_ARGS__)

#define FL_FOREACH_(sepatator,fun,funarg,...) \
		FL_CONCAT(FL_DOARG,FL_ARG_COUNT(__VA_ARGS__))(sepatator,fun,funarg,__VA_ARGS__)
#define FL_FOREACH(sepatator,fun,funarg,...) \
		FL_FOREACH_(sepatator,fun,funarg,__VA_ARGS__)



#endif
