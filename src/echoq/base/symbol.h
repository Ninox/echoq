/*=============================================================================
#     FileName: symbol.h
#         Desc: the symbol macros define here.
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-14 10:30:43
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_SYMBOL_H
#define ECHOQ_BASE_SYMBOL_H


//    the limit of echoq
//--------------------------------
#define EQ_MAX_CONTENT_SIZE   2097152     // 2MB Content data Per Protocol
#define EQ_HEADER_LENGTH      36          // **DO NOT** change it

#if !defined(EQ_WORKER_LIMIT) || EQ_WORKER_LIMIT < 512      // at least 512 worker
      #define EQ_WORKER_LIMIT 0
#endif

//    The platform declare
//-------------------------------
#define EQ_OS_UNKNOW    0x00  // OS declare here
#define EQ_OS_WINDOWS   0x01
#define EQ_OS_LINUX     0x02
#define EQ_OS_BSD       0x03

#define EQ_RUNNING_OS   EQ_OS_UNKNOW

#define EQ_BUILD_UNKNOW 0x00  // build tools declare  
#define EQ_BUILD_MSVC   0x01
#define EQ_BUILD_GCC    0x02
#define EQ_BUILD_CLANG  0x03
#define EQ_BUILD_CYGWIN 0x04

#define EQ_BUILDTOOLS   EQ_BUILD_UNKNOW

#if defined(__WIN32) || defined(WIN32)
      #undef      EQ_RUNNING_OS
      #define     EQ_RUNNING_OS     EQ_OS_WINDOWS
#endif

// more platforms will supported...

#endif /* end of include guard: ECHOQ_BASE_SYMBOL_H */

