require 'mkmf'

$LDFLAGS = '-lfoma'
have_func('fsm_read_binary_file')

create_makefile "foma/foma"
