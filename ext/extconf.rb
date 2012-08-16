require 'mkmf'
$LDFLAGS = '-lfoma'
dir_config("foma")
create_makefile "foma"
