/*=============================================================================
#     FileName: log_impl.h
#         Desc: the async log implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-20 10:17:16
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_IMPL_LOG_H
#define ECHOQ_BASE_IMPL_LOG_H

#include <string>

#include <boost/noncopyable.hpp>

namespace echoq   {
namespace base    {
namespace impl    {

      class log_impl: public boost::noncopyable
      {
      public:
            static log_impl * getImplement();

            void save();
            void exec(const std::string & data);
      
      private:
            static log_impl *  _impl;
      };

}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */


#endif /* end of include guard: ECHOQ_BASE_IMPL_LOG_H */

