use greendb;
#use strict;

sub strtest {
	my $env = shift(@_);

	my $db = greendb::new_GreenDb($env, "perl.db", "strings");
	greendb::GreenDb_open_btree($db);
	
	my $key = greendb::new_StrDatum("a");
	my $val = greendb::new_StrDatum("one");
	greendb::GreenDb_put($db,$key,$val);
	
	my $get = greendb::new_StrDatum("");
	greendb::GreenDb_fetch($db,$key,$get);
	print "got: ",greendb::StrDatum_value($get), "\n";
	assert_equals(greendb::StrDatum_value($get), "one");

	greendb::GreenDb_close($db);
}
sub schema {
	my $env = shift(@_);
	my $db = greendb::new_GreenDb($env, "perl.db", "schema");
	greendb::GreenDb_open_btree($db);
	
	my $key = greendb::new_StrDatum("a");
	my $val = greendb::new_StrDatum("one");
	greendb::GreenDb_put($db,$key,$val);
}
sub assert_equals {
	my $first = shift(@_);
	my $second = shift(@_);
	if ( $first != $second ) {
		print "Assertion Failed: ", $first, " != ", $second, "\n";
	} else {
		print  $first, " == ", $second, "\n";
	}
}
sub inttest {
	my $env = shift(@_);
	my $db = greendb::new_GreenDb($env, "perl.db", "ints");
	greendb::GreenDb_open_btree($db);
	
	my $key = greendb::new_IntDatum(1);
	my $val = greendb::new_IntDatum(100);
	greendb::GreenDb_put($db,$key,$val);
	greendb::IntDatum_set_value($key,2);
	greendb::IntDatum_set_value($val,200);
	greendb::GreenDb_put($db,$key,$val);
	
	my $get = greendb::new_IntDatum(0);
	greendb::IntDatum_set_value($key,1);
	greendb::GreenDb_fetch($db,$key,$get);
	print "got: ",greendb::IntDatum_value($get), "\n";
	assert_equals(greendb::IntDatum_value($get), 100);
	
	greendb::IntDatum_set_value($key,2);
	greendb::GreenDb_fetch($db,$key,$get);
	print "got: ",greendb::IntDatum_value($get), "\n";
	assert_equals(greendb::IntDatum_value($get), 200);
	
	greendb::GreenDb_close($db);
}
sub table_test {
	my $env = shift(@_);
	my $table = greendb::new_Table("perltbl", $env);
	my $schema = greendb::Table_get_schema($table);
	greendb::Schema_add_column($schema, "userid", greendb::TypeMap_STRING, 0 );
	greendb::Schema_add_column($schema, "fname", greendb::TypeMap_STRING, 0);
	greendb::Schema_add_column($schema, "lname", greendb::TypeMap_STRING, 0);
	
#	my $pk = greendb::new_StrDatum("smceligot");
#	my $row = greendb::new_Row($table, $pk);
#	greendb::Row_set($row, "userid", $pk);
#	my $fname = greendb::new_StrDatum("Sean");
#	greendb::Row_set($row, "fname", $fname);
#	my $lname = greendb::new_StrDatum("McEligot");
#	greendb::Row_set($row, "lname", $lname);
#	greendb::Table_save($table, $row);	
#	
#	my $cursor = greendb::Table_cursor($table,"userid");
#	my $key = greendb::new_StrDatum("");
#	my $val = greendb::new_StrDatum("");
#	while(greendb::Cursor_next($cursor,$key,$val) ==0) {
#			print "cursor->next: key(",greendb::StrDatum_value($key), ")\n";
#			print "cursor->next: val(",greendb::StrDatum_value($val), ")\n";
#	}
#	greendb::Cursor_close($cursor);
	
	my $schema = greendb::Table_close($table);
}
	my $env = greendb::new_GreenEnv(".");
	greendb::GreenEnv_open($env);
	strtest($env);
	inttest($env);
	table_test($env);
	greendb::GreenEnv_close($env);
