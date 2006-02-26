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
  int error = 0;
  // Rf_PrintValue(expr);
  res = R_tryEval(expr, R_GlobalEnv, &error);

  if (error) {
    //    rb_raise(rb_eRException, "%s", get_last_error_msg());
    printf("error occured in eval_Rexpr [i]");
  }

  return res;
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


SEXP R_get_function(char *fname)
{
  SEXP expr, res;
  int error;

  printf("fname: %s\n", fname);

  SEXP robj = Rf_findVar(Rf_install(fname), R_GlobalEnv);
  if (robj == R_UnboundValue)
    return R_NilValue;
  robj = Rf_findFun(Rf_install(fname), R_GlobalEnv);

  printf("VALUE: \n");
  Rf_PrintValue(robj);


  PROTECT(expr = allocVector(LANGSXP, 2));
  SETCAR(expr, install("get"));
  SETCAR(CDR(expr), Rf_mkString(fname));
  res = R_tryEval(expr, R_GlobalEnv, &error);
  //  Rf_PrintValue(res);
  if (error) {
    //    rb_raise(rb_eRException, "R execution exception. %s", expr);
    UNPROTECT(1);
    return NULL;
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
    r = to_REXP(rb_ary_entry(args, i));
    if (!r)
      return 0;
    SETCAR(*e, r);
    *e = CDR(*e);
  }
  return 1;
}

