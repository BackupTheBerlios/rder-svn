#include <Rdefines.h>
#include "ruby.h"

int main(int argc, char *argv)
{
  SEXP res;
  VALUE ruby;

  initR();
  //  Rf_PrintValue(res = eval_cR("sum"));
  res = (SEXP) eval_cR("sum");

  ruby = to_RubyObj(res);

  return(0);
}
