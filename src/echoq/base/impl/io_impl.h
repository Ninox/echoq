/*=============================================================================
#     FileName: io_impl.h
#         Desc: the async io implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.0.1
#   LastChange: 2013-07-20 10:17:01
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_IMPL_IO_H
#define ECHOQ_BASE_IMPL_IO_H

#include <string>

#include <boost/noncopyable.hpp>

namespace echoq   {
namespace base    {
namespace impl    {

      class io_impl: public boost::noncopyable
      {
      public:
            static io_impl *  getImplement();

            void save();
            void exec(const std::string & data);
      
      private:
            static io_impl *  _impl;
      };

}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */


#endif /* end of include guard: ECHOQ_BASE_IMPL_IO_H */

