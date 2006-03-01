#include "rder.h"

int
to_RubyObj(SEXP rexp, VALUE ruby_ary)
{
  int i, *integers, type;
  long length;

  VALUE ruby_hash, ruby_obj;
  ROBJ *robj_p;
  SEXP str_p;

  length = GET_LENGTH(rexp);
  type = TYPEOF(rexp);
    printf("%i\n", length);
  ruby_ary = rb_ary_new();

  for (i=0; i<length; i++) {
    printf("TYPE: %i\n", type);
    if (type == NILSXP) {
      ruby_obj = Qnil;
    } else if (type == INTSXP) {
      int *integers = INTEGER(rexp);
      ruby_obj = INT2NUM(*integers);

    } else if (type == CLOSXP) {
      char *m = "masashi";
      ruby_obj = rb_str_new(0, 0);
      printf("'%s'\n", StringValuePtr(ruby_obj));
    } else {
      printf("EXCEPTION: %i\n", type);
      return 0; // failed
    }
    
    ruby_ary = rb_ary_push(ruby_ary, ruby_obj);

/*     switch(TYPEOF(rexp))  */
/*       { */
/*       case NILSXP: */
/* 	ruby_obj = Qnil; */
/* 	break; */
/*       case SYMSXP: */
/* 	break; */
/*       case LISTSXP: */
/* 	break; */
/*       case CLOSXP: */
/* 	break; */
/*       case ENVSXP: */
/* 	break; */
/*       case PROMSXP: */
/* 	break; */
/*       case LANGSXP: */
/* 	break; */
/*       case SPECIALSXP: */
/* 	break; */
/*       case BUILTINSXP: */
/* 	break; */
/*       case CHARSXP: */
/* 	break; */
/*       case LGLSXP: */
/* 	integers = INTEGER(robj); */
/* 	if (integers[i] == NA_INTEGER) { */

/* 	} else { */
	  
/* 	} */
/* 	break; */
/*       case INTSXP: */
/* 	integers = INTEGER(robj); */
/* 	integers[i] = INT2FIX(integers[i]); */
/* 	break; */
/*       case REALSXP: */
/* 	break; */
/*       case CPLXSXP: */
/* 	break; */
/*       case STRSXP: */
/* 	//	str_p = *STRING_PTR(robj); */
/* 	//	Rf_PrintValue(str_p); */
/* 	ruby_robj = rb_str_new2(CHAR(robj)); */
/* 	break; */
/*       case DOTSXP: */
/* 	break; */
/*       case ANYSXP: */
/* 	break; */
/*       case VECSXP: */
/* 	break; */
/*       case EXPRSXP: */
/* 	break; */
/*       case BCODESXP: */
/* 	break; */
/*       case EXTPTRSXP: */
/* 	break; */
/*       case WEAKREFSXP: */
/* 	break; */
/*       case RAWSXP: */
/* 	break; */
/*       case FUNSXP: */
/* 	break; */
/*       default: */
/* 	ruby_hash = Qtrue; */
/* 	break; */
/*       } */
  }
  
  return 1;
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

SEXP to_REXP(VALUE obj)
{
  SEXP robj;
  int ruby_type;

  ruby_type = rb_type(obj);

  switch (ruby_type)
    {
    case T_NIL:
      //      printf("switch T_NIL: in to_REXP\n");
      //      PROTECT(robj = R_NilValue);
      robj = R_NilValue;
      break;
    case T_FIXNUM:
printf("switch T_FIXNUM: in to_REXP\n");
      robj = NEW_INTEGER(1);
      INTEGER_DATA(robj)[0] = (int) FIX2INT(obj);
      break;
    case T_STRING:
      //      printf("switch T_STRING: in to_REXP\n");
      robj = Rf_mkString(RSTRING(obj)->ptr);
      break;
    default:
      // printf("switch default: in to_REXP\n");
      robj = NULL;
    }

  //  UNPROTECT(1);

  return robj;
}
