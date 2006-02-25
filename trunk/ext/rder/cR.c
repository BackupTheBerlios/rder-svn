#include "rder.h"

char *ident;

void initR() {
  char *argv[] = {"RdeR", "--quiet", "--vanilla"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  Rf_initEmbeddedR(argc, argv);
}

void quitR() {
  //  end_Rmainloop();
  
  R_CleanUp();
}

SEXP eval_Rexpr(SEXP expr) {
  SEXP res;
  int errorOccured = 0;

  res = R_tryEval(expr, R_GlobalEnv, &errorOccured);

  if (errorOccured) {
    rb_raise(rb_eRException, "%s", get_last_error_msg());
  }

  return (res);
}

SEXP eval_Rfunc(char *fname) {
  SEXP expr, func, res;

  func = get_fun_from_name(fname);

  if (!func)
    return NULL;

  PROTECT(func);
  PROTECT(expr = allocVector(LANGSXP, 1));
  SETCAR(expr, func);

  PROTECT(res = eval_Rexpr(expr));
  UNPROTECT(3);

  return res;
}

SEXP eval_R_get(char *fname)
{
  SEXP expr, res;
  int error;

printf("fname: %s\n", fname);

  PROTECT(expr = allocVector(LANGSXP, 2));
  SETCAR(expr, install("get"));
  SETCAR(CDR(expr), Rf_mkString(fname));
  res = R_tryEval(expr, R_GlobalEnv, &error);

  if (error) {
    rb_raise(rb_eRException, "R execution exception. %s", expr);
  }

  UNPROTECT(1);
  return res;
}

SEXP get_fun_from_name(char *ident) {

  SEXP obj;

  if (!*ident) {
    return NULL;
  }

  obj = Rf_findVar(Rf_install(ident), R_GlobalEnv);

/*   if (obj != R_UnboundValue) { */
/*     obj = Rf_findFun(Rf_install(ident), R_GlobalEnv); */
/*   } */

  if (obj == R_UnboundValue)
    rb_raise(rb_eRobjException, "There is no symbol \"%s\".", ident);

  return obj;
}

/* Obtain the text of the last R error message */
char *get_last_error_msg() {
  SEXP msg;
  msg = (SEXP) eval_Rfunc("geterrmessage");

  return (char*) CHARACTER_VALUE(msg);
}


int makeargs(int nargs, VALUE args, SEXP *e)
{
  SEXP r;
  int i;

  for (i=0; i<nargs; i++) {
    r = to_Robj(rb_ary_entry(args, i));
    if (!r)
      return 0;
    SETCAR(*e, r);
    *e = CDR(*e);
  }
  return 1;
}

static VALUE 
robj_call(VALUE self, VALUE args)
{
  SEXP exp, e, res;
  int nargs;
  struct robj *ptr;
  VALUE ruby_obj;

  if (args)
    nargs = NUM2INT(rb_ary_length(args));

  PROTECT(exp = Rf_allocVector(LANGSXP, nargs+1));
  e = exp;
Rf_PrintValue(exp);
  Data_Get_Struct(self, struct robj, ptr);
  SETCAR(e, ptr->RObj);
  e = CDR(e);
  makeargs(nargs, args, &e);
  PROTECT(res = eval_Rexpr(exp));
  
  ruby_obj = Data_Make_Struct(rb_cRobj, struct robj, 0, -1, ptr);
  ptr->RObj = res;

  return ruby_obj;
}
