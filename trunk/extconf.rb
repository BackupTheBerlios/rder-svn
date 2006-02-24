require 'mkmf'

$CPPFLAGS += "-I/usr/local/lib/R/include"
$LDFLAGS += "-L/usr/local/lib/R/lib"
$LOCAL_LIBS += "-lR"

create_makefile('RdeR')

