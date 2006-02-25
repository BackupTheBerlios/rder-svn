#include "rder.h"

VALUE to_ubyObj(SEXP robj){
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
    //    strings = STRING_PTR(robj); // R to C
      // C to Ruby
    break;
  default:
    ruby_obj = Qtrue;
    break;
  }

  return (ruby_obj);
}

static VALUE 
to_RubyObj(VALUE self)
{

  int i, *integers;

  VALUE ruby_hash;
  SEXP robj;
  struct robj *ptr;

  Data_Get_Struct(self, struct robj, ptr);
  robj = ptr->RObj;
  int len = GET_LENGTH(robj);
printf("%i\n", len);  
  ruby_hash = rb_funcall(rb_cHash, rb_intern("new"), 0);

  for (i=0; i<len; i++) {
    switch(TYPEOF(robj)) 
      {
      case NILSXP:
	rb_funcall(ruby_hash, rb_intern("store"), 2, INT2FIX(i), Qnil);
	break;
      case SYMSXP:
	break;
      case LISTSXP:
	break;
      case CLOSXP:
	break;
      case ENVSXP:
	break;
      case PROMSXP:
	break;
      case LANGSXP:
	break;
      case SPECIALSXP:
	break;
      case BUILTINSXP:
	break;
      case CHARSXP:
	break;
      case LGLSXP:
	integers = INTEGER(robj);
	if (integers[i] == NA_INTEGER) {

	} else {
	  
	}
	break;
      case INTSXP:
	integers = INTEGER(robj);
	integers[i] = INT2FIX(integers[i]);
	break;
      case REALSXP:
	break;
      case CPLXSXP:
	break;
      case STRSXP:
	break;
      case DOTSXP:
	break;
      case ANYSXP:
	break;
      case VECSXP:
	break;
      case EXPRSXP:
	break;
      case BCODESXP:
	break;
      case EXTPTRSXP:
	break;
      case WEAKREFSXP:
	break;
      case RAWSXP:
	break;
      case FUNSXP:
	break;
      default:
	ruby_hash = Qtrue;
	break;
      }
  }
  
  return ruby_hash;
}

static VALUE to_RObj(VALUE self, VALUE obj) {

  SEXP robj;
  struct robj *ptr;

  Data_Get_Struct(obj, struct robj, ptr);
  robj = ptr->RObj;

  int type = TYPE(self);

  switch (type)
    {
    case T_NIL:
      robj = R_NilValue;
    case T_FIXNUM:
      PROTECT(robj = NEW_INTEGER(1));
      NUMERIC_DATA(robj)[0] = FIX2LONG(self);
    default:
      Qnil;
    }
  return obj;
}

