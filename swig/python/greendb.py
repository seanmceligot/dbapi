# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.
import _greendb
def _swig_setattr(self,class_type,name,value):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    self.__dict__[name] = value

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class GreenDb(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GreenDb, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GreenDb, name)
    def __init__(self,*args):
        _swig_setattr(self, GreenDb, 'this', apply(_greendb.new_GreenDb,args))
        _swig_setattr(self, GreenDb, 'thisown', 1)
    def __del__(self, destroy= _greendb.delete_GreenDb):
        try:
            if self.thisown: destroy(self)
        except: pass
    def open(*args): return apply(_greendb.GreenDb_open,args)
    def open_unknown(*args): return apply(_greendb.GreenDb_open_unknown,args)
    def open_queue(*args): return apply(_greendb.GreenDb_open_queue,args)
    def open_recno(*args): return apply(_greendb.GreenDb_open_recno,args)
    def open_hash(*args): return apply(_greendb.GreenDb_open_hash,args)
    def open_btree(*args): return apply(_greendb.GreenDb_open_btree,args)
    def dbfile(*args): return apply(_greendb.GreenDb_dbfile,args)
    def name(*args): return apply(_greendb.GreenDb_name,args)
    def put(*args): return apply(_greendb.GreenDb_put,args)
    def fetch(*args): return apply(_greendb.GreenDb_fetch,args)
    def cursor(*args): return apply(_greendb.GreenDb_cursor,args)
    def close(*args): return apply(_greendb.GreenDb_close,args)
    def __repr__(self):
        return "<C GreenDb instance at %s>" % (self.this,)

class GreenDbPtr(GreenDb):
    def __init__(self,this):
        _swig_setattr(self, GreenDb, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, GreenDb, 'thisown', 0)
        _swig_setattr(self, GreenDb,self.__class__,GreenDb)
_greendb.GreenDb_swigregister(GreenDbPtr)

class GreenEnv(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GreenEnv, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GreenEnv, name)
    def __init__(self,*args):
        _swig_setattr(self, GreenEnv, 'this', apply(_greendb.new_GreenEnv,args))
        _swig_setattr(self, GreenEnv, 'thisown', 1)
    def __del__(self, destroy= _greendb.delete_GreenEnv):
        try:
            if self.thisown: destroy(self)
        except: pass
    def open(*args): return apply(_greendb.GreenEnv_open,args)
    def close(*args): return apply(_greendb.GreenEnv_close,args)
    def home(*args): return apply(_greendb.GreenEnv_home,args)
    def __repr__(self):
        return "<C GreenEnv instance at %s>" % (self.this,)

class GreenEnvPtr(GreenEnv):
    def __init__(self,this):
        _swig_setattr(self, GreenEnv, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, GreenEnv, 'thisown', 0)
        _swig_setattr(self, GreenEnv,self.__class__,GreenEnv)
_greendb.GreenEnv_swigregister(GreenEnvPtr)

class Datum(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Datum, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Datum, name)
    def __init__(self,*args):
        _swig_setattr(self, Datum, 'this', apply(_greendb.new_Datum,args))
        _swig_setattr(self, Datum, 'thisown', 1)
    def __del__(self, destroy= _greendb.delete_Datum):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C Datum instance at %s>" % (self.this,)

class DatumPtr(Datum):
    def __init__(self,this):
        _swig_setattr(self, Datum, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Datum, 'thisown', 0)
        _swig_setattr(self, Datum,self.__class__,Datum)
_greendb.Datum_swigregister(DatumPtr)

class StrDatum(Datum):
    __swig_setmethods__ = {}
    for _s in [Datum]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, StrDatum, name, value)
    __swig_getmethods__ = {}
    for _s in [Datum]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, StrDatum, name)
    def __init__(self,*args):
        _swig_setattr(self, StrDatum, 'this', apply(_greendb.new_StrDatum,args))
        _swig_setattr(self, StrDatum, 'thisown', 1)
    def type_name(*args): return apply(_greendb.StrDatum_type_name,args)
    def __del__(self, destroy= _greendb.delete_StrDatum):
        try:
            if self.thisown: destroy(self)
        except: pass
    def repr(*args): return apply(_greendb.StrDatum_repr,args)
    def value(*args): return apply(_greendb.StrDatum_value,args)
    def set_value(*args): return apply(_greendb.StrDatum_set_value,args)
    def __repr__(self):
        return "<C StrDatum instance at %s>" % (self.this,)

class StrDatumPtr(StrDatum):
    def __init__(self,this):
        _swig_setattr(self, StrDatum, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, StrDatum, 'thisown', 0)
        _swig_setattr(self, StrDatum,self.__class__,StrDatum)
_greendb.StrDatum_swigregister(StrDatumPtr)

class IntDatum(Datum):
    __swig_setmethods__ = {}
    for _s in [Datum]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntDatum, name, value)
    __swig_getmethods__ = {}
    for _s in [Datum]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, IntDatum, name)
    def __init__(self,*args):
        _swig_setattr(self, IntDatum, 'this', apply(_greendb.new_IntDatum,args))
        _swig_setattr(self, IntDatum, 'thisown', 1)
    def type_name(*args): return apply(_greendb.IntDatum_type_name,args)
    def __del__(self, destroy= _greendb.delete_IntDatum):
        try:
            if self.thisown: destroy(self)
        except: pass
    def repr(*args): return apply(_greendb.IntDatum_repr,args)
    def value(*args): return apply(_greendb.IntDatum_value,args)
    def set_value(*args): return apply(_greendb.IntDatum_set_value,args)
    def __repr__(self):
        return "<C IntDatum instance at %s>" % (self.this,)

class IntDatumPtr(IntDatum):
    def __init__(self,this):
        _swig_setattr(self, IntDatum, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, IntDatum, 'thisown', 0)
        _swig_setattr(self, IntDatum,self.__class__,IntDatum)
_greendb.IntDatum_swigregister(IntDatumPtr)

class Cursor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Cursor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Cursor, name)
    def __del__(self, destroy= _greendb.delete_Cursor):
        try:
            if self.thisown: destroy(self)
        except: pass
    def first(*args): return apply(_greendb.Cursor_first,args)
    def last(*args): return apply(_greendb.Cursor_last,args)
    def find(*args): return apply(_greendb.Cursor_find,args)
    def next(*args): return apply(_greendb.Cursor_next,args)
    def close(*args): return apply(_greendb.Cursor_close,args)
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C Cursor instance at %s>" % (self.this,)

class CursorPtr(Cursor):
    def __init__(self,this):
        _swig_setattr(self, Cursor, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Cursor, 'thisown', 0)
        _swig_setattr(self, Cursor,self.__class__,Cursor)
_greendb.Cursor_swigregister(CursorPtr)

class Row(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Row, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Row, name)
    def __init__(self,*args):
        _swig_setattr(self, Row, 'this', apply(_greendb.new_Row,args))
        _swig_setattr(self, Row, 'thisown', 1)
    def __del__(self, destroy= _greendb.delete_Row):
        try:
            if self.thisown: destroy(self)
        except: pass
    def close(*args): return apply(_greendb.Row_close,args)
    def getpk(*args): return apply(_greendb.Row_getpk,args)
    def set_n(*args): return apply(_greendb.Row_set_n,args)
    def set(*args): return apply(_greendb.Row_set,args)
    def from_string_n(*args): return apply(_greendb.Row_from_string_n,args)
    def from_string(*args): return apply(_greendb.Row_from_string,args)
    def to_string_n(*args): return apply(_greendb.Row_to_string_n,args)
    def to_string(*args): return apply(_greendb.Row_to_string,args)
    def get_column_n(*args): return apply(_greendb.Row_get_column_n,args)
    def get_column(*args): return apply(_greendb.Row_get_column,args)
    def get_col_no(*args): return apply(_greendb.Row_get_col_no,args)
    def get_existing_column(*args): return apply(_greendb.Row_get_existing_column,args)
    def size(*args): return apply(_greendb.Row_size,args)
    def __repr__(self):
        return "<C Row instance at %s>" % (self.this,)

class RowPtr(Row):
    def __init__(self,this):
        _swig_setattr(self, Row, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Row, 'thisown', 0)
        _swig_setattr(self, Row,self.__class__,Row)
_greendb.Row_swigregister(RowPtr)

class Table(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Table, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Table, name)
    def __init__(self,*args):
        _swig_setattr(self, Table, 'this', apply(_greendb.new_Table,args))
        _swig_setattr(self, Table, 'thisown', 1)
    def get_schema(*args): return apply(_greendb.Table_get_schema,args)
    def close(*args): return apply(_greendb.Table_close,args)
    def __del__(self, destroy= _greendb.delete_Table):
        try:
            if self.thisown: destroy(self)
        except: pass
    def get_name(*args): return apply(_greendb.Table_get_name,args)
    def save(*args): return apply(_greendb.Table_save,args)
    def index(*args): return apply(_greendb.Table_index,args)
    def fetch(*args): return apply(_greendb.Table_fetch,args)
    def new_row(*args): return apply(_greendb.Table_new_row,args)
    def cursor(*args): return apply(_greendb.Table_cursor,args)
    def first(*args): return apply(_greendb.Table_first,args)
    def last(*args): return apply(_greendb.Table_last,args)
    def next(*args): return apply(_greendb.Table_next,args)
    def get_col_name(*args): return apply(_greendb.Table_get_col_name,args)
    def __repr__(self):
        return "<C Table instance at %s>" % (self.this,)

class TablePtr(Table):
    def __init__(self,this):
        _swig_setattr(self, Table, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Table, 'thisown', 0)
        _swig_setattr(self, Table,self.__class__,Table)
_greendb.Table_swigregister(TablePtr)

class Schema(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Schema, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Schema, name)
    def add_column(*args): return apply(_greendb.Schema_add_column,args)
    def get_type_n(*args): return apply(_greendb.Schema_get_type_n,args)
    def get_type(*args): return apply(_greendb.Schema_get_type,args)
    def get_col_no(*args): return apply(_greendb.Schema_get_col_no,args)
    def get_name(*args): return apply(_greendb.Schema_get_name,args)
    def size(*args): return apply(_greendb.Schema_size,args)
    def __del__(self, destroy= _greendb.delete_Schema):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C Schema instance at %s>" % (self.this,)

class SchemaPtr(Schema):
    def __init__(self,this):
        _swig_setattr(self, Schema, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, Schema, 'thisown', 0)
        _swig_setattr(self, Schema,self.__class__,Schema)
_greendb.Schema_swigregister(SchemaPtr)

class TypeMap(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TypeMap, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TypeMap, name)
    __swig_getmethods__["get_type_map"] = lambda x: _greendb.TypeMap_get_type_map
    if _newclass:get_type_map = staticmethod(_greendb.TypeMap_get_type_map)
    UNDEFINED = _greendb.TypeMap_UNDEFINED
    USER = _greendb.TypeMap_USER
    STRING = _greendb.TypeMap_STRING
    WSTRING = _greendb.TypeMap_WSTRING
    INT = _greendb.TypeMap_INT
    SHORT = _greendb.TypeMap_SHORT
    LONG = _greendb.TypeMap_LONG
    DOUBLE = _greendb.TypeMap_DOUBLE
    UINT = _greendb.TypeMap_UINT
    USHORT = _greendb.TypeMap_USHORT
    ULONG = _greendb.TypeMap_ULONG
    CHAR = _greendb.TypeMap_CHAR
    WCHAR = _greendb.TypeMap_WCHAR
    BOOL = _greendb.TypeMap_BOOL
    def __del__(self, destroy= _greendb.delete_TypeMap):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<C TypeMap instance at %s>" % (self.this,)

class TypeMapPtr(TypeMap):
    def __init__(self,this):
        _swig_setattr(self, TypeMap, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, TypeMap, 'thisown', 0)
        _swig_setattr(self, TypeMap,self.__class__,TypeMap)
_greendb.TypeMap_swigregister(TypeMapPtr)
TypeMap_get_type_map = _greendb.TypeMap_get_type_map


class CursorRow(Row):
    __swig_setmethods__ = {}
    for _s in [Row]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CursorRow, name, value)
    __swig_getmethods__ = {}
    for _s in [Row]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CursorRow, name)
    def __init__(self,*args):
        _swig_setattr(self, CursorRow, 'this', apply(_greendb.new_CursorRow,args))
        _swig_setattr(self, CursorRow, 'thisown', 1)
    def get_cursor(*args): return apply(_greendb.CursorRow_get_cursor,args)
    def __del__(self, destroy= _greendb.delete_CursorRow):
        try:
            if self.thisown: destroy(self)
        except: pass
    def __repr__(self):
        return "<C CursorRow instance at %s>" % (self.this,)

class CursorRowPtr(CursorRow):
    def __init__(self,this):
        _swig_setattr(self, CursorRow, 'this', this)
        if not hasattr(self,"thisown"): _swig_setattr(self, CursorRow, 'thisown', 0)
        _swig_setattr(self, CursorRow,self.__class__,CursorRow)
_greendb.CursorRow_swigregister(CursorRowPtr)


