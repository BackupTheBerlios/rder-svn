#include <Rinternals.h>

void initR(void);

// for cR
SEXP get_fun_from_name(char *ident);
char *get_last_error_msg();

// for R2R
VALUE to_RubyObj(SEXP robj);
SEXP to_RObj(VALUE ruby_obj);

