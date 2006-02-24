#include <ruby.h>

#include "rder.h"


static VALUE R_initialize(VALUE);
static VALUE R_finalize(VALUE);
static VALUE R_evaluate(VALUE, VALUE);


void Init_RdeR(void) {

  VALUE rb_mRdeR; // module RdeR
  VALUE rb_cR; // class R 
  VALUE rb_cRobj;

  rb_mRdeR = rb_define_module("RdeR");
  rb_cR = rb_define_class_under(rb_mRdeR, "R", rb_cObject);
  rb_cRobj = rb_define_class_under(rb_mRdeR, "Robj", rb_cObject);
  rb_include_module(rb_cRobj, rb_mEnumerable);

  rb_define_method(rb_cR, "initialize", R_initialize, 0);
  rb_define_method(rb_cR, "quitR", R_finalize, 0);
  rb_define_method(rb_cR, "evalR", R_evaluate, 1);

}

static VALUE R_initialize(VALUE self) {
  initR();
  return Qnil;
}

static VALUE R_finalize(VALUE self) {
  quitR();
  return Qnil;
}

static VALUE R_evaluate(VALUE self, VALUE f_name) {
  VALUE ret;
  ret = eval_Rfunc(STR2CSTR(f_name));

  return to_RubyObj(ret);
}

