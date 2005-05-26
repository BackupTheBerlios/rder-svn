#include <Rdefines.h>

int main(int argc, char** argv)
{
  SEXP expr, res, lsstr;
  int errorOccured;

  char *localArgs[] = {"R", "--quiet", "--vanilla"};
  Rf_initEmbeddedR(sizeof(localArgs) / sizeof(localArgs[0]), localArgs);
  
  PROTECT(expr = allocVector(REALSXP, 1));
  REAL(expr)[0] = 123.45;
  defineVar(install("mimamu"), expr, R_GlobalEnv);
  Rf_PrintValue(expr);

  PROTECT(lsstr = allocVector(LANGSXP, 1));
  SETCAR(lsstr, install("ls"));
  res = R_tryEval(lsstr, R_GlobalEnv, &errorOccured);
  Rf_PrintValue(res);

  UNPROTECT(2);

  return (0);
}
