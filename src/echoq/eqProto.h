/*=============================================================================
#     FileName: dataproto.h
#         Desc: echoq's network protocol
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-06 14:08:20
#      History:
=============================================================================*/

#ifndef ECHOQ_DATAPROTOCOL_H
#define ECHOQ_DATAPROTOCOL_H

#include <stdint.h>
#include <boost/smart_ptr.hpp>

#include "base/zip.h"

#define ECHOQ_PROTO_PREALLOC_SIZE   512

namespace echoq
{
      /**********************************************
       *          buffer header declaration         *
       **********************************************/
      struct proto_header     {
            enum proto_data_enum {
                  UNKNOWN     = 0,
                  BINARY      = 1,
                  STRING      = 2,
                  INT32       = 3,
                  INT64       = 4,
                  FLOAT       = 5
            };

            char        proto_prefix[12];       // '!echoPROTO_'
            uint32_t    proto_group, proto_ts, proto_sz, proto_osz;
            uint16_t    proto_sid, proto_uid, proto_type, proto_dtype;

            proto_header()
                  : proto_sid(0), proto_group(0), proto_ts(0), proto_sz(0),
                    proto_uid(0), proto_type(0), proto_dtype(0), proto_osz(0)
            {
                  strcpy(this->proto_prefix, "!echoPROTO_");
            }
      };


      /**********************************************
       *            echoq's data protocol           *
       **********************************************/

      class eqProtocoll       {
            enum proto_type {
                  PROTO_ASYNCSOCK   = 0,
                  PROTO_PUBLISHER   = 1,
                  PROTO_SUBSCRIPE   = 2,
                  PROTO_BROADCAST   = 3,
                  PROTO_PIPELINES   = 4
            };

      public:
            //    constructor
            //--------------------------------------------
            eqProtocoll();
            eqProtocoll(char * buffer, size_t sz);
            eqProtocoll(const eqProtocoll &other);
            eqProtocoll(const proto_header &h);
            ~eqProtocoll();

            //    getter methods
            //-------------------------------------------
            proto_header & getHeader() const;
            char *         getContent() const;
            const char *   getRawData() const;
            uint32_t       getContentLength() const;
            uint32_t       getRawSize() const;

            //    setter methods
            //------------------------------------------
            void  setBuffer(const char *data, size_t sz);
            void  setServiceId(uint16_t srvid);
            void  setGroupId(uint32_t group);
            void  setDatatype(uint16_t datatype);
            void  setUserID(uint16_t userid);
            void  setProtocalType(uint16_t protoType);

      private:
            boost::shared_array<char>     _rawdata;
      };

}


#endif /* end of include guard: ECHOQ_DATAPROTOCOL_H */

