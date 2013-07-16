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

#include <string.h>
#include <stdint.h>
#include <memory.h>
#include <boost/smart_ptr.hpp>

#define ECHOQ_PROTO_MAX             2097152     // 2MB per message
#define ECHOQ_PROTO_PREALLOC_SIZE   512

namespace echoq
{
      /**********************************************
       *          buffer header declaration         *
       **********************************************/
      struct proto_header     {
            enum proto_data_enum {
                  UNKNOWN     = 0,
                  CUSTOM      = 1,
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
      static proto_header __GEmptyHolder;


      /**********************************************
       *            echoq's data protocol           *
       **********************************************/

      class echoqProtocol       {
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
            echoqProtocol()
                  : _header(__GEmptyHolder)
            {
                  size_t rawlen     = sizeof(proto_header) + ECHOQ_PROTO_PREALLOC_SIZE;
                  _rawdata.reset((char*)malloc(rawlen));
                  memset(_rawdata.get(), 0, rawlen);
                  proto_header header;
                  header.proto_sz = header.proto_osz = ECHOQ_PROTO_PREALLOC_SIZE;
                  memcpy(_rawdata.get(), &header, sizeof(header));
                  _header = *(reinterpret_cast<proto_header*>(_rawdata.get()));
            }
            echoqProtocol(char * buffer, size_t sz)
                  : _header(__GEmptyHolder)
            {
                  size_t rawlen     = sizeof(proto_header) + sz;
                  _rawdata.reset((char*)malloc(rawlen));
                  memset(_rawdata.get(), 0, rawlen);
                  // TODO: no compress operation now. 
                  proto_header header;
                  header.proto_sz = header.proto_osz = sz;
                  memcpy(_rawdata.get(), &header, sizeof(header));
                  _header = *(reinterpret_cast<proto_header*>(_rawdata.get()));
            }
                 
            echoqProtocol(const echoqProtocol &other)
                  : _header(__GEmptyHolder)
            {
                  this->_rawdata = other._rawdata;
                  _header = *(reinterpret_cast<proto_header*>(_rawdata.get()));
            }
            echoqProtocol(const proto_header &h)
                  : _header(__GEmptyHolder)
            {
                  size_t rawlen = sizeof(h) + h.proto_sz;
                  _rawdata.reset((char*)malloc(rawlen));
                  memset(_rawdata.get(), 0, rawlen);
                  memcpy(_rawdata.get(), &h, sizeof(h));
                  _header = *(reinterpret_cast<proto_header*>(_rawdata.get()));
            }
            ~echoqProtocol()  {
                  _rawdata.reset();
            }

            //    getter methods
            //-------------------------------------------
            proto_header &          getHeader() const {
                  return _header;
            }
            char *                  getContent() const     {
                  return _rawdata.get() + sizeof(proto_header);
            }
            const char *            getRawData() const     {
                  return _rawdata.get();
            }
            uint32_t                getContentLength() const     {
                  return _header.proto_sz;
            }
            uint32_t                getRawSize() const      {
                  return _header.proto_sz + sizeof(proto_header);
            }

            //    setter methods
            //------------------------------------------
            void  setBufferSize(size_t sz)      {
                  size_t      rawsize = sizeof(proto_header) + sz;
                  char *      pOldRaw = _rawdata.get();
                  char *      pNewRaw = (char*)realloc(pOldRaw, rawsize);
                  // TODO: no data compress
                  if (pNewRaw == NULL)    {
                        return;
                  } else if (pNewRaw != pOldRaw)      {
                        // it means 'realloc' create a new memory block and auto free the old one
                        _rawdata.reset(pNewRaw);
                        _header = *(reinterpret_cast<proto_header*>(_rawdata.get()));
                  }
                  _header.proto_sz  = sz;
                  _header.proto_osz = sz;
            }
            void  setBuffer(const char *data, size_t sz)    {
                  this->setBufferSize(sz);
                  memcpy(_rawdata.get() + sizeof(proto_header), data, sz);
            }
            void  setServiceId(uint16_t srvid)  {
                  _header.proto_sid = srvid;
            }
            void  setGroupId(uint32_t group)    {
                  _header.proto_group = group;
            }
            void  setDatatype(uint16_t datatype)      {
                  _header.proto_dtype = datatype;
            }
            void  setUserID(uint16_t userid)    {
                  _header.proto_uid = userid;
            }
            void  setProtocalType(uint16_t protoType) {
                  _header.proto_type = protoType;
            }

            // echoqSession can access the private rawdata
            friend class echoqSession;
            
      private:
            boost::shared_array<char>     _rawdata;
            proto_header &                _header;
      };

}


#endif /* end of include guard: ECHOQ_DATAPROTOCOL_H */

