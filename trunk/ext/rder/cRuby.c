#include "rder.h"




static VALUE R_initialize(VALUE self) {
  initR();
  return Qnil;
}

static VALUE R_finalize(VALUE self) {
  quitR();
  return Qnil;
}


static VALUE R_evaluate(VALUE self, VALUE f_name) {
  VALUE ret, robj;
  SEXP r_ret;
  //  r_ret = (SEXP) eval_Rfunc(STR2CSTR(f_name));
  r_ret = (SEXP) eval_R_get(STR2CSTR(f_name));
  
  if (!r_ret) {
    rb_raise(rb_eException, "%s: R evaluation error.\n", r_ret);
  }

  struct robj *ptr;

  robj = Data_Make_Struct(rb_cRobj, struct robj, 0, -1, ptr);
  ptr->RObj = r_ret;

  ptr->conversion = 3;

  return robj;
}



// Robj class

static VALUE
robj_alloc(VALUE klass)
{
  struct robj *ptr = ALLOC(struct robj);

  return Data_Wrap_Struct(klass, 0, -1, ptr);
}

static VALUE
robj_initialize(VALUE self, VALUE r_fname)
{
  struct robj *ptr;

  Data_Get_Struct(self, struct robj*, ptr);

  ptr->RObj = R_get_function(RSTRING(r_fname)->ptr);
  ptr->conversion = CONV_BASIC;


  SEXP rexp = ptr->RObj;
  //  Rf_PrintValue(rexp);

  return Qnil;
}

static VALUE
robj_length(VALUE self)
{
  VALUE rb_int;
  int len;
  struct robj *ptr;

  Data_Get_Struct(self, struct robj, ptr);
  len = GET_LENGTH(ptr->RObj);

  if (!len) {
    rb_int = INT2FIX(0);
  } else {
    rb_int = INT2NUM(len);
  }
  
  return rb_int;
}

static VALUE
robj_eval(VALUE self)
{
  SEXP rexp, tmp, res;
  struct robj *ptr;

  Data_Get_Struct(self, struct robj*, ptr);
  rexp = ptr->RObj;

  printf("REXP: ");
  Rf_PrintValue(rexp);



  PROTECT(rexp);
  PROTECT(tmp = allocVector(LANGSXP, 1));
  SETCAR(tmp, rexp);
  PROTECT(res = eval_Rexpr(tmp));
  UNPROTECT(3);

  printf("---- EALUATE! ---- \n");  

  printf("Result: ");
  Rf_PrintValue(res);

  VALUE obj;
  obj = Data_Make_Struct(rb_cRobj, struct robj, 0, -1, ptr);
  ptr->RObj = (SEXP) res;

  return obj;
  //  return Qnil;
}


// static VALUE robj_get_args(VALUE self) {}

static VALUE 
robj_set_args(VALUE self, VALUE args)
{
  long nargs;
  struct robj *e;

  args = rb_Array(args); // corece to Array class with to_a
  nargs = LONG2NUM(RARRAY(args)->len);

  Data_Get_Struct(self, struct robj, e);

  makeargs(nargs, args, &e);
  return Qnil;
}

// Initialize RdeR module
void Init_rder(void) {
  
  // module RdeR
  rb_mRdeR = rb_define_module("RdeR");
  rb_cR = rb_define_class_under(rb_mRdeR, "R", rb_cObject);
  rb_cRobj = rb_define_class_under(rb_mRdeR, "Robj", rb_cObject);

  // class R
  rb_define_method(rb_cR, "initialize", R_initialize, 0);
  rb_define_method(rb_cR, "close", R_finalize, 0);

  rb_eRException = rb_define_class("RException", rb_eException);

  // class Robj
  rb_define_alloc_func(rb_cRobj, robj_alloc);
  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);
  rb_define_method(rb_cRobj, "length", robj_length, 0);
  rb_define_method(rb_cRobj, "args=", robj_set_args, 1);
  rb_define_method(rb_cRobj, "eval", robj_eval, 0);

  rb_eRobjException = rb_define_class("RobjException", rb_eException);
}
