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
    rb_raise(rb_eException, get_last_error_msg());
    // Raise Ruby exception
    return NULL;
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


SEXP get_fun_from_name(char *ident) {

  SEXP obj;

  if (!*ident) {
    rb_raise(rb_eException, 'attempt to use zero-length vaiable name');
    return NULL;
  }

  obj = Rf_findVar(Rf_install(ident), R_GlobalEnv);

  if (obj != R_UnboundValue) {
    obj = Rf_findFun(Rf_install(ident), R_GlobalEnv);
  }

  return obj;
}

/* Obtain the text of the last R error message */
char *get_last_error_msg() {
  SEXP msg;
  msg = do_eval_fun("geterrmessage");

  return CHARACTER_VALUE(msg);
}

