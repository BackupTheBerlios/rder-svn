require "mkmf"
$CPPFLAGS += "-I/home/shinamon/src/source/R-2.1.0/src/include"
$LOCAL_LIBS += "-lR"
create_makefile("RdeR")
