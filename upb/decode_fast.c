
#include "upb/decode.h"

#include "upb/port_def.inc"

#define UPB_PARSE_PARAMS                                                      \
  upb_decstate *d, const char *ptr, upb_msg *msg, const upb_msglayout *table, \
      uint64_t hasbits, uint64_t data

#define UPB_PARSE_ARGS d, ptr, msg, table, hasbits, data

#define RETURN_GENERIC(msg)  \
  /* fprintf(stderr, msg); */ \
  return fastdecode_generic(UPB_PARSE_ARGS);

typedef enum {
  CARD_s = 0,
  CARD_o = 1,
  CARD_r = 2,
  CARD_p = 3
} upb_card;

UPB_NOINLINE
const char *fastdecode_dispatch(upb_decstate *d, const char *ptr, upb_msg *msg,
                                const upb_msglayout *table, uint64_t hasbits) {
  uint16_t tag;
  uint64_t data = 0;;
  size_t idx;
  if (UPB_UNLIKELY(ptr >= d->fastlimit)) {
    if (UPB_LIKELY(ptr == d->limit)) {
      *(uint32_t*)msg |= hasbits >> 16;  /* Sync hasbits. */
      return ptr;
    }
    RETURN_GENERIC("dispatch hit end\n");
  }
  memcpy(&tag, ptr, 2);
  idx = (tag & 0xf8) >> 3;
  data = table->field_data[idx] ^ tag;
  return table->field_parser[idx](UPB_PARSE_ARGS);
}

UPB_FORCEINLINE
static bool fastdecode_checktag(uint64_t data, int tagbytes) {
  if (tagbytes == 1) {
    return (data & 0xff) == 0;
  } else {
    return (data & 0xffff) == 0;
  }
}

UPB_FORCEINLINE uint64_t fastdecode_munge(uint64_t val, int valbytes, bool zigzag) {
  if (valbytes == 1) {
    return val != 0;
  } else if (zigzag) {
    if (valbytes == 4) {
      uint32_t n = val;
      return (n >> 1) ^ -(int32_t)(n & 1);
    } else if (valbytes == 8) {
      return (val >> 1) ^ -(int64_t)(val & 1);
    }
    UPB_UNREACHABLE();
  }
  return val;
}

UPB_FORCEINLINE
static uint16_t fastdecode_readtag(const char *ptr, int tagbytes) {
  uint16_t ret = 0;
  memcpy(&ret, ptr, tagbytes);
  return ret;
}

UPB_FORCEINLINE
static void *fastdecode_getfield_ofs(upb_decstate *d, const char *ptr,
                                     upb_msg *msg, size_t ofs, uint64_t *data,
                                     uint64_t *hasbits, upb_array **outarr,
                                     void **end, int tagbytes, int valbytes,
                                     upb_card card) {
  void *field = (char *)msg + ofs;

  switch (card) {
    case CARD_s:
      *hasbits |= *data;
      return field;
    case CARD_o: {
      uint32_t *case_ptr = UPB_PTR_AT(msg, (*data >> 16) & 0xffff, uint32_t);
      *case_ptr = (*data >> 32) & 0xffff;
      return field;
    }
    case CARD_r: {
      uint8_t elem_size_lg2 = __builtin_ctz(valbytes);
      upb_array **arr_p = field;
      upb_array *arr;
      uint16_t expected_tag;
      *hasbits >>= 16;
      *(uint32_t*)msg |= *hasbits;
      *hasbits = 0;
      if (UPB_LIKELY(!*arr_p)) {
        size_t need = (valbytes * 4) + sizeof(upb_array);
        if (UPB_UNLIKELY((size_t)(d->arena_end - d->arena_ptr) < need)) {
          *outarr = NULL;
          *data = 0;
          *end = NULL;
          return NULL;
        }
        arr = (void*)d->arena_ptr;
        field = arr + 1;
        arr->data = _upb_array_tagptr(field, elem_size_lg2);
        *arr_p = arr;
        arr->size = 4;
        *end = (char*)field + (arr->size * valbytes);
        d->arena_ptr += need;
      } else {
        arr = *arr_p;
        field = _upb_array_ptr(arr);
        *end = (char*)field + (arr->size * valbytes);
        field = (char*)field + (arr->len * valbytes);
      }
      expected_tag = fastdecode_readtag(ptr, tagbytes);
      *data = expected_tag;
      *outarr = arr;
      return field;
    }
    default:
      UPB_UNREACHABLE();
  }
}

UPB_FORCEINLINE
static void *fastdecode_getfield(upb_decstate *d, const char *ptr, upb_msg *msg,
                                 uint64_t *data, uint64_t *hasbits,
                                 int tagbytes, int valbytes, upb_card card) {
  return fastdecode_getfield_ofs(d, ptr, msg, *data >> 48, data, hasbits, NULL,
                                 NULL, tagbytes, valbytes, card);
}

/* varint fields **************************************************************/

/*
UPB_FORCEINLINE
static const char *fastdecode_longvarint(UPB_PARSE_PARAMS, int valbytes, int varintbytes) {
  uint64_t val = 0;
  void *dst = (void*)data;
#ifdef __BMI2__
#else
  for (int i = 0; i < varintbytes; i++) {
    uint64_t byte = ptr[i];
    if (i != varintbytes - 1) byte &= 0x7f;
    val |= byte << (7 * i);
  }
#endif
  memcpy((void*)data, &val, valbytes);
  return fastdecode_dispatch(d, ptr + varintbytes, msg, table, hasbits);
}

UPB_FORCEINLINE
static const char *fastdecode_longvarintjmp(UPB_PARSE_PARAMS, void *dst,
                                            _upb_field_parser *funcs) {
  uint64_t bytes;
  memcpy(&bytes, ptr + 1, 8);
  bytes = ~bytes & 0x8080808080808080;
  data = (uint64_t)dst;
  return funcs[__builtin_ctz(bytes) / 8](UPB_PARSE_ARGS);
}
*/

UPB_FORCEINLINE
static const char *fastdecode_varint(UPB_PARSE_PARAMS, int tagbytes,
                                     int valbytes, upb_card card, bool zigzag) {
  uint64_t val = 0;
  void *dst;
  if (UPB_UNLIKELY(!fastdecode_checktag(data, tagbytes))) {
    RETURN_GENERIC("varint field tag mismatch\n");
  }
  dst = fastdecode_getfield(d, ptr, msg, &data, &hasbits, tagbytes, valbytes,
                            card);
  val = (uint8_t)ptr[tagbytes];
  if (UPB_UNLIKELY(val & 0x80)) {
    uint32_t byte = (uint8_t)ptr[tagbytes + 1];
    val += (byte - 1) << 7;
    if (UPB_UNLIKELY(byte & 0x80)) {
      RETURN_GENERIC("varint field >2 bytes\n");
    }
    ptr++;
  }
  ptr += tagbytes + 1;
  val = fastdecode_munge(val, valbytes, zigzag);
  memcpy(dst, &val, valbytes);
  return fastdecode_dispatch(d, ptr, msg, table, hasbits);
}

// Generate all varint functions.
// {s,o,r} x {b1,v4,z4,v8,z8} x {1bt,2bt}

#define z_ZZ true
#define b_ZZ false
#define v_ZZ false

#define F(card, type, valbytes, tagbytes)                                      \
  const char *upb_p##card##type##valbytes##_##tagbytes##bt(UPB_PARSE_PARAMS) { \
    return fastdecode_varint(UPB_PARSE_ARGS, tagbytes, valbytes, CARD_##card,  \
                             type##_ZZ);                                       \
  }

#define TYPES(card, tagbytes) \
  F(card, b, 1, tagbytes)     \
  F(card, v, 4, tagbytes)     \
  F(card, v, 8, tagbytes)     \
  F(card, z, 4, tagbytes)     \
  F(card, z, 8, tagbytes)

#define TAGBYTES(card) \
  TYPES(card, 1)       \
  TYPES(card, 2)

TAGBYTES(s)
TAGBYTES(o)
//TAGBYTES(r)

#undef z_ZZ
#undef b_ZZ
#undef v_ZZ
#undef o_ONEOF
#undef s_ONEOF
#undef r_ONEOF
#undef F
#undef TYPES
#undef TAGBYTES

/* string fields **************************************************************/

UPB_FORCEINLINE
bool fastdecode_boundscheck(const char *ptr, unsigned len, const char *end) {
  uintptr_t uptr = (uintptr_t)ptr;
  uintptr_t uend = (uintptr_t)end;
  uintptr_t res = uptr + len;
  return res < uptr || res > uend;
}

UPB_FORCEINLINE
static const char *fastdecode_string(UPB_PARSE_PARAMS, int tagbytes,
                                     upb_card card) {
  upb_strview *dst;
  int64_t len;
  if (UPB_UNLIKELY(!fastdecode_checktag(data, tagbytes))) {
    RETURN_GENERIC("string field tag mismatch\n");
  }

  dst = fastdecode_getfield(d, ptr, msg, &data, &hasbits, tagbytes,
                            sizeof(upb_strview), card);
  len = ptr[tagbytes];
  if (UPB_UNLIKELY(len < 0)) {
    RETURN_GENERIC("string field len >1 byte\n");
  }
  ptr += tagbytes + 1;
  dst->data = ptr;
  dst->size = len;
  if (UPB_UNLIKELY(fastdecode_boundscheck(ptr, len, d->limit))) {
    return fastdecode_err(d);
  }
  ptr += len;
  return fastdecode_dispatch(d, ptr, msg, table, hasbits);
}

const char *upb_pss_1bt(UPB_PARSE_PARAMS) {
  return fastdecode_string(UPB_PARSE_ARGS, 1, CARD_s);
}

const char *upb_pos_1bt(UPB_PARSE_PARAMS) {
  return fastdecode_string(UPB_PARSE_ARGS, 1, CARD_o);
}

const char *upb_pss_2bt(UPB_PARSE_PARAMS) {
  return fastdecode_string(UPB_PARSE_ARGS, 2, CARD_s);
}

const char *upb_pos_2bt(UPB_PARSE_PARAMS) {
  return fastdecode_string(UPB_PARSE_ARGS, 2, CARD_o);
}

/* message fields *************************************************************/

UPB_FORCEINLINE
static const char *fastdecode_submsg(UPB_PARSE_PARAMS, int tagbytes,
                                     upb_card card) {
  const char *saved_limit;
  const upb_msglayout_field *field = &table->fields[data >> 48];
  size_t ofs = field->offset;
  const upb_msglayout *subl = table->submsgs[field->submsg_index];
  upb_array *arr;
  upb_msg **submsg;
  void *end;

  if (UPB_UNLIKELY(!fastdecode_checktag(data, tagbytes))) {
    RETURN_GENERIC("submessage field tag mismatch\n");
  }

  submsg = fastdecode_getfield_ofs(d, ptr, msg, ofs, &data, &hasbits, &arr,
                                   &end, tagbytes, sizeof(upb_msg *), card);

again:
  if (card == CARD_r) {
    if (UPB_UNLIKELY(submsg == end)) {
      if (arr) arr->len = submsg - (upb_msg**)_upb_array_ptr(arr);
      RETURN_GENERIC("need array realloc\n");
    }
  }

  {
    uint32_t len = (uint8_t)ptr[tagbytes];
    if (UPB_UNLIKELY(len & 0x80)) {
      uint32_t byte = (uint8_t)ptr[tagbytes + 1];
      len += (byte - 1) << 7;
      if (UPB_UNLIKELY(byte & 0x80)) {
        if (card == CARD_r) {
          arr->len = submsg - (upb_msg**)_upb_array_ptr(arr);
        }
        RETURN_GENERIC("submessage field len >2 bytes\n");
      }
      ptr++;
    }
    ptr += tagbytes + 1;
    if (UPB_UNLIKELY(fastdecode_boundscheck(ptr, len, d->limit))) {
      return fastdecode_err(d);
    }
    if (card == CARD_r || !*submsg) {
      *submsg = decode_newmsg(d, subl);
    }

    saved_limit = d->limit;
    if (--d->depth < 0) return fastdecode_err(d);
    d->limit = ptr + len;
    d->fastlimit = UPB_MIN(d->limit, d->fastend);
  }

  ptr = fastdecode_dispatch(d, ptr, *submsg, subl, 0);
  submsg++;
  if (ptr != d->limit) return fastdecode_err(d);

  d->limit = saved_limit;
  d->fastlimit = UPB_MIN(d->limit, d->fastend);
  if (d->end_group != 0) return fastdecode_err(d);
  d->depth++;

  if (card == CARD_r) {
    if (UPB_LIKELY(ptr < d->fastlimit) &&
        fastdecode_readtag(ptr, tagbytes) == (uint16_t)data) {
      goto again;
    }
    arr->len = submsg - (upb_msg**)_upb_array_ptr(arr);
  }

  return fastdecode_dispatch(d, ptr, msg, table, hasbits);
}

const char *upb_psm_1bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 1, CARD_s);
}

const char *upb_pom_1bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 1, CARD_o);
}

const char *upb_prm_1bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 1, CARD_r);
}

const char *upb_psm_2bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 2, CARD_s);
}

const char *upb_pom_2bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 2, CARD_o);
}

const char *upb_prm_2bt(UPB_PARSE_PARAMS) {
  return fastdecode_submsg(UPB_PARSE_ARGS, 2, CARD_r);
}