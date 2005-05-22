#include <Rdefines.h>
#include "ruby.h"

VALUE to_RubyObj(SEXP robj){
  VALUE ruby_obj;

  int *integers;

  switch (TYPEOF(robj)) {
  case INTSXP:
    integers = INTEGER(robj); // R to C
    ruby_obj = INT2NUM(*integers); // C to Ruby

    //    if (TYPE(ruby_obj) == T_FIXNUM) printf("FIXNUM\n");

    //    printf("INT %i\n", *integers);
    break;
  }

  return (ruby_obj);
}

SEXP to_RObj(VALUE ruby_obj) {
  SEXP robj;

  if (!ruby_obj) {
    return (NULL);
  }
}
