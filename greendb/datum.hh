#ifndef __DATUM_HH
#define __DATUM_HH

#include <db_cxx.h>
#include "greendb/memory.hh"
#include "greendb/typemap.hh"

class Datum:protected Dbt {
  bool _internal_allocated;
  DataType _type;
  friend class GreenDb;
  friend class Cursor;
public:
  Datum (DataType type, u_int32_t size);
  Datum (DataType type);
  Datum (DataType type, void *ptr, u_int32_t size, u_int32_t allocated);
  virtual ~Datum();
  void *get_ptr();
  void set_ptr(void* ptr);
  u_int32_t get_size () const;
  u_int32_t get_allocated () const;
  void atleast_size ();
  void atleast (size_t newsize);
  //virtual const char * type_name () const = 0;
  //virtual const char * str() const = 0;
/**
 * caller must free pointer
 */
  const char * repr() const;
/**
 * caller must free pointer
 */
  const char * str() const;
/**
 * caller must free pointer
 */
  const char * c_str() const;
  Datum* set_int(int value);
  Datum* set_string(const char* value);
  int get_int() const;
  const char* get_string() const;
  void from_string(const char* value);
/**
 * caller must free pointer
 */
  const char* to_string() const;
	bool isset() const { return const_ptr() != NULL;};
protected:
  void set_internal_allocated();
  u_int32_t get_internal_allocated();
  void set_size (u_int32_t size);
  void set_allocated (u_int32_t allocated);
  void set_db_flags(u_int32_t flags);
  void free_ptr();
  const void *const_ptr() const;
};

/*template < typename T, typename Mem,typename DatumTraits = DatumTraits<T> >
class DatumT: public Datum {
  friend class GreenDb;
  friend class Cursor;
  public:
    //DatumT (T *ptr, u_int32_t size, u_int32_t allocated):Datum(ptr, size,allocated) {
    //}
    DatumT ():Datum() {
    }
    DatumT (const T &ptr):Datum() {
      set_ptr(new T(ptr));
      set_internal_allocated();
      u_int32_t size =DatumTraits::size_of(ptr);
      set_size(size);
      set_allocated(size);
    }
    const T& set_value(const T& newvalue) {
      size_t size = DatumTraits::size_of(newvalue);
      if (get_ptr()) {
        T* ptr = (T*)get_ptr();
        std::_Destroy<T>(ptr);
        //greendb_free(ptr);
        atleast(size);
				set_size(size);
        std::_Construct<T>(ptr, newvalue);
      } else {
        atleast(size);
        set_ptr( new T(newvalue) );
      }
      std::cout << "after set_value: " << repr () << std::endl;
      return value();
    }
    const T& operator=(const T& newvalue) {
      return set_value(newvalue);
    }
  const T& value() const {
    const T* ptr = (T*)Dbt::get_data ();
    return *ptr;
  }
  const char * type_name () const {
     return typeid (*this).name ();
  }
  virtual ~DatumT () {
    free_ptr();
  }
  virtual const char * repr () const {
    std::stringstream os;
    if (const_ptr()) {
      os << type_name()<<"("<< value() << ")";
    } else {
      os << type_name () << "(NULL, " << get_size() << "," << get_allocated() << ")";
    }
    return strdup(os.str ().c_str ());
  }
  virtual const char* str () const {
    std::stringstream os;
    if (const_ptr()) {
      os << value();
    } else {
      os << type_name () << "("<<get_size()<<","<< get_allocated()<<")";
    }
    return strdup(os.str ().c_str ());
  }
  };
*/
class StrDatum: public Datum {
public:
	StrDatum():Datum(TYPE_STRING) {
	}
	StrDatum(const char* value):Datum(TYPE_STRING) {
		set_string(value);
	}
	const char* value() const {
		return get_string();
	}
};
class IntDatum: public Datum {
public:
	IntDatum():Datum(TYPE_INT) {
	}
	IntDatum(int value):Datum(TYPE_INT) {
		set_int(value);
	}
	int value() const {
		return get_int();
	}
};
class DataTypeDatum: public Datum {
public:
	DataTypeDatum():Datum(TYPE_INT) {
	}
	DataTypeDatum(DataType value):Datum(TYPE_INT) {
		set_int(value);
	}
	DataType value() const {
		return (DataType)get_int();
	}
};
//typedef DatumT < int, Malloc> IntDatum;
//typedef DatumT < DataType, Malloc> DataTypeDatum;

//std::ostream & operator << (std::ostream & os, const Datum & datum);
#endif
