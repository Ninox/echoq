/*=============================================================================
#     FileName: assert.h
#         Desc: a simple assert helper for echoq
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-07 23:38:25
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_ASSERT_H
#define ECHOQ_BASE_ASSERT_H

#include <stdio.h>

#include "echoqsymbol.h"

namespace echoq   {
namespace base    {

      void inline echoq_assert ( bool isAssert, const char * expr,
                          const char * filename, int line,
                          const char * message
                        )
      {
#if defined(ECHOQ_IS_DEBUG)
            if (isAssert) return;
            if (message)
                  pritnf("echoq assert happened!\nfile   :%s\nline   :%d\nexpr   :%s\nmessage:%s\n",
                         filename, line, expr, message);
            else
                  printf("echoq assert happened!\nfile   :%s\nline   :%d\nexpr   :%s\n",
                          filename, line, expr);
#endif
            abort();
      }

#define ECHOQ_ASSERT(boolExpr, info)      \
            echoq_assert(boolExpr, #boolExpr, __FILE__, __LINE__, info)

}     // end of base
}     // end of echoq

#endif /* end of include guard: ECHOQ_BASE_ASSERT_H */

