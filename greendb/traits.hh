#include <string>

class IllegalAllocateException:public std::exception {
public:
  const char * what () const throw() {
    return "ERROR: Illegal Allocation";
  }
};

template < typename T>
class DatumTraits {
public:
	static void* pvoid(const T* t ) {
			return t;
	}
	static T* from_void(void* ptr) {
			return (T*)ptr;
	}
	static size_t size_of(const T& t) {
		//std::cout<<"SizeOf returning "<<sizeof(T)<<std::endl;
		return sizeof(T);
	}
};

/* string specialization
template <>
class DatumTraits <std::string >{
public:
	static void* pvoid(const std::string* s) {
			return s->c_str();
	}
	static string* from_void(void* ptr) {
			return (string*)ptr;
	}
	static size_t size_of(const string& s) {
		size_t sz = s->length()+1;
		std::cout<<"StrSize returning "<<sz<<std::endl;
		return sz;
	}
};
*/
// char* specialization
template <>
class DatumTraits <char*>{
	public:
	static void* pvoid(const char* s) {
			return (void*)s;
	}
	static char* from_void(char* ptr) {
			return ptr;
	}
	static size_t size_of(const char* t) {
		size_t sz = strlen(t)+1;
		std::cout<<"StrSize returning "<<sz<<std::endl;
		return sz;
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

