#include <Rdefines.h>
#include "ruby.h"

VALUE to_RubyObj(SEXP robj){
  VALUE ruby_obj;

  int *integers;
  char *strings;
  double *reals;

  switch (TYPEOF(robj)) {
  case NILSXP:
    ruby_obj = Qnil;
    break;
  case INTSXP:
    integers = INTEGER(robj); // R to C
    ruby_obj = INT2FIX(*integers); // C to Ruby

    //    if (TYPE(ruby_obj) == T_FIXNUM) printf("FIXNUM\n");

    //    printf("INT %i\n", *integers);
    break;
/*   case REALSXP: */
/*     reals = REAL(robj); // R to C */
/*     ruby_obj = INT2FIX(reals); // C to Ruby */
/*    break; */
  case STRSXP:
    ruby_obj = STRING_PTR(robj); // R to C
      // C to Ruby
    break;
  default:
    ruby_obj = Qtrue;
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
