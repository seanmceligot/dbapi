
import greendb
import sys

def addrow(args):
  table_name = args[0];
  args = args[1:]  

  env = greendb.GreenEnv(".")
  env.open()
  
  table = greendb.Table("people", env)
  row = table.new_row()
  i = 0
  for val in args:
    colname = table.get_col_name(i);
    print i,") ",colname,"=", val
    row.from_string(colname, val)
    i = i + 1
  table.save(row)
  table.close()
  env.close()

if __name__ == '__main__':
  addrow(sys.argv[1:])
