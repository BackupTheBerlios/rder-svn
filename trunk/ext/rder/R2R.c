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

  VALUE ruby_hash, ruby_arr, ruby_robj;
  SEXP robj;
  struct robj *ptr;
  SEXP str_p;

  Data_Get_Struct(self, struct robj, ptr);
  robj = ptr->RObj;
  int len = GET_LENGTH(robj);

  ruby_arr = rb_ary_new();

  for (i=0; i<len; i++) {
    switch(TYPEOF(robj)) 
      {
      case NILSXP:
	ruby_robj = Qnil;
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
	//	str_p = *STRING_PTR(robj);
	//	Rf_PrintValue(str_p);
	ruby_robj = rb_str_new2(CHAR(robj));
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
    ruby_arr = rb_ary_push(ruby_arr, ruby_robj);
  }
  
  return ruby_arr;
}

static VALUE
to_str(VALUE self)
{
  SEXP robj;
  VALUE ruby_obj;
  
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

SEXP to_Robj(VALUE obj)
{
  SEXP robj;
  int type;

  if (obj == Qnil)
    return R_NilValue;

  type = TYPE(obj);
  switch (type)
    {
    case T_NIL:
      PROTECT(robj = R_NilValue);
    default:
      rb_raise(rb_eRobjException, "cannot convert from type %s", rb_class2name(obj));
      PROTECT(robj = NULL);
    }

  UNPROTECT(1);
  return robj;

}
