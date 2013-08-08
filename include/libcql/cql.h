/*
Copyright (c) 2013 Matthew Stump

This file is part of libcql.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __CQL_C_H_INCLUDED__
#define __CQL_C_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#if !defined _WIN32_WCE
#include <errno.h>
#endif
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/*  Handle DSO symbol visibility */
#if defined _WIN32
#   if defined CQL_STATIC
#       define CQL_EXPORT
#   elif defined DLL_EXPORT
#       define CQL_EXPORT __declspec(dllexport)
#   else
#       define CQL_EXPORT __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define CQL_EXPORT __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define CQL_EXPORT __attribute__ ((visibility("default")))
#   else
#       define CQL_EXPORT
#   endif
#endif

typedef uint8_t   cql_byte_t;
typedef uint16_t  cql_short_t;
typedef int32_t   cql_int_t;
typedef int64_t   cql_bigint_t;
typedef int8_t    cql_stream_id_t;

struct cql_context_t;
struct cql_future_t;
struct cql_result_t;
struct cql_status_t;

#define CQL_OPCODE_ERROR        0x00
#define CQL_OPCODE_STARTUP      0x01
#define CQL_OPCODE_READY        0x02
#define CQL_OPCODE_AUTHENTICATE 0x03
#define CQL_OPCODE_CREDENTIALS  0x04
#define CQL_OPCODE_OPTIONS      0x05
#define CQL_OPCODE_SUPPORTED    0x06
#define CQL_OPCODE_QUERY        0x07
#define CQL_OPCODE_RESULT       0x08
#define CQL_OPCODE_PREPARE      0x09
#define CQL_OPCODE_EXECUTE      0x0A
#define CQL_OPCODE_REGISTER     0x0B
#define CQL_OPCODE_EVENT        0x0C

#define CQL_CONSISTENCY_ANY          0x0000
#define CQL_CONSISTENCY_ONE          0x0001
#define CQL_CONSISTENCY_TWO          0x0002
#define CQL_CONSISTENCY_THREE        0x0003
#define CQL_CONSISTENCY_QUORUM       0x0004
#define CQL_CONSISTENCY_ALL          0x0005
#define CQL_CONSISTENCY_LOCAL_QUORUM 0x0006
#define CQL_CONSISTENCY_EACH_QUORUM  0x0007

#define CQL_COLUMN_TYPE_UNKNOWN   0xFFFF
#define CQL_COLUMN_TYPE_CUSTOM    0x0000
#define CQL_COLUMN_TYPE_ASCII     0x0001
#define CQL_COLUMN_TYPE_BIGINT    0x0002
#define CQL_COLUMN_TYPE_BLOB      0x0003
#define CQL_COLUMN_TYPE_BOOLEAN   0x0004
#define CQL_COLUMN_TYPE_COUNTER   0x0005
#define CQL_COLUMN_TYPE_DECIMAL   0x0006
#define CQL_COLUMN_TYPE_DOUBLE    0x0007
#define CQL_COLUMN_TYPE_FLOAT     0x0008
#define CQL_COLUMN_TYPE_INT       0x0009
#define CQL_COLUMN_TYPE_TEXT      0x000A
#define CQL_COLUMN_TYPE_TIMESTAMP 0x000B
#define CQL_COLUMN_TYPE_UUID      0x000C
#define CQL_COLUMN_TYPE_VARCHAR   0x000D
#define CQL_COLUMN_TYPE_VARINT    0x000E
#define CQL_COLUMN_TYPE_TIMEUUID  0x000F
#define CQL_COLUMN_TYPE_INET      0x0010
#define CQL_COLUMN_TYPE_LIST      0x0020
#define CQL_COLUMN_TYPE_MAP       0x0021
#define CQL_COLUMN_TYPE_SET       0x0022

#define CQL_LOG_CRITICAL 0x00
#define CQL_LOG_ERROR    0x01
#define CQL_LOG_INFO     0x02
#define CQL_LOG_DEBUG    0x03

#define CQL_RESULT_VOID          0x0001
#define CQL_RESULT_ROWS          0x0002
#define CQL_RESULT_SET_KEYSPACE  0x0003
#define CQL_RESULT_PREPARED      0x0004
#define CQL_RESULT_SCHEMA_CHANGE 0x0005

#define CQL_EVENT_TYPE_UNKOWN   0x00
#define CQL_EVENT_TYPE_TOPOLOGY 0x01
#define CQL_EVENT_TYPE_STATUS   0x02
#define CQL_EVENT_TYPE_SCHEMA   0x03

#define CQL_EVENT_SCHEMA_UNKNOWN 0x00
#define CQL_EVENT_SCHEMA_CREATED 0x01
#define CQL_EVENT_SCHEMA_DROPPED 0x02
#define CQL_EVENT_SCHEMA_UPDATED 0x03

#define CQL_EVENT_STATUS_UNKNOWN 0x00
#define CQL_EVENT_STATUS_UP      0x01
#define CQL_EVENT_STATUS_DOWN    0x02

#define CQL_EVENT_TOPOLOGY_UNKNOWN     0x00
#define CQL_EVENT_TOPOLOGY_ADD_NODE    0x01
#define CQL_EVENT_TOPOLOGY_REMOVE_NODE 0x02


/******************************************************************************/
/*                                                                            */
/* CQL Context initialization and configuration                               */
/*                                                                            */
/******************************************************************************/

CQL_EXPORT cql_context_t*
cql_context_new();

CQL_EXPORT void
cql_context_free(
    cql_context_t* context);

CQL_EXPORT bool
cql_set_opt(
    cql_context_t* context,
    int            option,
    void*          value,
    size_t         value_size,
    cql_status_t** status);

CQL_EXPORT bool
cql_init(
    cql_context_t* context,
    cql_status_t** status);

/******************************************************************************/
/*                                                                            */
/* Pool                                                                       */
/*                                                                            */
/******************************************************************************/

CQL_EXPORT bool
cql_close(
    cql_context_t* context,
    cql_status_t** status);

CQL_EXPORT void*
cql_add_client(
    cql_context_t* context,
    char*          host,
    size_t         host_size,
    unsigned short port);

/******************************************************************************/
/*                                                                            */
/* Futures                                                                    */
/*                                                                            */
/******************************************************************************/

CQL_EXPORT bool
cql_future_ready(
    cql_context_t* context,
    cql_future_t*  future);

CQL_EXPORT void
cql_future_wait(
    cql_context_t* context,
    cql_future_t*  future);

CQL_EXPORT bool
cql_future_success(
    cql_context_t* context,
    cql_future_t*  future);

CQL_EXPORT int
cql_future_get_error_code(
    cql_context_t* context,
    cql_future_t*  future);

CQL_EXPORT void
cql_future_get_error_message(
    cql_context_t* context,
    cql_future_t*  future,
    char**         message);

CQL_EXPORT bool
cql_future_get_result(
    cql_context_t* context,
    cql_future_t*  future,
    cql_result_t** result,
    cql_status_t** status);

/******************************************************************************/
/*                                                                            */
/* Queries and Prepared Statements                                            */
/*                                                                            */
/******************************************************************************/

CQL_EXPORT cql_future_t*
cql_query(
    cql_context_t* context,
    const char*    query,
    size_t         query_size,
    int            consistency);

CQL_EXPORT cql_future_t*
cql_prepare(
    cql_context_t* context,
    const char*    query,
    size_t         query_size);

CQL_EXPORT void*
cql_execute_new(
    cql_context_t* context,
    void*          id,
    size_t         id_size);

CQL_EXPORT void
cql_execute_free(
    void*  execute);

CQL_EXPORT cql_future_t*
cql_execute(
    cql_context_t* context,
    void*          execute,
    int            consistency);

CQL_EXPORT void
cql_execute_push_data(
    cql_context_t* context,
    void*          execute,
    void*          data,
    size_t         data_size);

CQL_EXPORT void
cql_execute_push_bool(
    cql_context_t* context,
    void*          execute,
    bool           param);

CQL_EXPORT void
cql_execute_push_short(
    cql_context_t* context,
    void*          execute,
    short          param);

CQL_EXPORT void
cql_execute_push_int(
    cql_context_t* context,
    void*          execute,
    int            param);

CQL_EXPORT void
cql_execute_push_float(
    cql_context_t* context,
    void*          execute,
    float          param);

CQL_EXPORT void
cql_execute_push_double(
    cql_context_t* context,
    void*          execute,
    float          param);

CQL_EXPORT void
cql_execute_push_bigint(
    cql_context_t* context,
    void*          execute,
    int64_t        param);

/******************************************************************************/
/*                                                                            */
/* Result data                                                                */
/*                                                                            */
/******************************************************************************/

CQL_EXPORT cql_int_t
cql_result_get_type(
    cql_context_t* context,
    cql_result_t*  result);

CQL_EXPORT size_t
cql_result_get_column_count(
    cql_context_t* context,
    cql_result_t*  result);

CQL_EXPORT size_t
cql_result_get_row_count(
    cql_context_t* context,
    cql_result_t*  result);

CQL_EXPORT bool
cql_result_get_index(
    cql_context_t* context,
    cql_result_t*  result,
    char*          column,
    size_t         column_size,
    size_t*        index);

CQL_EXPORT bool
cql_result_is_null(
    cql_context_t* context,
    cql_result_t*  result,
    size_t         row,
    size_t         column);


#undef CQL_EXPORT

#ifdef __cplusplus
}
#endif

#endif // __CQL_C_H_INCLUDED__
