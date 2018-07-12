//
// Created by shniu on 18-7-12.
//

#ifndef METACHAIN_HELLO_H
#define METACHAIN_HELLO_H
#if defined _WIN32
#if LIBHELLO_BUILD
#define LIBHELLO_API __declspec(dllexport)
#else
#define LIBHELLO_API __declspec(dllimport)
#endif
#else
#define LIBHELLO_API
#endif

LIBHELLO_API void hello(const char *name);

#endif //METACHAIN_HELLO_H
