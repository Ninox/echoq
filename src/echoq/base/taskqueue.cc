/*=============================================================================
#     FileName: taskqueue.cc
#         Desc: the async taskqueue implement, **INTERNAL USE ONLY**
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-17 00:10:19
#      History:
=============================================================================*/
#include "taskqueue.h"
#include "assert.h"

#include "impl/impl.hpp"

#include <stdlib.h>
#include <memory.h>

using namespace std;
using namespace boost;

using namespace echoq::base::impl;

#define SAVE_EVENT(name)      (name)_impl::getImplement()->save()
#define EXEC_EVENT(name,data) (name)_impl::getImplement()->exec(data)

namespace echoq   {
namespace base    {

      /**************************************************
       *               helpers functions                *
       **************************************************/

      
      /**
       * @brief Save the current event. if the event file has been switched, the old file will be saved by implement.
       */
      static void
      _task_savefile()  {
            SAVE_EVENT(log);
            SAVE_EVENT(stat);
            SAVE_EVENT(io);
      }

      /**************************************************
       *             the taskEvent implement            *
       **************************************************/
      void
      taskEvent::set(const char * buffer, size_t sz)   {
            if (this->evtBuffer != NULL)  {
                  free(this->evtBuffer);
            }
            this->evtBuffer = (char*)malloc(sz);
            this->evtBufSize= sz;
            memcpy(this->evtBuffer, buffer, sz);
      }
      void
      taskEvent::free(taskEvent ** task)  {
            ECHOQ_ASSERT(task != NULL, "the reference of task cannot be null");

            if (*task != NULL)      {
                  free((*task)->evtBuffer);
                  (*task)->evtBufSize = 0;
                  free((*task));
                  *task = NULL;
            }
      }

      /**************************************************
       *             the taskqueue implement            *
       **************************************************/
      void
      taskqueue::pushEvent(taskEvent evt) {
      }
      void
      taskqueue::run()  {
            if (taskqueue::_isRunning)
                  return;
            taskqueue::_isRunning = true;
            _workingThread = boost::thread(taskqueue::_eventHandler);
            _workingThread.detach();
      }
      void
      taskqueue::stop() {
            taskqueue::_isRunning = false;
      }

      void
      taskqueue::_eventHandler()    {
            bool hasTask = false;
            while (taskqueue::_isRunning)      {
                  // DO NOT SAVE THE FILE WHEN THE EVENT(io, log, status) IS BUSY
                  hasTask = false;
                  string sdata;
                  while ( _queue.size() > 0)    {
                        hasTask = true;
                        taskEvent ev = _queue.front();

                        switch(ev.evtType)
                        {
                        case taskEvent::LOG:
                              EXEC_EVENT(log, ev.evtBuffer);
                              break;
                        case taskEvent::IO:
                              sdata.assign(ev.evtBuffer, ev.evtBufSize);
                              EXEC_EVENT(io, sdata);
                              break;
                        case taskEvent::STATUS:
                              EXEC_EVENT(log, ev.evtBuffer);
                              break;
                        default:
                              continue;
                        }
                        
                        // remove the finished event
                        _queue.pop();
                  }
                  // if the queue has been run, save the file
                  if (hasTask)      {
                        _task_savefile();
                  }                  
                  thread::sleep(100);
            }
            // if the thread is stopped, save file
            _task_savefile();
      }


}     /*    end of base    */
}     /*    end of echoq    */
