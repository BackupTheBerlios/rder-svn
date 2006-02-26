#include <Rdefines.h>

char *get_last_error_msg();

int main(int argc, char** argv)
{
  SEXP expr, res, lsstr;
  int errorOccured;

  char *localArgs[] = {"R", "--quiet", "--vanilla"};
  Rf_initEmbeddedR(sizeof(localArgs) / sizeof(localArgs[0]), localArgs);
  
  PROTECT(expr = allocVector(REALSXP, 1));
  REAL(expr)[0] = 123.45;
  defineVar(Rf_install("foo"), expr, R_GlobalEnv);
  Rf_PrintValue(expr);

  PROTECT(lsstr = allocVector(LANGSXP, 1));
  //  SETCAR(lsstr, Rf_install("version"));
  SETCAR(lsstr, Rf_install("c"));
  res = R_tryEval(lsstr, R_GlobalEnv, &errorOccured);

  if (errorOccured) {
    printf("%s\n", get_last_error_msg());
    //fflush(stderr);
  } else {
    Rf_PrintValue(res);
  }

  UNPROTECT(2);

  return (0);
}

/* Obtain the text of the last R error message */
char *get_last_error_msg() {
  SEXP msg, res;

  PROTECT(msg = allocVector(LANGSXP, 1));
  SETCAR(msg, install("geterrmessage"));
  res = R_tryEval(msg, R_GlobalEnv, NULL);

  //  msg = do_eval_fun("geterrmessage");
  return CHARACTER_VALUE(msg);
}
