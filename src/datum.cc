#include "greendb/datum.hh"
#include "greendb/debug.hh"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Datum::Datum (DataType type):Dbt (),_type(type), _internal_allocated(false) {
}
Datum::Datum (DataType type, u_int32_t size):Dbt (),_type(type), _internal_allocated(false) {
  atleast(size);
}
Datum::Datum (DataType type, void *ptr, u_int32_t size, u_int32_t allocated):Dbt (ptr, size),_type(type), _internal_allocated(false) {
 set_ulen (allocated);
}
Datum::~Datum() {
  free_ptr();
}
void Datum::free_ptr() {
  void* ptr = get_ptr();
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
          set_ptr( malloc(newsize) );
        } else {
          set_ptr( realloc(get_ptr(), newsize) );
          _internal_allocated = true;
        }
      set_allocated ( newsize);
      set_size( newsize);
    }
}
char * Datum::repr() const{
	TypeMap tm;
   return g_strdup_printf("Datum::new_%s(%s)", tm.get_type_name(_type), this->to_string());
}
char * Datum::str() const{
   return to_string();
}
char * Datum::c_str() const{
   return to_string();
}
Datum* Datum::set_int(int newvalue){
      size_t size = sizeof(int);
      if (get_ptr()) {
        int* ptr = (int*)get_ptr();
        std::_Destroy<int>(ptr);
        atleast(size);
				set_size(size);
        std::_Construct<int>(ptr, newvalue);
      } else {
        atleast(size);
        set_ptr( new int(newvalue) );
      }
      return this;
}
Datum* Datum::set_string(const char* newvalue){
    g_return_val_if_fail(newvalue != NULL, NULL);
		size_t length = strlen(newvalue);
		size_t size= (length+1)*(sizeof(char));
		if (get_ptr()) {
			atleast(size);
			set_size(size);
      char* ptr = (char*)get_ptr();
			strncpy(ptr, newvalue, length+1);
		} else {
			set_ptr(strdup(newvalue));
			set_internal_allocated();
			set_size(size);
			set_allocated(size);
		}
    return this;
}
int Datum::get_int() const {
  g_return_val_if_fail(const_ptr() != NULL, 0);
  return *((int*)const_ptr());
}
const char* Datum::get_string() const{
  return (const char*)const_ptr();
}
void Datum::from_string(const char* value){
  g_return_if_fail(value != NULL);
  switch(_type) {
    case TYPE_STRING:
       set_string(value);
       break;
    case TYPE_INT:
       set_int(atoi(value));
       break;
    default:
      g_message("unknown type, cannot set from string");
  }
}
/**
 * caller must free pointer
 */
char* Datum::to_string() const {
  g_return_val_if_fail(const_ptr() != NULL, 0);
  switch(_type) {
    case TYPE_STRING:
      return strdup(get_string());
    case TYPE_INT:
      return g_strdup_printf("%d", get_int());
  }
  g_message("unknown type, cannot get to string");
  return NULL;
}
