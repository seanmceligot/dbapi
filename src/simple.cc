#include "greendb/simple.hh"

SimpleInterface::SimpleInterface(const char* home) : _env(home),_table(NULL), _row(NULL) {
}
