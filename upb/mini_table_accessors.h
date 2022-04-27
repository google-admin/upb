/*
 * Copyright (c) 2009-2022, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UPB_MINI_TABLE_ACCESSORS_H_
#define UPB_MINI_TABLE_ACCESSORS_H_

#include "upb/mini_table_accessors_internal.h"
#include "upb/msg_internal.h"

// Must be last.
#include "upb/port_def.inc"

#ifdef __cplusplus
extern "C" {
#endif

bool upb_MiniTable_HasField(const upb_Message* msg,
                            const upb_MiniTable_Field* field);

void upb_MiniTable_ClearField(upb_Message* msg,
                              const upb_MiniTable_Field* field);

UPB_INLINE bool upb_MiniTable_GetBool(const upb_Message* msg,
                                      const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Bool);
  return *UPB_PTR_AT(msg, field->offset, bool);
}

UPB_INLINE void upb_MiniTable_SetBool(upb_Message* msg,
                                      const upb_MiniTable_Field* field,
                                      bool value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Bool);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, bool) = value;
}

UPB_INLINE int32_t upb_MiniTable_GetInt32(const upb_Message* msg,
                                          const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Int32 ||
             field->descriptortype == kUpb_FieldType_SInt32 ||
             field->descriptortype == kUpb_FieldType_SFixed32);
  return *UPB_PTR_AT(msg, field->offset, int32_t);
}

UPB_INLINE void upb_MiniTable_SetInt32(upb_Message* msg,
                                       const upb_MiniTable_Field* field,
                                       int32_t value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Int32 ||
             field->descriptortype == kUpb_FieldType_SInt32 ||
             field->descriptortype == kUpb_FieldType_SFixed32);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, int32_t) = value;
}

UPB_INLINE uint32_t upb_MiniTable_GetUInt32(const upb_Message* msg,
                                            const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_UInt32 ||
             field->descriptortype == kUpb_FieldType_Fixed32);
  return *UPB_PTR_AT(msg, field->offset, uint32_t);
}

UPB_INLINE void upb_MiniTable_SetUInt32(upb_Message* msg,
                                        const upb_MiniTable_Field* field,
                                        uint32_t value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_UInt32 ||
             field->descriptortype == kUpb_FieldType_Fixed32);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, uint32_t) = value;
}

UPB_INLINE int32_t upb_MiniTable_GetEnum(const upb_Message* msg,
                                         const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Enum);
  return *UPB_PTR_AT(msg, field->offset, int32_t);
}

UPB_INLINE void upb_MiniTable_SetEnum(upb_Message* msg,
                                      const upb_MiniTable_Field* field,
                                      int32_t value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Enum);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, int32_t) = value;
}

UPB_INLINE int64_t upb_MiniTable_GetInt64(const upb_Message* msg,
                                          const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Int64 ||
             field->descriptortype == kUpb_FieldType_SInt64 ||
             field->descriptortype == kUpb_FieldType_SFixed64);
  return *UPB_PTR_AT(msg, field->offset, int64_t);
}

UPB_INLINE void upb_MiniTable_SetInt64(upb_Message* msg,
                                       const upb_MiniTable_Field* field,
                                       int64_t value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Int64 ||
             field->descriptortype == kUpb_FieldType_SInt64 ||
             field->descriptortype == kUpb_FieldType_SFixed64);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, int64_t) = value;
}

UPB_INLINE uint64_t upb_MiniTable_GetUInt64(const upb_Message* msg,
                                            const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_UInt64 ||
             field->descriptortype == kUpb_FieldType_Fixed64);
  return *UPB_PTR_AT(msg, field->offset, uint64_t);
}

UPB_INLINE void upb_MiniTable_SetUInt64(upb_Message* msg,
                                        const upb_MiniTable_Field* field,
                                        uint64_t value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_UInt64 ||
             field->descriptortype == kUpb_FieldType_Fixed64);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, uint64_t) = value;
}

UPB_INLINE float upb_MiniTable_GetFloat(const upb_Message* msg,
                                        const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Float);
  return *UPB_PTR_AT(msg, field->offset, float);
}

UPB_INLINE void upb_MiniTable_SetFloat(upb_Message* msg,
                                       const upb_MiniTable_Field* field,
                                       float value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Float);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, float) = value;
}

UPB_INLINE double upb_MiniTable_GetDouble(const upb_Message* msg,
                                          const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Double);
  return *UPB_PTR_AT(msg, field->offset, double);
}

UPB_INLINE void upb_MiniTable_SetDouble(upb_Message* msg,
                                        const upb_MiniTable_Field* field,
                                        double value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Double);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, double) = value;
}

UPB_INLINE upb_StringView upb_MiniTable_GetString(
    const upb_Message* msg, const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Bytes ||
             field->descriptortype == kUpb_FieldType_String);
  return *UPB_PTR_AT(msg, field->offset, upb_StringView);
}

UPB_INLINE void upb_MiniTable_SetString(upb_Message* msg,
                                        const upb_MiniTable_Field* field,
                                        upb_StringView value) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Bytes ||
             field->descriptortype == kUpb_FieldType_String);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, upb_StringView) = value;
}

UPB_INLINE const upb_Message* upb_MiniTable_GetMessage(
    const upb_Message* msg, const upb_MiniTable_Field* field) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Message);
  return *UPB_PTR_AT(msg, field->offset, const upb_Message*);
}

UPB_INLINE void upb_MiniTable_SetMessage(upb_Message* msg,
                                         const upb_MiniTable_Field* field,
                                         upb_Message* sub_message) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Message);
  _upb_MiniTable_SetPresence(msg, field);
  *UPB_PTR_AT(msg, field->offset, const upb_Message*) = sub_message;
}

UPB_INLINE upb_Message* upb_MiniTable_GetMutableMessage(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTable_Field* field, upb_Arena* arena) {
  UPB_ASSERT(field->descriptortype == kUpb_FieldType_Message);
  upb_Message* sub_message = *UPB_PTR_AT(msg, field->offset, upb_Message*);
  if (!sub_message) {
    sub_message =
        _upb_Message_New(mini_table->subs[field->submsg_index].submsg, arena);
  }
  return sub_message;
}

// For users repeated field array is opaque.
struct upb_RepeatedFieldArray;
typedef struct upb_RepeatedFieldArray upb_RepeatedFieldArray;

// Resizes storage for repeated fields.
upb_RepeatedFieldArray* upb_MiniTable_ResizeArray(
    upb_Message* msg, const upb_MiniTable_Field* field, size_t new_size,
    upb_Arena* arena);

typedef union {
  bool bool_val;
  float float_val;
  double double_val;
  int32_t int32_val;
  int64_t int64_val;
  uint32_t uint32_val;
  uint64_t uint64_val;
  const upb_Map* map_val;
  const upb_Message* msg_val;
  const upb_Array* array_val;
  upb_StringView str_val;
} upb_FieldValue;

typedef union {
  upb_Map* map_val;
  upb_Message* msg_val;
  upb_Array* array_val;
  upb_StringView str_val;
} upb_MutableFieldValue;

UPB_INLINE upb_RepeatedFieldArray* upb_MiniTable_GetArray(
    const upb_Message* msg, const upb_MiniTable_Field* field) {
  return (upb_RepeatedFieldArray*)*UPB_PTR_AT(msg, field->offset, upb_Array*);
}

UPB_INLINE size_t
upb_MiniTable_GetArraySize(const upb_RepeatedFieldArray* array) {
  UPB_ASSERT(array);
  return ((upb_Array*)array)->size;
}

// Mutates repeated field data at index.
void upb_MiniTable_SetArrayValue(upb_RepeatedFieldArray* array, size_t index,
                                 const upb_FieldValue* value);

upb_FieldValue upb_MiniTable_GetArrayValue(const upb_RepeatedFieldArray* array,
                                           size_t index);

upb_MutableFieldValue upb_MiniTable_GetMutableArrayValue(
    const upb_RepeatedFieldArray* array, size_t index);

UPB_INLINE const upb_MiniTable* upb_MiniTable_GetSubMessageTable(
    const upb_MiniTable* mini_table, const upb_MiniTable_Field* field) {
  return mini_table->subs[field->submsg_index].submsg;
}

// TODO(ferhat): Add support for extensions.

#ifdef __cplusplus
} /* extern "C" */
#endif

#include "upb/port_undef.inc"

#endif  // UPB_MINI_TABLE_ACCESSORS_H_
