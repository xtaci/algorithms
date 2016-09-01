#ifndef ALGO_ALGVS_H__
#define ALGO_ALGVS_H__
#ifdef _MSC_VER

#define _CRT_SECURE_NO_WARNINGS

#define __func__ __FUNCTION__

#define strtok_r strtok_s

#if _MSC_VER <= 1800
#define ALG_VLA_NOT_SUPPORTED
#endif

#define typeof decltype

#endif//_MSC_VER
#endif//ALGO_ALGVS_H__