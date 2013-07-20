/*=============================================================================
#     FileName: io_impl.cc
#         Desc: the async io writter implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-20 13:42:32
#      History:
=============================================================================*/
#include "io_impl.h"

#include "../utils.h"

namespace echoq   {
namespace base    {
namespace impl    {

      io_impl * io_impl::_impl = NULL;

      io_impl *
      io_impl::getImplement()      {
            if (io_impl::_impl == NULL)  {
                  io_impl::_impl = new io_impl();
            }
            return io_impl::_impl;
      }

      void
      io_impl::save()  {
      }

      void
      io_impl::exec()  {
      }


}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */
