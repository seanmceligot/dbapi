#! /usr/bin/perl -w
#
use greendb;
use strict;

sub mktable {
	my $env = greendb::new_GreenEnv(".");
	greendb::GreenEnv_open($env);
  my $table_name = $ARGV[0];
	my $table = greendb::new_Table($table_name, $env);

	my $schema = greendb::Table_get_schema($table);

  my $size = greendb::Schema_size($schema);
  my $pk = greendb::Schema_get_name($schema, 0);
  my $row = greendb::Table_first($table, $pk);
  while ($row) {
    for my $i (0 .. ($size -1) ) {
#my $value = greendb::Row_get_column_n(i);
      my $value = greendb::Row_to_string_n($row, $i);
      print $i .") ". $value . "\n";
      $i = $i + 1;
    }
    greendb::Row_close($row);
    $row = greendb::Table_next($table, $row, $pk);
  }
	greendb::Table_close($table);
	greendb::GreenEnv_close($env);
}

mktable();
