/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: balls.proto */

#ifndef PROTOBUF_C_balls_2eproto__INCLUDED
#define PROTOBUF_C_balls_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct BallDrawDisplayMsg BallDrawDisplayMsg;
typedef struct PayperviewReq PayperviewReq;
typedef struct PayperviewResp PayperviewResp;


/* --- enums --- */


/* --- messages --- */

struct  BallDrawDisplayMsg
{
  ProtobufCMessage base;
  ProtobufCBinaryData ch;
  uint32_t x;
  uint32_t y;
};
#define BALL_DRAW_DISPLAY_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&ball_draw_display_msg__descriptor) \
, {0,NULL}, 0, 0 }


struct  PayperviewReq
{
  ProtobufCMessage base;
  int32_t message_type;
  char *subscriber_name;
  char *creditcard_number;
  int32_t ch;
  int32_t direction;
};
#define PAYPERVIEW_REQ__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&payperview_req__descriptor) \
, 0, NULL, NULL, 0, 0 }


struct  PayperviewResp
{
  ProtobufCMessage base;
  int32_t random_secret;
};
#define PAYPERVIEW_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&payperview_resp__descriptor) \
, 0 }


/* BallDrawDisplayMsg methods */
void   ball_draw_display_msg__init
                     (BallDrawDisplayMsg         *message);
size_t ball_draw_display_msg__get_packed_size
                     (const BallDrawDisplayMsg   *message);
size_t ball_draw_display_msg__pack
                     (const BallDrawDisplayMsg   *message,
                      uint8_t             *out);
size_t ball_draw_display_msg__pack_to_buffer
                     (const BallDrawDisplayMsg   *message,
                      ProtobufCBuffer     *buffer);
BallDrawDisplayMsg *
       ball_draw_display_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   ball_draw_display_msg__free_unpacked
                     (BallDrawDisplayMsg *message,
                      ProtobufCAllocator *allocator);
/* PayperviewReq methods */
void   payperview_req__init
                     (PayperviewReq         *message);
size_t payperview_req__get_packed_size
                     (const PayperviewReq   *message);
size_t payperview_req__pack
                     (const PayperviewReq   *message,
                      uint8_t             *out);
size_t payperview_req__pack_to_buffer
                     (const PayperviewReq   *message,
                      ProtobufCBuffer     *buffer);
PayperviewReq *
       payperview_req__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   payperview_req__free_unpacked
                     (PayperviewReq *message,
                      ProtobufCAllocator *allocator);
/* PayperviewResp methods */
void   payperview_resp__init
                     (PayperviewResp         *message);
size_t payperview_resp__get_packed_size
                     (const PayperviewResp   *message);
size_t payperview_resp__pack
                     (const PayperviewResp   *message,
                      uint8_t             *out);
size_t payperview_resp__pack_to_buffer
                     (const PayperviewResp   *message,
                      ProtobufCBuffer     *buffer);
PayperviewResp *
       payperview_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   payperview_resp__free_unpacked
                     (PayperviewResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*BallDrawDisplayMsg_Closure)
                 (const BallDrawDisplayMsg *message,
                  void *closure_data);
typedef void (*PayperviewReq_Closure)
                 (const PayperviewReq *message,
                  void *closure_data);
typedef void (*PayperviewResp_Closure)
                 (const PayperviewResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor ball_draw_display_msg__descriptor;
extern const ProtobufCMessageDescriptor payperview_req__descriptor;
extern const ProtobufCMessageDescriptor payperview_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_balls_2eproto__INCLUDED */
