import greendb
import sys

def mktable(args):
	table_name = args[0];

	env = greendb.GreenEnv(".")
	env.open()
	
	table = greendb.Table(table_name, env)
	schema = table.get_schema()
	size = schema.size()
	if (size != 0):
		print size, "table already created"
		return
	args = args[1:]	
	i = 0
	while i < len(args):
		type = int(args[i])
		i = i + 1
		name = args[i]
		i = i + 1
		print "adding ", type, name
		schema.add_column(name, type, 0)
	
	table.close()
	env.close()

if __name__ == '__main__':
	mktable(sys.argv[1:])
