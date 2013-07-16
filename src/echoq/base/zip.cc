/*=============================================================================
#     FileName: fastlog.cc
#         Desc: faset async logger implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-07 23:39:10
#      History:
=============================================================================*/
#include "zip.h"
#include "symbol.h"
#include "assert.h"

#include <zlib.h>

using namespace boost;

namespace echoq   {
namespace base    {

      refBuffer_t zip_compress(const char * src, size_t src_sz, size_t & dest_sz, bool & ok)   {
            // NOTE: the compress buffer must less than 
            //       echoq's protocol content size limitation
            ECHOQ_ASSERT(src == NULL, "cannot use a NULL source");

            refBuffer_t buffer(NULL);
            if ( src_sz > EQ_MAX_CONTENT_SIZE)      {
                  ok = false;
                  dest_sz = 0;
                  return buffer;
            }
            buffer.reset((char*)malloc(src_sz));
            int err = compress(buffer.get(), &dest_sz, src, src_sz);
            if (err == Z_OK)  {
                  ok = true;
            } else      {
                  dest_sz = 0;
                  ok = false;
                  buffer.reset(NULL);
            }
            return buffer;
      }

      refBuffer_t zip_uncompress(const char * src, size_t src_sz, size_t & targetSZ, bool & ok) {
            // NOTE:
            //       you must get the uncompress size before call this function.
            //       the parameter 'targetSZ' is the original size (uncompress size)
            ECHOQ_ASSERT(src == NULL, "cannot use a NULL source");

            refBuffer_t buffer(NULL);
            if (targetSZ == 0)      {
                  ok = false;
                  return buffer;
            }
            buffer.reset((char*)malloc(targetSZ));
            int err = uncompress(buffer.get(), &targetSZ, src, src_sz);
            if (err == Z_OK)  {
                  ok = true;
            } else      {
                  targetSZ = 0;
                  ok = false;
                  buffer.reset(NULL);
            }
            return buffer;
      }

}     /*    end of base    */
}     /*    end of echoq    */
