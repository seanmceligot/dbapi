#! /usr/bin/perl -w
#
use greendb;
use strict;

sub desc {
	my $env = greendb::new_GreenEnv(".");
	greendb::GreenEnv_open($env);
  my $table_name = $ARGV[0];
  print "creating " . $table_name . "\n";
	my $table = greendb::new_Table($table_name, $env);
	my $schema = greendb::Table_get_schema($table);

  my $size = greendb::Schema_size($schema);
  for my $i (0 .. ($size -1) ) {
    my $type = greendb::Schema_get_type_n($schema, $i);
    my $name = greendb::Schema_get_name($schema, $i);
    print $i . " " . $type . " " . $name . "\n";
  }
	greendb::Table_close($table);
	greendb::GreenEnv_close($env);
}

desc();
