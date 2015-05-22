/*
 * upb - a minimalist implementation of protocol buffers.
 *
 * Copyright (c) 2012 Google Inc.  See LICENSE for details.
 * Author: Josh Haberman <jhaberman@gmail.com>
 *
 * Shared definitions for upb Lua modules.
 */

#ifndef UPB_LUA_UPB_H_
#define UPB_LUA_UPB_H_

#include "lauxlib.h"
#include "upb/def.h"
#include "upb/handlers.h"
#include "upb/symtab.h"

// Lua 5.1/5.2 compatibility code.
#if LUA_VERSION_NUM == 501

#define lua_rawlen lua_objlen

// Lua >= 5.2's getuservalue/setuservalue functions do not exist in prior
// versions but the older function lua_getfenv() can provide 100% of its
// capabilities (the reverse is not true).
#define lua_getuservalue(L, index) lua_getfenv(L, index)
#define lua_setuservalue(L, index) lua_setfenv(L, index)

void *luaL_testudata(lua_State *L, int ud, const char *tname);

#elif LUA_VERSION_NUM == 502 || LUA_VERSION_NUM == 503

int luaL_typerror(lua_State *L, int narg, const char *tname);

#else
#error Only Lua 5.1, 5.2, and 5.3 are supported
#endif

#define lupb_assert(L, predicate) \
  if (!(predicate))               \
    luaL_error(L, "internal error: %s, %s:%d ", #predicate, __FILE__, __LINE__);

// Function for initializing the core library.  This function is idempotent,
// and should be called at least once before calling any of the functions that
// construct core upb types.
int luaopen_upb(lua_State *L);

// Gets or creates a package table for a C module that is uniquely identified by
// "ptr".  The easiest way to supply a unique "ptr" is to pass the address of a
// static variable private in the module's .c file.
//
// If this module has already been registered in this lua_State, pushes it and
// returns true.
//
// Otherwise, creates a new module table for this module with the given name,
// pushes it, and registers the given top-level functions in it.  It also sets
// it as a global variable, but only if the current version of Lua expects that
// (ie Lua 5.1/LuaJIT).
//
// If "false" is returned, the caller is guaranteed that this lib has not been
// registered in this Lua state before (regardless of any funny business the
// user might have done to the global state), so the caller can safely perform
// one-time initialization.
bool lupb_openlib(lua_State *L, void *ptr, const char *name,
                  const luaL_Reg *funcs);

// Custom check/push functions.  Unlike the Lua equivalents, they are pinned to
// specific types (instead of lua_Number, etc), and do not allow any implicit
// conversion or data loss.
int64_t lupb_checkint64(lua_State *L, int narg);
int32_t lupb_checkint32(lua_State *L, int narg);
uint64_t lupb_checkuint64(lua_State *L, int narg);
uint32_t lupb_checkuint32(lua_State *L, int narg);
double lupb_checkdouble(lua_State *L, int narg);
float lupb_checkfloat(lua_State *L, int narg);
bool lupb_checkbool(lua_State *L, int narg);
const char *lupb_checkname(lua_State *L, int narg);

void lupb_pushint64(lua_State *L, int64_t val);
void lupb_pushint32(lua_State *L, int32_t val);
void lupb_pushuint64(lua_State *L, uint64_t val);
void lupb_pushuint32(lua_State *L, uint32_t val);
void lupb_pushdouble(lua_State *L, double val);
void lupb_pushfloat(lua_State *L, float val);
void lupb_pushbool(lua_State *L, bool val);

// Functions for getting/pushing wrappers to various types defined in the
// core library.
void *lupb_refcounted_check(lua_State *L, int narg, const char *type);
const upb_msgdef *lupb_msg_checkdef(lua_State *L, int narg);
const upb_msgdef *lupb_msgdef_check(lua_State *L, int narg);
const upb_enumdef *lupb_enumdef_check(lua_State *L, int narg);
const upb_fielddef *lupb_fielddef_check(lua_State *L, int narg);
const upb_symtab *lupb_symtab_check(lua_State *L, int narg);

void lupb_refcounted_pushnewrapper(lua_State *L, const upb_refcounted *obj,
                                   const char *type, const void *ref_donor);
bool lupb_def_pushwrapper(lua_State *L, const upb_def *def,
                          const void *ref_donor);
void lupb_def_pushnewrapper(lua_State *L, const upb_def *def,
                            const void *ref_donor);
void lupb_symtab_pushwrapper(lua_State *L, const upb_symtab *s,
                             const void *ref_donor);
void lupb_symtab_pushnewrapper(lua_State *L, const upb_symtab *s,
                               const void *ref_donor);

// For constructing a new message.  narg is the Lua value for the MessageDef
// object.
void lupb_msg_pushnew(lua_State *L, int narg);

// Builds and returns a handlers object for populating a lupb_msg described by
// the MessageDef at "narg".
//
// TODO(haberman): factor this so it doesn't have to take a lua_State.  We
// should be able to generate message handlers for a upb_msgdef that can be used
// across many Lua states, so we can shared JIT code across lua_States.
const upb_handlers *lupb_msg_newwritehandlers(lua_State *L, int narg,
                                              const void *owner);

// Registers a type with the given name, methods, and metamethods.
// If "refcount_gc" is true, adds a __gc metamethod that does an unref.
// Refcounted types must be allocated with lupb_refcounted_push[new]wrapper.
void lupb_register_type(lua_State *L, const char *name, const luaL_Reg *m,
                        const luaL_Reg *mm, bool refcount_gc);

// Checks the given upb_status and throws a Lua error if it is not ok.
void lupb_checkstatus(lua_State *L, upb_status *s);

#endif  // UPB_LUA_UPB_H_
