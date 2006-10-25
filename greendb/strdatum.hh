#include "greendb/datum.hh"
#include <cwctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>

template<typename _CharT, typename _Traits = std::char_traits<_CharT>, 
           typename _Alloc = std::allocator<_CharT> >
class BasicStrDatum: public Datum {
	typedef _CharT CharT;
	typedef _Traits Traits;
	typedef _Alloc Alloc;
	friend class GreenDb;
	friend class Cursor;
  public:
  	//BasicStrDatum (T *ptr, u_int32_t size, u_int32_t allocated):Datum(ptr, size,allocated) {
		//}
  BasicStrDatum ():Datum() {
	}
  BasicStrDatum (const CharT* s):Datum() {
		size_t length = Traits::length(s);
		size_t size= (length+1)*(sizeof(CharT));
		CharT* ptr = (CharT*)malloc(size);
		set_ptr(Traits::copy(ptr,s,size));
		set_internal_allocated();
		set_size(size);
		set_allocated(size);
	}
	const CharT* set_value(const CharT* newvalue) {
		size_t length = Traits::length(newvalue);
		size_t size= (length+1)*(sizeof(CharT));
		if (get_ptr()) {
			atleast(size);
			set_size(size);
      CharT* ptr = (CharT*)get_ptr();
			Traits::copy(ptr, newvalue, length+1);
		} else {
			CharT* ptr = (CharT*)malloc(size);
			set_ptr(Traits::copy(ptr,newvalue,size));
			set_internal_allocated();
			set_size(size);
			set_allocated(size);
		}
		return value();
	}
	const CharT* operator=(const CharT* newvalue) {
		return set_value(newvalue);
	}
  CharT* operator*() {
    CharT* ptr = (CharT*)Dbt::get_data ();
		return ptr;
  };
  const CharT* value() const {
		return (CharT*)Dbt::get_data ();
  };
  const CharT* type_name () const {
   	return typeid (*this).name ();
  }
	virtual ~BasicStrDatum () {
			void* ptr = get_ptr();
      if ( (ptr) && (get_internal_allocated()) ) {
          free(ptr);
      }
			set_ptr(NULL);
    }
  virtual const char* repr () const {
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
		os << value();
    return strdup(os.str ().c_str ());
  }
	/*
  std::ostream & operator << (std::ostream & os) {
      os << value();
  }
	size_t size_of(const CharT& ptr) const {
		return Traits::size_of(ptr);
	}*/
};
typedef BasicStrDatum<char> StrDatum;
typedef BasicStrDatum<wchar_t> WStrDatum;

