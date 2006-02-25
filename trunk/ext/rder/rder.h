#include <Rdefines.h>
#include <Rinternals.h>
#include <ruby.h>


static VALUE R_initialize(VALUE);
static VALUE R_finalize(VALUE);
static VALUE R_evaluate(VALUE, VALUE);

static VALUE robj_alloc(VALUE);
static VALUE Robj_initialize(VALUE, VALUE);
static VALUE Robj_length(VALUE);

static SEXP R_References;

static CONV_BASIC = 0;

VALUE rb_mRdeR;
VALUE rb_cR;
VALUE rb_cRobj;

struct robj {
  SEXP RObj;
  char *symbol;
  int conversion;
};



void initR(void);

// for cR
SEXP get_fun_from_name(char *ident);
char *get_last_error_msg();

// for R2R
static VALUE to_RubyObj(VALUE);
static VALUE to_RObj(VALUE, VALUE);

static VALUE robj_call(VALUE, VALUE);

static VALUE rb_eRException;
static VALUE rb_eRobjException;
