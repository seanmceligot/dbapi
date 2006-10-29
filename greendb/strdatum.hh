#include "greendb/datum.hh"
#include <cwctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
/*
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
  BasicStrDatum ():Datum(TYPE_STRING) {
	}
  BasicStrDatum (const CharT* s):Datum(TYPE_STRING) {
		size_t length = Traits::length(s);
		size_t size= (length+1)*(sizeof(CharT));
		CharT* ptr = (CharT*)malloc(size);
		set_ptr(Traits::copy(ptr,s,size));
		set_internal_allocated();
		set_size(size);
		set_allocated(size);
	}
	const CharT* set_value(const CharT* newvalue) {
		return set_string(newvalue);
	}
	const Datum* operator=(const CharT* newvalue) {
		return Datum::set_string(newvalue);
	}
  const CharT* value() const {
		return get_string();
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
};
typedef BasicStrDatum<char> StrDatum;
typedef BasicStrDatum<wchar_t> WStrDatum;
*/
