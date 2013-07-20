/*=============================================================================
#     FileName: stat_impl.h
#         Desc: the async status recorder implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-20 10:17:30
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_IMPLE_STAT_H
#define ECHOQ_BASE_IMPLE_STAT_H

#include <string>

#include <boost/noncopyable.hpp>

namespace echoq   {
namespace base    {
namespace impl    {

      class stat_impl: public boost::noncopyable
      {
      public:
            static stat_impl * getImplement();

            void save();
            void exec(const std::string & data);

      private:
            static stat_impl   * _impl;
      };

}     /*    end of impl    */
}     /*    end of base    */
}     /*    end of echoq    */


#endif /* end of include guard: ECHOQ_BASE_IMPLE_STAT_H */

