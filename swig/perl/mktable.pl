#! /usr/bin/perl -w
#
use greendb;
use strict;

sub mktable {
	my $env = greendb::new_GreenEnv(".");
	greendb::GreenEnv_open($env);
  my $table_name = $ARGV[0];
  print "creating " . $table_name . "\n";
	my $table = greendb::new_Table($table_name, $env);
	my $schema = greendb::Table_get_schema($table);

  my $size = greendb::Schema_size($schema);
  if ($size > 0) {
    print $size . " table already created";
    return;
  }
 
  my $i = 1;
  while ($i < $#ARGV) {
    print "arg ". $i . " " . $ARGV[$i] . "\n";
    my $type = $ARGV[$i];
    $i = $i + 1;
    print "arg ". $i . " " . $ARGV[$i] . "\n";
    my $name = $ARGV[$i];
    $i = $i + 1;
    print "adding ". $type . " " . $name . "\n";
    greendb::Schema_add_column($schema, $name, $type, 0 );
  }
	greendb::Table_close($table);
	greendb::GreenEnv_close($env);
}

mktable();
