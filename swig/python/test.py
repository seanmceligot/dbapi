import greendb

env = greendb.GreenEnv(".")
env.open()

db = greendb.GreenDb(env, "python.db", "data")
db.open_btree()

key = greendb.StrDatum("a")
val = greendb.StrDatum("one")

db.put(key,val)

get = greendb.StrDatum("")
db.fetch(key, get)

print "got: ",get.value(),"\n"

db.close()

table = greendb.Table("perltbl", env)
schema = table.get_schema()
schema.add_column("userid", greendb.TypeMap.STRING, 0 )
schema.add_column("fname", greendb.TypeMap.STRING, 0)
schema.add_column("lname", greendb.TypeMap.STRING, 0)
	
pk = greendb.StrDatum("smceligot")
row = greendb.Row(table, pk)
row.set("userid", pk)
dfn = greendb.StrDatum("Sean")
dln = greendb.StrDatum("McEligot")
row.set("fname", dfn )
row.set("lname",dln )
table.save(row)

row = table.fetch(pk)
for i in range(schema.size()):
	print  schema.get_name(i), "\t",

print

for i in range(schema.size()):
	colname = schema.get_name(i)
	val = row.get_column(colname)
	print row.to_string(colname, str), "\t",

table.close()

env.close()


