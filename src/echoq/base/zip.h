/*=============================================================================
#     FileName: zip.h
#         Desc: a zlib helper for message content comrpess
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-16 22:04:56
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_ZIP_H
#define ECHOQ_BASE_ZIP_H

#include <boost/smart_ptr.hpp>

namespace echoq   {
namespace base    {
      
      typedef boost::shared_array<char> refBuffer_t;

      refBuffer_t zip_compress(const char * src, size_t src_sz, size_t * dest_sz);
      refBuffer_t zip_uncompress(const char *src, size_t src_sz, size_t * dest_sz);

}     /*    end of base    */
}     /*    end of echoq    */


#endif /* end of include guard: ECHOQ_BASE_ZIP_H */

