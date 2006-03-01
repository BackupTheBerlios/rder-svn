#include <Rdefines.h>
#include <Rinternals.h>
#include <ruby.h>


static VALUE R_initialize(VALUE);
static VALUE R_finalize(VALUE);
static VALUE R_evaluate(VALUE, VALUE);

static VALUE robj_alloc(VALUE);
static VALUE robj_initialize(VALUE, VALUE);

static SEXP R_References;

// Conversion types
static NO_CONV = -1;
static CONV_BASIC = 0;

static VALUE rb_mRdeR;
static VALUE rb_cR;
static VALUE rb_cRobj;

static VALUE rb_eRException;
static VALUE rb_eRobjException;


typedef struct robj {
  char *symbol;
  char *class;
  long length;
  int conversion;
} ROBJ;


void initR(void);

// for cR
SEXP get_fun_from_name(char *ident);
char *get_last_error_msg();

// for R2R
int to_RubyObj(SEXP, VALUE);
static VALUE to_RObj(VALUE, VALUE);

VALUE to_Robj(VALUE);

SEXP get_rexp(char*);
