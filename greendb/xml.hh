#ifndef __XML_HH
#define __XML_HH

#include <iostream>
#include "greendb/row.hh"
#include "greendb/schema.hh"

void to_xml(Schema* schema, Row* row, std::ostream& out);

#endif
