
#include <sstream>
#include <iostream>
#include <string>
#include <malloc.h>
#include <exception>

/*
 * 1. const object passed
 *      don't copy on init
 *      don't resize
 * 2. no objet passed
 *      don't resize
 * 3. int passed
 *      copy on init
 *      don't resize
 * 4. non-const string passed
 *      don't copy on init
 *      allow resize
 * 5. obstack passed
 *      don't copy on init
 *      allow resize with obstack functions
 *      
 *      new_ref(ptr,size); // don't copy
 *      new_copy(ptr,size);// copy
 *  new_empty() 
 */
class IllegalAllocateException:public std::exception {
public:
    const char * what () const throw() {
      return "ERROR: Illegal Allocation";
    }
  };
class ZatI {
  public:
    virtual void atleast (size_t size) = 0;
    virtual void * pvoid () = 0;
    virtual const char * type_name () const = 0;
    virtual const char * repr () const = 0;
    virtual const char * str() const = 0;
		virtual void set_size(size_t newsize) =0;
  };
/*
template < typename T>
class SizeOf {
	public:
		static size_t size_of(const T& t) {
			std::cout<<"SizeOf returning "<<sizeof(T)<<std::endl;
			return sizeof(T);
		}
};
class StrSize {
	public:
		static size_t size_of(const char* t) {
			size_t sz = strlen(t)+1;
			std::cout<<"StrSize returning "<<sz<<std::endl;
			return sz;
		}
};
*/
template < typename T, typename Mem,typename Size = SizeOf<T> >
class Zat: public ZatI {
    size_t _allocated;
    size_t _size;
    T * _ptr;
    bool _zat_allocated;
  public:
    Zat (): _allocated (0), _size (0), _ptr (NULL),_zat_allocated(false) {}
    static Zat * new_new(const T&ptr) {
      std::cout << "new_new: "<<std::endl;
      Zat * zat = new Zat ();
			zat->_ptr = new T(ptr);
      zat->_size = zat->_allocated = Size::size_of(ptr);
      std::cout << "after new_new: " << zat->repr () << std::endl;
			return zat;
		}
    static Zat * new_copy (const T&ptr) {
			return new_copy_size(ptr, Size::size_of(ptr));
		}
    static Zat * new_copy_size (const T& ptr, const size_t size) {
      std::cout << "new_copy: "<<std::endl;
      Zat * zat = new Zat ();
      zat->atleast (size);
      memcpy (zat->_ptr, &ptr, size);
      zat->_size = size;
      std::cout << "after new_copy: " << zat->repr () << std::endl;
			return zat;
    }
    static Zat * new_ref (T&ptr) {
			return new_ref_size(ptr, Size::size_of(ptr));
		}
    static Zat * new_ref_size (T & ptr, size_t size) {
      std::cout << "new_ref: "<<std::endl;
      Zat * zat = new Zat ();
      zat->_ptr = &ptr;
      zat->_size = size;
      zat->_allocated = size;
      std::cout << "after new_ref: " << zat->repr () << std::endl;
      return zat;
    }
    static Zat * new_empty () {
      std::cout << "new_empty: "<<std::endl;
      Zat * zat = new Zat ();
			return zat;
    }
		size_t size_of(const T& ptr) const {
			return Size::size_of(ptr);
		}
    const char * type_name () const {
        return typeid (*this).name ();
      }
    /*
     * Zat (T * ptr) { _ptr = ptr; } 
     */ 
		virtual ~Zat () {
      if ( (_ptr) && (_zat_allocated) ) {
          Mem::delbuf (_ptr);
        }
    }
    void atleast (size_t newsize) {
      if (_allocated < newsize) {
          if (_ptr == NULL) {
							_zat_allocated = true;
              _ptr = (T *) Mem::newbuf (newsize);
            } else {
              _ptr = (T *) Mem::resize (_ptr, newsize);
            }
          _allocated = newsize;
        }
    }
		/*
    void copy (T * ptr, size_t size) {
      atleast (size);
      memcpy (_ptr, ptr, size);
      _size = size;
    }*/
    size_t get_size () {
      return _size;
    }
    void set_size (size_t newsize) {
      _size = newsize;
    }
    void * pvoid () {
      return (void *) _ptr;
    }
    size_t get_allocated () {
      return _allocated;
    }
    void set_allocated (size_t newallocated) {
      _allocated = newallocated;
    }
    const char * repr () const {
        std::stringstream os;
				if (_ptr) {
        	os << type_name () << "(" << * _ptr << "," << _size << "," << _allocated << ")";
				} else {
        	os << type_name () << "(NULL, " << _size << "," << _allocated << ")";
				}
        return os.  str ().  c_str ();
      }
    /*
     * void fromstr (const char *str) { std::basic_istrstream<const char*> 
     * in (str); _ptr = Mem::newbuf (sizeof (T)); in >> *_ptr; } 
     */ 
		const char* str () const {
        std::stringstream os;
        os << * _ptr;
        return os.str().c_str ();
      }
    T & zat () {
      return *_ptr;
    }
    std::ostream & operator << (std::ostream & os) {
      os << *_ptr;
    }
		static const char* test() {
			return "It Worked!";
		}
  };

class Malloc {
  public:
    static bool resizeable () {
      return true;
    }
    static void * newbuf (size_t size) {
      std::cerr << "newbuf(" << size << ")" << std::endl;
      void* ptr =malloc (size);
      std::cerr << "got pointer (" << ptr << ")" << std::endl;
			return ptr;
    }
    static void * resize (void *ptr, size_t size) {
      std::cerr << "resize(" << size << ")" << std::endl;
      return realloc (ptr, size);
    }
    static void delbuf (void *ptr) {
      std::cerr << "delbuf()" << std::endl;
      free (ptr);
    }
  };

class
  NullAlloc {
  public:
    static bool resizeable () {
      return false;
    }
    static void * newbuf (size_t size) {
      throw new IllegalAllocateException ();
    }
    static void * resize (void *ptr, size_t size) {
      throw new IllegalAllocateException ();
    }
    static void delbuf (void *ptr) {
      throw new IllegalAllocateException ();
    }
  };

typedef Zat < int, Malloc> IntZat;
typedef Zat < int, NullAlloc> StaticIntZat;
typedef Zat < char *, Malloc, StrSize> StrZat;
typedef Zat < char *, NullAlloc, StrSize > StaticStrZat;

