#! /usr/bin/perl -w
#
use greendb;
use strict;

sub mktable {
	my $env = greendb::new_GreenEnv(".");
	greendb::GreenEnv_open($env);
  my $table_name = $ARGV[0];
	my $table = greendb::new_Table($table_name, $env);

  my $row = greendb::Table_new_row($table);
	my $schema = greendb::Table_get_schema($table);

  my $size = greendb::Schema_size($schema);
  for my $i (0 .. ($size -1) ) {
    my $value = $ARGV[$i+1];
    print $i .") adding ". $value . "\n";
    greendb::Row_from_string_n($row, $i, $value);
    $i = $i + 1;
  }
	greendb::Table_save($table, $row);
	greendb::Table_close($table);
	greendb::GreenEnv_close($env);
}

mktable();
