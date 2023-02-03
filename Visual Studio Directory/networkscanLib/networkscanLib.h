// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the NETWORKSCANLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// NETWORKSCANLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#pragma once

#ifdef NETWORKSCANLIB_EXPORTS
#define NETWORKSCANLIB_API __declspec(dllexport)
#else
#define NETWORKSCANLIB_API __declspec(dllimport)
#endif

extern "C" NETWORKSCANLIB_API int adder(int arg1, int arg2);