
import greendb
import sys

def addrow(args):
  table_name = args[0];
  args = args[1:]  

  env = greendb.GreenEnv(".")
  env.open()
  
  table = greendb.Table("testtable", env)
  row = table.new_row()
  i = 0
  for val in args:
    print i, ")", val
    row.from_string_n(i, val)
    i = i + 1

  table.save(row)
  row.close(row)
  table.close()
  env.close()

if __name__ == '__main__':
  addrow(sys.argv[1:])
