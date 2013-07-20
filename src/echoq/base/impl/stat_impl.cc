/*=============================================================================
#     FileName: stat_impl.cc
#         Desc: the async status module implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-20 13:41:10
#      History:
=============================================================================*/
#include "stat_impl.h"

#include "../utils.h"

namespace echoq   {
namespace base    {
namespace impl    {

      stat_impl * stat_impl::_impl = NULL;

      stat_impl *
      stat_impl::getImplement()      {
            if (stat_impl::_impl == NULL)  {
                  stat_impl::_impl = new stat_impl();
            }
            return stat_impl::_impl;
      }

      void
      stat_impl::save()  {
      }

      void
      stat_impl::exec()  {
      }


}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */
