#include "greendb/xml.hh"

void to_xml(Schema* schema, Row* row, std::ostream& out) {
	for (size_t i = 0; i < schema->size() ;i++) {
		const char* name = schema->get_name(i);
		out<<"<"<<name<<">";
    out<<row->to_string(i);
		out<<"</"<<name<<">"<<std::endl;
  }
}
