/*=============================================================================
#     FileName: taskqueue.h
#         Desc: async taskqueue(status, log, io)helper, **INTERNAL USE ONLY**
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-17 00:09:03
#      History:
=============================================================================*/
#ifndef ECHOQ_BASE_TASKQUEUE_H
#define ECHOQ_BASE_TASKQUEUE_H

#include <queue>
#include <boost/thread.hpp>

namespace echoq   {
namespace base    {

      struct taskEvent  {
            enum {
                  LOG    = 0,
                  STATUS = 1,
                  IO     = 2
            };

            char * evtBuffer;
            int    evtType;
            size_t evtBufSize;

            void set(const char *buffer, size_t sz);
            static void free(taskEvent ** task);
      };

      class taskqueue
      {
      public:
            static void pushEvent(taskEvent evt);
            static void run();
            static void stop();
      
      private:
            static void                  _eventHandler();
            static std::queue<taskEvent> _queue;
            static boost::thread         _workingThread;
            static bool                  _isRunning;
      };

}     /*    end of base    */
}     /*    end of echoq   */


#endif /* end of include guard: ECHOQ_BASE_TASKQUEUE_H */

