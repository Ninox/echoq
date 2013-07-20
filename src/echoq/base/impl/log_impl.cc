/*=============================================================================
#     FileName: log_impl.cc
#         Desc: the async log implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-20 13:39:31
#      History:
=============================================================================*/
#include "log_impl.h"

#include "../utils.h"


namespace echoq   {
namespace base    {
namespace impl    {

      log_impl * log_impl::_impl = NULL;

      log_impl *
      log_impl::getImplement()      {
            if (log_impl::_impl == NULL)  {
                  log_impl::_impl = new log_impl();
            }
            return log_impl::_impl;
      }

      void
      log_impl::save()  {
      }

      void
      log_impl::exec()  {
      }

}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */
