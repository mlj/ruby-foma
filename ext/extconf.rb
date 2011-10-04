require 'mkmf'
$LDFLAGS = '-lfoma'
create_makefile "foma"
