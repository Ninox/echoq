/*=============================================================================
#     FileName: eqTimer.h
#         Desc: a timer helper for echoq
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-16 18:29:18
#      History:
=============================================================================*/
#ifndef _ECHOQ_TIMER_H_
#define _ECHOQ_TIMER_H_

namespace echoq   {
      class eqTimer     {
      public:
            typedef void (*eqTimerEvent)();

            static uint32_t   interval(eqTimerEvent evt, uint32_t inv);
            static void       stopInterval(uint32_t invId);

            static void       delay(eqTimerEvent evt, uint32_t timeout);
      
      private:
            eqTimer();
            ~eqTimer ();

            eqTimerEvent _callback;
      };

}     /*    end of echoq    */

#endif /* end of include guard: _ECHOQ_TIMER_H_ */

