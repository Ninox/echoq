/*=============================================================================
#     FileName: eqProto.cc
#         Desc: the eqProtocol implement
#       Author: drzunny
#        Email: drzunny@hotmail.com
#     HomePage: http://drzlab.info
#      Version: 0.1.0
#   LastChange: 2013-07-16 21:36:05
#      History:
=============================================================================*/
#include "eqProto.h"
#include "base/zip.h"
#include "base/symbol.h"

#include <string.h>
#include <memory.h>

#define SELF_HEADER(attr, v)     *((proto_header*)this->_rawdata.get()).attr = v

namespace echoq   {

      // constructor
      //----------------------------------------------------
      eqProtocol::eqProtocol()     {
            size_t rawlen     = sizeof(proto_header) + ECHOQ_PROTO_PREALLOC_SIZE;
            _rawdata.reset((char*)malloc(rawlen));
            memset(_rawdata.get(), 0, rawlen);
            proto_header header;
            header.proto_sz = header.proto_osz = ECHOQ_PROTO_PREALLOC_SIZE;
            memcpy(_rawdata.get(), &header, sizeof(header));
      }
      eqProtocol::eqProtocol(const char * buffer, size_t sz)      {
            /*    TODO:
             *          The limitation of the buffer size is not ready
             */
            // compress the buffer
            size_t csz, destSize;
            const char * destBuf = buffer;
            bool ok;
            base::refBuffer_t cbuffer = base::zip_compress(buffer, sz, csz, ok);
            // if success, return the compress data & compress size
            // if fail,    return the original data and original size
            if (ok)     {
                  destBuffer  = cbuffer.get();
                  destSize    = csz;
            } else      {
                  destSize    = sz;
                  sz          = 0;
            }
            // setup the protocol buffer
            size_t rawlen     = sizeof(proto_header) + destSize;
            _rawdata.reset((char*)malloc(rawlen));
            proto_header header;
            header.proto_sz = csz;
            header.proto_osz = sz;
            memcpy(_rawdata.get(), &header, sizeof(header));
            memcpy(_rawdata.get() + sizeof(header), destBuffer, destSize);
      }
      eqProtocol::eqProtocol(const eqProtocol & other)      {
            _rawdata = other._rawdata;
      }
      eqProtocol::eqProtocol(const proto_header & header)   {
            size_t rawlen = header.proto_sz + sizeof(proto_header);
            _rawdata.reset((char*)malloc(rawlen));
            memset(_rawdata.get(), 0, rawlen);
            memcpy(_rawdata.get(), &header, sizeof(header));
      }
      eqProtocol::~eqProtocol()     {
            _rawdata.reset();
      }

      // getter methods
      //---------------------------------------------------
      const proto_header & 
      eqProtocol::getHeader() const    {
            return *(reinterpret_cast<proto_header*>(_rawdata.get()));
      }
      const char *
      eqProtocol::getContent() const      {
            return _rawdata.get() + sizeof(proto_header);
      }
      const char *
      eqProtocol::getRawdata() const      {
            return _rawdata.get();
      }
      size_t
      eqProtocol::getContentLength() const      {
            return this->getHeader().proto_sz;
      }
      size_t
      eqProtocol::getRawSize() const      {
            return sizeof(proto_header) + this->getContentLength();
      }

      // setter methods
      //---------------------------------------------------
      void 
      eqProtocol::setBuffer(const char * data, size_t sz)    {
            /*    TODO:
             *          The limitation of the buffer size is not ready
             */

            // compress the buffer
            size_t c_sz, destSize;
            const char * destBuffer = data;
            bool ok;
            base::refBuffer_t cbuffer = base::zip_compress(data, sz, csz, ok);
            // if success, return the compress data & compress size
            // if fail,    return the original data and original size
            if (ok)     {
                  destBuffer  = cbuffer.get();
                  destSize    = csz;
            } else      {
                  destSize    = sz;
                  sz          = 0;
            }

            // setup the compress buffer
            size_t rawlen  = sizeof(proto_header) + destSize;
            char * pOldRaw = _rawdata.get();
            char * pNewRaw = (char*)realloc(pOldRaw, rawlen);
            // if 'realloc' fail, ** DO NOT ** do any thing
            // if success, copy the new buffer
            if ( pNewRaw == NULL )  {
                  return;
            } else if ( pNewRaw != pOldRaw )    {
                  _rawdata.reset(pNewRaw);
            }
            SELF_HEADER(proto_sz, destSize);
            SELF_HEADER(proto_osz, sz);
            memcpy(_rawdata.get() + sizeof(proto_header), destBuffer, destSize);

      }
      void
      eqProtocol::setServiceId(uint16_t sid)    {
            SELF_HEADER(proto_sid, sid);
      }
      void
      eqProtocol::setGroupId(uint32_t group)    {
            SELF_HEADER(proto_group, group);
      }
      void 
      eqProtocol::setDatatype(uint16_t datatype)      {
            SELF_HEADER(proto_dtype, datatype);
      }
      void
      eqProtocol::setUserID(uint16_t userid)    {
            SELF_HEADER(proto_uid, userid);
      }
      void
      eqProtocol::setProtocolType(uint16_t protoType) {
            SELF_HEADER(proto_type, protoType);
      }



}     /*    end of echoq    */
