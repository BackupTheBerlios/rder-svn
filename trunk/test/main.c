#include <Rdefines.h>
#include <ruby.h>
#include "rder.h"

int main(int argc, char *argv)
{
  SEXP res;
  VALUE ruby;

  initR();
  //  Rf_PrintValue(res = eval_cR("sum"));
  res = (SEXP) eval_Rfunc("sum");

  ruby = to_RubyObj(res);

  return 0;
}
