import greendb
import sys

class Browser:
  def desc(self, table_name, grid):
    env = greendb.GreenEnv(".")
    env.open()
    
    table = greendb.Table("testtable", env)
    schema = table.get_schema()
    print table.get_name()  
    i = 0
    grid.CreateGrid(20, schema.size())
    for i in range(0, schema.size()):
      type = schema.get_type_n(i)
      name = schema.get_name(i)
      print i, type, name
      grid.SetLabelValue(0,name,i)
    table.close()
    env.close()
  def list(self, table_name, grid):
    env = greendb.GreenEnv(".")
    env.open()
    
    table = greendb.Table("testtable", env)
    schema = table.get_schema()
    print table.get_name()
    pk = schema.get_name(0)
    row = table.first(pk)
    while(row != None):
      for i in range(0, row.size()):
        val = row.get_column_n(i)
        print i,")", row.to_string_n(i)
      row.close()
      row = table.next(row, pk)
    table.close()
    env.close()
