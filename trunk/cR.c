#include "R.h"
#include "Rdefines.h"

#include "rder.h"

void initR() {
  char *argv[] = {"RdeR", "--quiet", "--vanilla"};
  int argc = sizeof(argv) / sizeof(argv[0]);
  Rf_initEmbeddedR(argc, argv);
}

void quitR() {
  //  end_Rmainloop();
  
  R_CleanUp();
}

SEXP do_eval_expr(SEXP e) {
  SEXP res;
  int errorOccured = 0;

  res = R_tryEval(e, NULL, &errorOccured);

  if (errorOccured) {
    fprintf(stderr, "Caught an error calling sqrt(). Try again with a different argument.\n");
    fflush(stderr);
  }

  return (res);
}

SEXP eval_cR(char *f_name) {
  SEXP e, val;

  SEXP e1;

  PROTECT(e = allocVector(LANGSXP, 1));
  SETCAR(e, Rf_install(f_name));

  val = do_eval_expr(e);
  //  printf("%i\n", length(val));
  printf("%s\n", GET_NAMES(val));

  UNPROTECT(1);

  return(val);
}
