#include "greendb/datum.hh"
#include "greendb/debug.hh"

static void print_void(std::ostream & os, const void* ptr, const size_t len) {
  size_t count = len > 74?74:len;
  char* p = (char*)ptr;
  for (size_t i = 0; i < count;i++) {
    int ch = p[i];
    if ( isalnum(ch) ) {
      os << (char)ch;
    } else {
      os << '<'<<ch<<'>';
    }
  }
  if ( len > 74 ) {
      os << "...";
  }
}


Datum::Datum ():Dbt (),_internal_allocated(false) {
  //debug<<"Datum()"<<std::endl;
}
Datum::Datum (u_int32_t size):Dbt (),_internal_allocated(false) {
  //debug<<"Datum("<<size<<")"<<std::endl;
  atleast(size);
}
Datum::Datum (void *ptr, u_int32_t size, u_int32_t allocated):Dbt (ptr, size),_internal_allocated(false) {
  //debug<<"Datum(";
  print_void(std::cerr, ptr, size);
	//debug<<")"<<std::endl;
 set_ulen (allocated);
}
Datum::~Datum() {
  //debug<<"~Datum()"<<std::endl;
  free_ptr();
}
void Datum::free_ptr() {
  void* ptr = get_ptr();
   //debug<<ptr<<_internal_allocated<<std::endl;
   if ( (ptr) && (_internal_allocated) ) {
       free(ptr);
   }
  set_ptr(NULL);
  set_size(0);
  set_allocated(0);
}
const void *Datum::const_ptr() const {
  return Dbt::get_data ();
};
void *Datum::get_ptr() {
  return Dbt::get_data ();
};
u_int32_t Datum::get_size () const {
  return Dbt::get_size ();
};
u_int32_t Datum::get_allocated () const {
  return Dbt::get_ulen ();
};

void Datum::atleast_size() {
  atleast(get_size());
};
void Datum::set_ptr(void* ptr) {
  return Dbt::set_data (ptr);
};
void Datum::set_db_flags(u_int32_t flags) {
  Dbt::set_flags(flags);
};
void Datum::set_size (u_int32_t size) {
  Dbt::set_size (size);
};
void Datum::set_allocated (u_int32_t allocated) {
  Dbt::set_ulen (allocated);
};
u_int32_t Datum::get_internal_allocated() {
  return _internal_allocated;
}
void Datum::set_internal_allocated() {
  _internal_allocated = true;
}
void Datum::atleast (size_t newsize) {
  if (get_allocated() < newsize) {
      if (get_ptr() == NULL) {
          _internal_allocated = true;
          //debug<<"atleast: "<<newsize<<std::endl;
          set_ptr( malloc(newsize) );
        } else {
          //debug<<"atleast: realloc "<<get_ptr()<<" "<<newsize<<std::endl;
          set_ptr( realloc(get_ptr(), newsize) );
          _internal_allocated = true;
        }
      set_allocated ( newsize);
      set_size( newsize);
    }
}
std::ostream & operator << (std::ostream & os, const Datum & datum) {
  os <<"Datum(";
  print_void(os, datum.const_ptr(), datum.get_size());
  os<<")"; 
  return os;
}
