/*
 * Copyright (c) 2009-2021, Google LLC
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Defs are upb's internal representation of the constructs that can appear
 * in a .proto file:
 *
 * - upb_msgdef: describes a "message" construct.
 * - upb_fielddef: describes a message field.
 * - upb_filedef: describes a .proto file and its defs.
 * - upb_enumdef: describes an enum.
 * - upb_oneofdef: describes a oneof.
 *
 * TODO: definitions of services.
 */

#ifndef UPB_DEF_H_
#define UPB_DEF_H_

#include "upb/upb.h"
#include "upb/table_internal.h"
#include "google/protobuf/descriptor.upb.h"

/* Must be last. */
#include "upb/port_def.inc"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

struct upb_enumdef;
typedef struct upb_enumdef upb_enumdef;
struct upb_enumvaldef;
typedef struct upb_enumvaldef upb_enumvaldef;
struct upb_extrange;
typedef struct upb_extrange upb_extrange;
struct upb_fielddef;
typedef struct upb_fielddef upb_fielddef;
struct upb_filedef;
typedef struct upb_filedef upb_filedef;
struct upb_methoddef;
typedef struct upb_methoddef upb_methoddef;
struct upb_msgdef;
typedef struct upb_msgdef upb_msgdef;
struct upb_oneofdef;
typedef struct upb_oneofdef upb_oneofdef;
struct upb_servicedef;
typedef struct upb_servicedef upb_servicedef;
struct upb_streamdef;
typedef struct upb_streamdef upb_streamdef;
struct upb_symtab;
typedef struct upb_symtab upb_symtab;

typedef enum {
  UPB_SYNTAX_PROTO2 = 2,
  UPB_SYNTAX_PROTO3 = 3
} upb_syntax_t;

/* All the different kind of well known type messages. For simplicity of check,
 * number wrappers and string wrappers are grouped together. Make sure the
 * order and merber of these groups are not changed.
 */
typedef enum {
  UPB_WELLKNOWN_UNSPECIFIED,
  UPB_WELLKNOWN_ANY,
  UPB_WELLKNOWN_FIELDMASK,
  UPB_WELLKNOWN_DURATION,
  UPB_WELLKNOWN_TIMESTAMP,
  /* number wrappers */
  UPB_WELLKNOWN_DOUBLEVALUE,
  UPB_WELLKNOWN_FLOATVALUE,
  UPB_WELLKNOWN_INT64VALUE,
  UPB_WELLKNOWN_UINT64VALUE,
  UPB_WELLKNOWN_INT32VALUE,
  UPB_WELLKNOWN_UINT32VALUE,
  /* string wrappers */
  UPB_WELLKNOWN_STRINGVALUE,
  UPB_WELLKNOWN_BYTESVALUE,
  UPB_WELLKNOWN_BOOLVALUE,
  UPB_WELLKNOWN_VALUE,
  UPB_WELLKNOWN_LISTVALUE,
  UPB_WELLKNOWN_STRUCT
} upb_wellknowntype_t;

/* upb_fielddef ***************************************************************/

/* Maximum field number allowed for FieldDefs.  This is an inherent limit of the
 * protobuf wire format. */
#define UPB_MAX_FIELDNUMBER ((1 << 29) - 1)

const google_protobuf_FieldOptions *upb_FieldDef_Options(const upb_fielddef *f);
bool upb_FieldDef_HasOptions(const upb_fielddef *f);
const char *upb_FieldDef_FullName(const upb_fielddef *f);
upb_fieldtype_t upb_FieldDef_CType(const upb_fielddef *f);
upb_descriptortype_t upb_FieldDef_Type(const upb_fielddef *f);
upb_label_t upb_FieldDef_Label(const upb_fielddef *f);
uint32_t upb_FieldDef_Number(const upb_fielddef *f);
const char *upb_FieldDef_Name(const upb_fielddef *f);
const char *upb_FieldDef_JsonName(const upb_fielddef *f);
bool upb_FieldDef_HasJsonName(const upb_fielddef *f);
bool upb_FieldDef_IsExtension(const upb_fielddef *f);
bool upb_FieldDef_IsPacked(const upb_fielddef *f);
const upb_filedef *upb_FieldDef_File(const upb_fielddef *f);
const upb_msgdef *upb_FieldDef_ContainingType(const upb_fielddef *f);
const upb_msgdef *upb_FieldDef_ExtensionScope(const upb_fielddef *f);
const upb_oneofdef *upb_FieldDef_ContainingOneof(const upb_fielddef *f);
const upb_oneofdef *upb_FieldDef_RealContainingOneof(const upb_fielddef *f);
uint32_t upb_FieldDef_Index(const upb_fielddef *f);
bool upb_FieldDef_IsSubMessage(const upb_fielddef *f);
bool upb_FieldDef_IsString(const upb_fielddef *f);
bool upb_FieldDef_IsRepeated(const upb_fielddef *f);
bool upb_FieldDef_IsPrimitive(const upb_fielddef *f);
bool upb_FieldDef_IsMap(const upb_fielddef *f);
bool upb_FieldDef_HasDefault(const upb_fielddef *f);
bool upb_FieldDef_HasSubDef(const upb_fielddef *f);
bool upb_FieldDef_HasPresence(const upb_fielddef *f);
const upb_msgdef *upb_FieldDef_MessageSubDef(const upb_fielddef *f);
const upb_enumdef *upb_FieldDef_EnumSubDef(const upb_fielddef *f);
const upb_msglayout_field *upb_FieldDef_Layout(const upb_fielddef *f);
const upb_msglayout_ext *_upb_FieldDef_ExtensionLayout(const upb_fielddef *f);
bool _upb_FieldDef_IsProto3Optional(const upb_fielddef *f);

/* upb_oneofdef ***************************************************************/

typedef upb_inttable_iter upb_oneof_iter;

const google_protobuf_OneofOptions *upb_oneofdef_options(const upb_oneofdef *o);
bool upb_oneofdef_hasoptions(const upb_oneofdef *o);
const char *upb_oneofdef_name(const upb_oneofdef *o);
const upb_msgdef *upb_oneofdef_containingtype(const upb_oneofdef *o);
uint32_t upb_oneofdef_index(const upb_oneofdef *o);
bool upb_oneofdef_issynthetic(const upb_oneofdef *o);
int upb_oneofdef_fieldcount(const upb_oneofdef *o);
const upb_fielddef *upb_oneofdef_field(const upb_oneofdef *o, int i);

/* Oneof lookups:
 * - ntof:  look up a field by name.
 * - ntofz: look up a field by name (as a null-terminated string).
 * - itof:  look up a field by number. */
const upb_fielddef *upb_oneofdef_ntof(const upb_oneofdef *o,
                                      const char *name, size_t length);
UPB_INLINE const upb_fielddef *upb_oneofdef_ntofz(const upb_oneofdef *o,
                                                  const char *name) {
  return upb_oneofdef_ntof(o, name, strlen(name));
}
const upb_fielddef *upb_oneofdef_itof(const upb_oneofdef *o, uint32_t num);

/* DEPRECATED, slated for removal. */
int upb_oneofdef_numfields(const upb_oneofdef *o);
void upb_oneof_begin(upb_oneof_iter *iter, const upb_oneofdef *o);
void upb_oneof_next(upb_oneof_iter *iter);
bool upb_oneof_done(upb_oneof_iter *iter);
upb_fielddef *upb_oneof_iter_field(const upb_oneof_iter *iter);
void upb_oneof_iter_setdone(upb_oneof_iter *iter);
bool upb_oneof_iter_isequal(const upb_oneof_iter *iter1,
                            const upb_oneof_iter *iter2);
/* END DEPRECATED */

/* upb_msgdef *****************************************************************/

typedef upb_inttable_iter upb_msg_field_iter;
typedef upb_strtable_iter upb_msg_oneof_iter;

/* Well-known field tag numbers for map-entry messages. */
#define UPB_MAPENTRY_KEY   1
#define UPB_MAPENTRY_VALUE 2

/* Well-known field tag numbers for Any messages. */
#define UPB_ANY_TYPE 1
#define UPB_ANY_VALUE 2

/* Well-known field tag numbers for timestamp messages. */
#define UPB_DURATION_SECONDS 1
#define UPB_DURATION_NANOS 2

/* Well-known field tag numbers for duration messages. */
#define UPB_TIMESTAMP_SECONDS 1
#define UPB_TIMESTAMP_NANOS 2

const google_protobuf_MessageOptions *upb_msgdef_options(const upb_msgdef *m);
bool upb_msgdef_hasoptions(const upb_msgdef *m);
const char *upb_msgdef_fullname(const upb_msgdef *m);
const upb_filedef *upb_msgdef_file(const upb_msgdef *m);
const upb_msgdef *upb_msgdef_containingtype(const upb_msgdef *m);
const char *upb_msgdef_name(const upb_msgdef *m);
upb_syntax_t upb_msgdef_syntax(const upb_msgdef *m);
upb_wellknowntype_t upb_msgdef_wellknowntype(const upb_msgdef *m);
bool upb_msgdef_iswrapper(const upb_msgdef *m);
bool upb_msgdef_isnumberwrapper(const upb_msgdef *m);
int upb_msgdef_extrangecount(const upb_msgdef *m);
int upb_msgdef_fieldcount(const upb_msgdef *m);
int upb_msgdef_oneofcount(const upb_msgdef *m);
const upb_extrange *upb_msgdef_extrange(const upb_msgdef *m, int i);
const upb_fielddef *upb_msgdef_field(const upb_msgdef *m, int i);
const upb_oneofdef *upb_msgdef_oneof(const upb_msgdef *m, int i);
const upb_fielddef *upb_msgdef_itof(const upb_msgdef *m, uint32_t i);
const upb_fielddef *upb_msgdef_ntof(const upb_msgdef *m, const char *name,
                                    size_t len);
const upb_oneofdef *upb_msgdef_ntoo(const upb_msgdef *m, const char *name,
                                    size_t len);
const upb_msglayout *upb_msgdef_layout(const upb_msgdef *m);

UPB_INLINE const upb_oneofdef *upb_msgdef_ntooz(const upb_msgdef *m,
                                               const char *name) {
  return upb_msgdef_ntoo(m, name, strlen(name));
}

UPB_INLINE const upb_fielddef *upb_msgdef_ntofz(const upb_msgdef *m,
                                                const char *name) {
  return upb_msgdef_ntof(m, name, strlen(name));
}

UPB_INLINE bool upb_msgdef_mapentry(const upb_msgdef *m) {
  return google_protobuf_MessageOptions_map_entry(upb_msgdef_options(m));
}

/* Nested entities. */
int upb_msgdef_nestedmsgcount(const upb_msgdef *m);
int upb_msgdef_nestedenumcount(const upb_msgdef *m);
int upb_msgdef_nestedextcount(const upb_msgdef *m);
const upb_msgdef *upb_msgdef_nestedmsg(const upb_msgdef *m, int i);
const upb_enumdef *upb_msgdef_nestedenum(const upb_msgdef *m, int i);
const upb_fielddef *upb_msgdef_nestedext(const upb_msgdef *m, int i);

/* Lookup of either field or oneof by name.  Returns whether either was found.
 * If the return is true, then the found def will be set, and the non-found
 * one set to NULL. */
bool upb_msgdef_lookupname(const upb_msgdef *m, const char *name, size_t len,
                           const upb_fielddef **f, const upb_oneofdef **o);

UPB_INLINE bool upb_msgdef_lookupnamez(const upb_msgdef *m, const char *name,
                                       const upb_fielddef **f,
                                       const upb_oneofdef **o) {
  return upb_msgdef_lookupname(m, name, strlen(name), f, o);
}

/* Returns a field by either JSON name or regular proto name. */
const upb_fielddef *upb_msgdef_lookupjsonname(const upb_msgdef *m,
                                              const char *name, size_t len);
UPB_INLINE const upb_fielddef *upb_msgdef_lookupjsonnamez(const upb_msgdef *m,
                                                          const char *name) {
  return upb_msgdef_lookupjsonname(m, name, strlen(name));
}

/* DEPRECATED, slated for removal */
int upb_msgdef_numfields(const upb_msgdef *m);
int upb_msgdef_numoneofs(const upb_msgdef *m);
int upb_msgdef_numrealoneofs(const upb_msgdef *m);
void upb_msg_field_begin(upb_msg_field_iter *iter, const upb_msgdef *m);
void upb_msg_field_next(upb_msg_field_iter *iter);
bool upb_msg_field_done(const upb_msg_field_iter *iter);
upb_fielddef *upb_msg_iter_field(const upb_msg_field_iter *iter);
void upb_msg_field_iter_setdone(upb_msg_field_iter *iter);
bool upb_msg_field_iter_isequal(const upb_msg_field_iter * iter1,
                                const upb_msg_field_iter * iter2);
void upb_msg_oneof_begin(upb_msg_oneof_iter * iter, const upb_msgdef *m);
void upb_msg_oneof_next(upb_msg_oneof_iter * iter);
bool upb_msg_oneof_done(const upb_msg_oneof_iter *iter);
const upb_oneofdef *upb_msg_iter_oneof(const upb_msg_oneof_iter *iter);
void upb_msg_oneof_iter_setdone(upb_msg_oneof_iter * iter);
bool upb_msg_oneof_iter_isequal(const upb_msg_oneof_iter *iter1,
                                const upb_msg_oneof_iter *iter2);
/* END DEPRECATED */

/* upb_extrange ***************************************************************/

const google_protobuf_ExtensionRangeOptions *upb_extrange_options(
    const upb_extrange *r);
bool upb_extrange_hasoptions(const upb_extrange *r);
int32_t upb_extrange_start(const upb_extrange *r);
int32_t upb_extrange_end(const upb_extrange *r);

/* upb_enumdef ****************************************************************/

typedef upb_strtable_iter upb_enum_iter;

const google_protobuf_EnumOptions *upb_enumdef_options(const upb_enumdef *e);
bool upb_enumdef_hasoptions(const upb_enumdef *e);
const char *upb_enumdef_fullname(const upb_enumdef *e);
const char *upb_enumdef_name(const upb_enumdef *e);
const upb_filedef *upb_enumdef_file(const upb_enumdef *e);
const upb_msgdef *upb_enumdef_containingtype(const upb_enumdef *e);
int32_t upb_enumdef_default(const upb_enumdef *e);
int upb_enumdef_valuecount(const upb_enumdef *e);
const upb_enumvaldef *upb_enumdef_value(const upb_enumdef *e, int i);

const upb_enumvaldef *upb_enumdef_lookupname(const upb_enumdef *e,
                                             const char *name, size_t len);
const upb_enumvaldef *upb_enumdef_lookupnum(const upb_enumdef *e, int32_t num);
bool upb_enumdef_checknum(const upb_enumdef *e, int32_t num);

/* DEPRECATED, slated for removal */
int upb_enumdef_numvals(const upb_enumdef *e);
void upb_enum_begin(upb_enum_iter *iter, const upb_enumdef *e);
void upb_enum_next(upb_enum_iter *iter);
bool upb_enum_done(upb_enum_iter *iter);
const char *upb_enum_iter_name(upb_enum_iter *iter);
int32_t upb_enum_iter_number(upb_enum_iter *iter);
/* END DEPRECATED */

// Convenience wrapper.
UPB_INLINE const upb_enumvaldef *upb_enumdef_lookupnamez(const upb_enumdef *e,
                                                         const char *name) {
  return upb_enumdef_lookupname(e, name, strlen(name));
}

/* upb_enumvaldef *************************************************************/

const google_protobuf_EnumValueOptions *upb_enumvaldef_options(
    const upb_enumvaldef *e);
bool upb_enumvaldef_hasoptions(const upb_enumvaldef *e);
const char *upb_enumvaldef_fullname(const upb_enumvaldef *e);
const char *upb_enumvaldef_name(const upb_enumvaldef *e);
int32_t upb_enumvaldef_number(const upb_enumvaldef *e);
uint32_t upb_enumvaldef_index(const upb_enumvaldef *e);
const upb_enumdef *upb_enumvaldef_enum(const upb_enumvaldef *e);

/* upb_filedef ****************************************************************/

const google_protobuf_FileOptions *upb_filedef_options(const upb_filedef *f);
bool upb_filedef_hasoptions(const upb_filedef *f);
const char *upb_filedef_name(const upb_filedef *f);
const char *upb_filedef_package(const upb_filedef *f);
const char *upb_filedef_phpprefix(const upb_filedef *f);
const char *upb_filedef_phpnamespace(const upb_filedef *f);
upb_syntax_t upb_filedef_syntax(const upb_filedef *f);
int upb_filedef_depcount(const upb_filedef *f);
int upb_filedef_publicdepcount(const upb_filedef *f);
int upb_filedef_weakdepcount(const upb_filedef *f);
int upb_filedef_toplvlmsgcount(const upb_filedef *f);
int upb_filedef_toplvlenumcount(const upb_filedef *f);
int upb_filedef_toplvlextcount(const upb_filedef *f);
int upb_filedef_servicecount(const upb_filedef *f);
const upb_filedef *upb_filedef_dep(const upb_filedef *f, int i);
const upb_filedef *upb_filedef_publicdep(const upb_filedef *f, int i);
const upb_filedef *upb_filedef_weakdep(const upb_filedef *f, int i);
const upb_msgdef *upb_filedef_toplvlmsg(const upb_filedef *f, int i);
const upb_enumdef *upb_filedef_toplvlenum(const upb_filedef *f, int i);
const upb_fielddef *upb_filedef_toplvlext(const upb_filedef *f, int i);
const upb_servicedef *upb_filedef_service(const upb_filedef *f, int i);
const upb_symtab *upb_filedef_symtab(const upb_filedef *f);
const int32_t *_upb_filedef_publicdepnums(const upb_filedef *f);
const int32_t *_upb_filedef_weakdepnums(const upb_filedef *f);

/* upb_methoddef **************************************************************/

const google_protobuf_MethodOptions *upb_methoddef_options(
    const upb_methoddef *m);
bool upb_methoddef_hasoptions(const upb_methoddef *m);
const char *upb_methoddef_fullname(const upb_methoddef *m);
const char *upb_methoddef_name(const upb_methoddef *m);
const upb_servicedef *upb_methoddef_service(const upb_methoddef *m);
const upb_msgdef *upb_methoddef_inputtype(const upb_methoddef *m);
const upb_msgdef *upb_methoddef_outputtype(const upb_methoddef *m);
bool upb_methoddef_clientstreaming(const upb_methoddef *m);
bool upb_methoddef_serverstreaming(const upb_methoddef *m);

/* upb_servicedef *************************************************************/

const google_protobuf_ServiceOptions *upb_servicedef_options(
    const upb_servicedef *s);
bool upb_servicedef_hasoptions(const upb_servicedef *s);
const char *upb_servicedef_fullname(const upb_servicedef *s);
const char *upb_servicedef_name(const upb_servicedef *s);
int upb_servicedef_index(const upb_servicedef *s);
const upb_filedef *upb_servicedef_file(const upb_servicedef *s);
int upb_servicedef_methodcount(const upb_servicedef *s);
const upb_methoddef *upb_servicedef_method(const upb_servicedef *s, int i);
const upb_methoddef *upb_servicedef_lookupmethod(const upb_servicedef *s,
                                                 const char *name);

/* upb_symtab *****************************************************************/

upb_symtab *upb_symtab_new(void);
void upb_symtab_free(upb_symtab* s);
const upb_msgdef *upb_symtab_lookupmsg(const upb_symtab *s, const char *sym);
const upb_msgdef *upb_symtab_lookupmsg2(
    const upb_symtab *s, const char *sym, size_t len);
const upb_enumdef *upb_symtab_lookupenum(const upb_symtab *s, const char *sym);
const upb_enumvaldef *upb_symtab_lookupenumval(const upb_symtab *s,
                                               const char *sym);
const upb_fielddef *upb_symtab_lookupext(const upb_symtab *s, const char *sym);
const upb_fielddef *upb_symtab_lookupext2(const upb_symtab *s, const char *sym,
                                         size_t len);
const upb_filedef *upb_symtab_lookupfile(const upb_symtab *s, const char *name);
const upb_servicedef *upb_symtab_lookupservice(const upb_symtab *s,
                                               const char *name);
const upb_filedef *upb_symtab_lookupfileforsym(const upb_symtab *s,
                                               const char *name);
const upb_filedef *upb_symtab_lookupfile2(
    const upb_symtab *s, const char *name, size_t len);
const upb_filedef *upb_symtab_addfile(
    upb_symtab *s, const google_protobuf_FileDescriptorProto *file,
    upb_status *status);
size_t _upb_symtab_bytesloaded(const upb_symtab *s);
upb_arena *_upb_symtab_arena(const upb_symtab *s);
const upb_fielddef *_upb_symtab_lookupextfield(const upb_symtab *s,
                                               const upb_msglayout_ext *ext);
const upb_fielddef *upb_symtab_lookupextbynum(const upb_symtab *s,
                                              const upb_msgdef *m,
                                              int32_t fieldnum);
const upb_extreg *upb_symtab_extreg(const upb_symtab *s);
const upb_fielddef **upb_symtab_getallexts(const upb_symtab *s,
                                           const upb_msgdef *m, size_t *count);

/* For generated code only: loads a generated descriptor. */
typedef struct upb_def_init {
  struct upb_def_init **deps;     /* Dependencies of this file. */
  const upb_msglayout_file *layout;
  const char *filename;
  upb_strview descriptor;         /* Serialized descriptor. */
} upb_def_init;

bool _upb_symtab_loaddefinit(upb_symtab *s, const upb_def_init *init);
void _upb_symtab_allownameconflicts(upb_symtab *s);

#include "upb/port_undef.inc"

#ifdef __cplusplus
}  /* extern "C" */
#endif  /* __cplusplus */

#endif /* UPB_DEF_H_ */
