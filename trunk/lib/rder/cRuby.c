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
robj_initialize(VALUE self, VALUE obj)
{
  struct robj *ptr;
  SEXP robj;

  Data_Get_Struct(self, struct robj, ptr);

/*   R_References = CONS(robj, R_References); */
/*   SET_SYMVALUE(install("R.References"), R_References); */

  ptr->RObj = robj;
  ptr->conversion = CONV_BASIC;

  return Qnil;
}

static VALUE
Robj_mode(VALUE self)
{
  struct robj *ptr;

  Data_Get_Struct(self, struct robj, ptr);
  return INT2NUM(ptr->conversion);
}

static VALUE
robj_length(VALUE self)
{
  struct robj *ptr;

  Data_Get_Struct(self, struct robj, ptr);
  int len = GET_LENGTH(ptr->RObj);
  if (!len) {
    return INT2FIX(0);
  } else {
    return INT2NUM(len);
  }
}



// Initialize RdeR module
void Init_rder(void) {


  rb_mRdeR = rb_define_module("RdeR");
  rb_cR = rb_define_class_under(rb_mRdeR, "R", rb_cObject);
  rb_cRobj = rb_define_class_under(rb_mRdeR, "Robj", rb_cObject);

  rb_define_method(rb_cR, "initialize", R_initialize, 0);
  rb_define_method(rb_cR, "close", R_finalize, 0);
  rb_define_method(rb_cR, "evalR", R_evaluate, 1);

  rb_eRException = rb_define_class("RException", rb_eException);

  rb_define_alloc_func(rb_cRobj, robj_alloc);
  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);
  rb_define_method(rb_cRobj, "mode", Robj_mode, 0);
  rb_define_method(rb_cRobj, "length", robj_length, 0);

  rb_define_method(rb_cRobj, "to_RubyObj", to_RubyObj, 0);
  rb_define_method(rb_cRobj, "to_RObj", to_RObj, 0);

  rb_eRobjException = rb_define_class("RobjException", rb_eException);
}
