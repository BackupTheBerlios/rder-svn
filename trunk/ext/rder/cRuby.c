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

  //struct robj *ptr;

  //  robj = Data_Make_Struct(rb_cRobj, struct robj, 0, -1, ptr);
  //ptr->RObj = r_ret;

  //ptr->conversion = 3;


  return robj;
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

  return Qnil;
}

// static VALUE robj_get_args(VALUE self) {}

static VALUE 
robj_set_args(VALUE self, VALUE args)
{

  args = rb_Array(args); // corece to Array class with to_a

  return Qnil;
}

// Initialize RdeR module
void Init_rder(void) {
  
  // module RdeR
  rb_mRdeR = rb_define_module("RdeR");

  // class R
  rb_cR = rb_define_class_under(rb_mRdeR, "R", rb_cObject);

  rb_define_method(rb_cR, "initialize", R_initialize, 0);
  rb_define_method(rb_cR, "close", R_finalize, 0);

  rb_eRException = rb_define_class("RException", rb_eException);

  // class Robj
  rb_cRobj = rb_define_class_under(rb_mRdeR, "Robj", rb_cObject);

  rb_define_alloc_func(rb_cRobj, robj_alloc);

  //  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);
  rb_define_private_method(rb_cRobj, "initialize", robj_initialize, 1);

  rb_define_method(rb_cRobj, "args=", robj_set_args, 1);

  rb_eRobjException = rb_define_class("RobjException", rb_eException);
}
