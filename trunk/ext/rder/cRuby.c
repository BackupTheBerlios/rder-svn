#include "rder.h"

static VALUE R_initialize(VALUE self) {
  initR();
  return Qnil;
}

static VALUE R_finalize(VALUE self) {
  quitR();
  return Qnil;
}

static VALUE r_evaluate(VALUE self, VALUE obj) {
  VALUE res, robj;
  SEXP r_res;
  int conv_success;
  char *symbol, *klass_name;

  symbol = StringValuePtr(obj);
  printf("%s\n", symbol);

  r_res = Rf_findVar(Rf_install(symbol), R_GlobalEnv);
  if (r_res == R_UnboundValue) {
    rb_raise(rb_eRException, "There is no symbol: '%s.'", symbol);
  }
  
  r_res = (SEXP) get_rexp(symbol);

  if (!r_res) {
    rb_raise(rb_eRException, "R evaluation error.\n");
  }

  //  robj = rb_class_new(rb_cObject);
  robj = rb_ary_new();

  conv_success = to_RubyObj(r_res, robj);

  if (!conv_success) {
    rb_raise(rb_eRException, "The conversion for this type is not implemented yet.");
    return Qnil; // dummy
  }

  return robj;
}

SEXP
get_rexp(char *symbol)
{
  SEXP res, rexp;
  int error;

  PROTECT(rexp = allocVector(LANGSXP, 2));
  SETCAR(rexp, Rf_install("get"));
  SETCAR(CDR(rexp), Rf_mkString(symbol));
  res = R_tryEval(rexp, R_GlobalEnv, &error);
  
  if (error) {
    UNPROTECT(1);
    return NULL;
  }
  
  UNPROTECT(1);
  return res;

}



// Robj class

static VALUE
robj_alloc(VALUE klass)
{
  ROBJ *robj = ALLOC(ROBJ);

  return Data_Wrap_Struct(klass, 0, -1, robj);
}

static VALUE
robj_initialize(VALUE self, VALUE obj)
{
  ROBJ *robj;

  Data_Get_Struct(self, ROBJ, robj);
  // NOT YET some initializations
  robj->class = "object";

  return Qnil;
}

// static VALUE robj_get_args(VALUE self) {}

static VALUE 
robj_set_args(VALUE self, VALUE args)
{

  args = rb_Array(args); // corece to Array class with to_a

  return Qnil;
}

static VALUE
robj_r_class_get(VALUE self)
{
  ROBJ *robj;
  char *r_class;

  Data_Get_Struct(self, ROBJ, robj);
  r_class = robj->class;
  
  return rb_str_new(r_class, strlen(r_class));
}

static VALUE 
robj_r_class_set(VALUE self, VALUE rc_name)
{
  ROBJ *robj;
  char *r_class;

  r_class = StringValuePtr(rc_name);

  Data_Get_Struct(self, ROBJ, robj);
  robj->class = r_class;

  return rc_name;
}

// Initialize RdeR module
void 
Init_rder(void) {
  
  // module RdeR
  rb_mRdeR = rb_define_module("RdeR");

  // class R
  rb_cR = rb_define_class_under(rb_mRdeR, "R", rb_cObject);

  rb_define_method(rb_cR, "initialize", R_initialize, 0);
  rb_define_method(rb_cR, "close", R_finalize, 0);
  rb_define_method(rb_cR, "reval", r_evaluate, 1);

  rb_eRException = rb_define_class("RException", rb_eException);

  // class Robj
  rb_cRobj = rb_define_class_under(rb_mRdeR, "Robj", rb_cObject);

  rb_define_alloc_func(rb_cRobj, robj_alloc);

  //  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);
  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);
  rb_define_method(rb_cRobj, "r_class", robj_r_class_get, 0);
  rb_define_method(rb_cRobj, "r_class=", robj_r_class_set, 1);
  rb_define_method(rb_cRobj, "args=", robj_set_args, 1);

  rb_eRobjException = rb_define_class("RobjException", rb_eException);
}
