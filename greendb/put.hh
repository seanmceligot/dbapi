
#include <sstream>
#include <iostream>
#include <string>
#include <malloc.h>
#include <exception>
#include <typeinfo>
#include "traits.hh"

class PutI {
  public:
    virtual void * pvoid () = 0;
    virtual const char * type_name () const = 0;
    virtual const char * repr () const = 0;
    virtual const char * str() const = 0;
    virtual const size_t get_size() const = 0;
  };
template < typename T, typename Mem,typename DatumTraits = DatumTraits<T> >
class Put: public PutI {
    size_t _allocated;
    size_t _size;
    T * _ptr;
    bool _put_allocated;
  public:
    Put (): _allocated (0), _size (0), _ptr (NULL),_put_allocated(false) {}
    static Put * new_new(const T&ptr) {
      std::cout << "new_new: "<<std::endl;
      Put * put = new Put ();
			put->_ptr = new T(ptr);
      put->_size = put->_allocated = DatumTraits::size_of(ptr);
      std::cout << "after new_new: " << put->repr () << std::endl;
			return put;
		}
		const size_t get_size() const {
			return _size;
		}
		size_t size_of(const T& ptr) const {
			return DatumTraits::size_of(ptr);
		}
    const char * type_name () const {
        return typeid (*this).name ();
      }
    /*
     * Put (T * ptr) { _ptr = ptr; } 
     */ 
		virtual ~Put () {
      if ( (_ptr) && (_put_allocated) ) {
          Mem::delbuf (_ptr);
        }
    }
    size_t get_size () {
      return _size;
    }
    void * pvoid () {
      return (void *) _ptr;
    }
    size_t get_allocated () {
      return _allocated;
    }
    const char * repr () const {
        stringstream os;
				if (_ptr) {
        	os << type_name () << "(" << * _ptr << "," << _size << "," << _allocated << ")";
				} else {
        	os << type_name () << "(NULL, " << _size << "," << _allocated << ")";
				}
        return os.  str ().  c_str ();
      }
    /*
     * void fromstr (const char *str) { basic_istrstream<const char*> 
     * in (str); _ptr = Mem::newbuf (sizeof (T)); in >> *_ptr; } 
     */ 
		const char* str () const {
        stringstream os;
        os << * _ptr;
        return os.str().c_str ();
      }
    T & put () {
      return *_ptr;
    }
    ostream & operator << (ostream & os) {
      os << *_ptr;
    }
		static const char* test() {
			return "It Worked!";
		}
  };

typedef Put < int, Malloc> IntPut;
typedef Put < char *, Malloc> StrPut;

