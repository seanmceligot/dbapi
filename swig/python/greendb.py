# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _greendb
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


class GreenDb(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GreenDb, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GreenDb, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_GreenDb(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _greendb.delete_GreenDb
    __del__ = lambda self : None;
    def open(*args): return _greendb.GreenDb_open(*args)
    def open_unknown(*args): return _greendb.GreenDb_open_unknown(*args)
    def open_queue(*args): return _greendb.GreenDb_open_queue(*args)
    def open_recno(*args): return _greendb.GreenDb_open_recno(*args)
    def open_hash(*args): return _greendb.GreenDb_open_hash(*args)
    def open_btree(*args): return _greendb.GreenDb_open_btree(*args)
    def dbfile(*args): return _greendb.GreenDb_dbfile(*args)
    def name(*args): return _greendb.GreenDb_name(*args)
    def put(*args): return _greendb.GreenDb_put(*args)
    def fetch(*args): return _greendb.GreenDb_fetch(*args)
    def cursor(*args): return _greendb.GreenDb_cursor(*args)
    def close(*args): return _greendb.GreenDb_close(*args)
GreenDb_swigregister = _greendb.GreenDb_swigregister
GreenDb_swigregister(GreenDb)

class GreenEnv(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, GreenEnv, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, GreenEnv, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_GreenEnv(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _greendb.delete_GreenEnv
    __del__ = lambda self : None;
    def open(*args): return _greendb.GreenEnv_open(*args)
    def close(*args): return _greendb.GreenEnv_close(*args)
    def home(*args): return _greendb.GreenEnv_home(*args)
GreenEnv_swigregister = _greendb.GreenEnv_swigregister
GreenEnv_swigregister(GreenEnv)

class Datum(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Datum, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Datum, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_Datum(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _greendb.delete_Datum
    __del__ = lambda self : None;
Datum_swigregister = _greendb.Datum_swigregister
Datum_swigregister(Datum)

class StrDatum(Datum):
    __swig_setmethods__ = {}
    for _s in [Datum]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, StrDatum, name, value)
    __swig_getmethods__ = {}
    for _s in [Datum]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, StrDatum, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_StrDatum(*args)
        try: self.this.append(this)
        except: self.this = this
    def type_name(*args): return _greendb.StrDatum_type_name(*args)
    __swig_destroy__ = _greendb.delete_StrDatum
    __del__ = lambda self : None;
    def repr(*args): return _greendb.StrDatum_repr(*args)
    def value(*args): return _greendb.StrDatum_value(*args)
    def set_value(*args): return _greendb.StrDatum_set_value(*args)
StrDatum_swigregister = _greendb.StrDatum_swigregister
StrDatum_swigregister(StrDatum)

class IntDatum(Datum):
    __swig_setmethods__ = {}
    for _s in [Datum]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntDatum, name, value)
    __swig_getmethods__ = {}
    for _s in [Datum]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, IntDatum, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_IntDatum(*args)
        try: self.this.append(this)
        except: self.this = this
    def type_name(*args): return _greendb.IntDatum_type_name(*args)
    __swig_destroy__ = _greendb.delete_IntDatum
    __del__ = lambda self : None;
    def repr(*args): return _greendb.IntDatum_repr(*args)
    def value(*args): return _greendb.IntDatum_value(*args)
    def set_value(*args): return _greendb.IntDatum_set_value(*args)
IntDatum_swigregister = _greendb.IntDatum_swigregister
IntDatum_swigregister(IntDatum)

class Cursor(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Cursor, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Cursor, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _greendb.delete_Cursor
    __del__ = lambda self : None;
    def first(*args): return _greendb.Cursor_first(*args)
    def last(*args): return _greendb.Cursor_last(*args)
    def find(*args): return _greendb.Cursor_find(*args)
    def next(*args): return _greendb.Cursor_next(*args)
    def close(*args): return _greendb.Cursor_close(*args)
Cursor_swigregister = _greendb.Cursor_swigregister
Cursor_swigregister(Cursor)

class Row(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Row, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Row, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_Row(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _greendb.delete_Row
    __del__ = lambda self : None;
    def close(*args): return _greendb.Row_close(*args)
    def getpk(*args): return _greendb.Row_getpk(*args)
    def set_n(*args): return _greendb.Row_set_n(*args)
    def set(*args): return _greendb.Row_set(*args)
    def from_string_n(*args): return _greendb.Row_from_string_n(*args)
    def from_string(*args): return _greendb.Row_from_string(*args)
    def to_string_n(*args): return _greendb.Row_to_string_n(*args)
    def to_string(*args): return _greendb.Row_to_string(*args)
    def get_column_n(*args): return _greendb.Row_get_column_n(*args)
    def get_column(*args): return _greendb.Row_get_column(*args)
    def get_col_no(*args): return _greendb.Row_get_col_no(*args)
    def get_existing_column(*args): return _greendb.Row_get_existing_column(*args)
    def size(*args): return _greendb.Row_size(*args)
Row_swigregister = _greendb.Row_swigregister
Row_swigregister(Row)

class Table(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Table, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Table, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_Table(*args)
        try: self.this.append(this)
        except: self.this = this
    def get_schema(*args): return _greendb.Table_get_schema(*args)
    def close(*args): return _greendb.Table_close(*args)
    __swig_destroy__ = _greendb.delete_Table
    __del__ = lambda self : None;
    def get_name(*args): return _greendb.Table_get_name(*args)
    def save(*args): return _greendb.Table_save(*args)
    def index(*args): return _greendb.Table_index(*args)
    def fetch(*args): return _greendb.Table_fetch(*args)
    def new_row(*args): return _greendb.Table_new_row(*args)
    def cursor(*args): return _greendb.Table_cursor(*args)
    def first(*args): return _greendb.Table_first(*args)
    def last(*args): return _greendb.Table_last(*args)
    def next(*args): return _greendb.Table_next(*args)
    def get_col_name(*args): return _greendb.Table_get_col_name(*args)
Table_swigregister = _greendb.Table_swigregister
Table_swigregister(Table)

class Schema(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Schema, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Schema, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def add_column(*args): return _greendb.Schema_add_column(*args)
    def add_columns(*args): return _greendb.Schema_add_columns(*args)
    def get_type_n(*args): return _greendb.Schema_get_type_n(*args)
    def get_type(*args): return _greendb.Schema_get_type(*args)
    def get_col_no(*args): return _greendb.Schema_get_col_no(*args)
    def get_name(*args): return _greendb.Schema_get_name(*args)
    def size(*args): return _greendb.Schema_size(*args)
    __swig_destroy__ = _greendb.delete_Schema
    __del__ = lambda self : None;
Schema_swigregister = _greendb.Schema_swigregister
Schema_swigregister(Schema)

class TypeMap(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TypeMap, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TypeMap, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
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
    __swig_destroy__ = _greendb.delete_TypeMap
    __del__ = lambda self : None;
TypeMap_swigregister = _greendb.TypeMap_swigregister
TypeMap_swigregister(TypeMap)
TypeMap_get_type_map = _greendb.TypeMap_get_type_map

class CursorRow(Row):
    __swig_setmethods__ = {}
    for _s in [Row]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CursorRow, name, value)
    __swig_getmethods__ = {}
    for _s in [Row]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CursorRow, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _greendb.new_CursorRow(*args)
        try: self.this.append(this)
        except: self.this = this
    def get_cursor(*args): return _greendb.CursorRow_get_cursor(*args)
    __swig_destroy__ = _greendb.delete_CursorRow
    __del__ = lambda self : None;
CursorRow_swigregister = _greendb.CursorRow_swigregister
CursorRow_swigregister(CursorRow)



