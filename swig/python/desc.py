import greendb
import sys

def desc(table_name):
	env = greendb.GreenEnv(".")
	env.open()
	
	table = greendb.Table("testtable", env)
	schema = table.get_schema()
	print table.get_name()	
	i = 0
	for i in range(0, schema.size()):
		type = schema.get_type_n(i)
		name = schema.get_name(i)
		print i, type, name
	
	table.close()
	env.close()

if __name__ == '__main__':
	desc(sys.argv[1])
