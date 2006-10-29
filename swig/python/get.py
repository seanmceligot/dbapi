import greendb
import sys

def get(env, table_name):
    
    table = greendb.Table("people", env)
    schema = table.get_schema()
    print table.get_name()
    pk = schema.get_name(0)
    row = table.first(pk)
    while(row != None):
        for i in range(0, row.size()):
            cc = row.get_column_n(i)
            print cc,")", row.to_string_n(i)
        row.close()
        row = table.next(row, pk)
    
    print "closing table"
    table.close()

if __name__ == '__main__':
    env = greendb.GreenEnv(".")
    env.open()
    get(env, sys.argv[1])
    print "closing env"
    env.close()
    print "done"

