#include <ruby.h>

#include "rder.h"

static VALUE RdeR_initialize(VALUE self) {
  initR();
  return Qnil;
}

static VALUE RdeR_finalize(VALUE self) {
  quitR();
  return Qnil;
}

static VALUE eval_R(VALUE self, VALUE f_name) {
  VALUE ret;

  ret = eval_cR(STR2CSTR(f_name));
  return to_RubyObj(ret);
}

void Init_RdeR(void) {
  VALUE rb_cRdeR;

  rb_cRdeR = rb_define_class("RdeR", rb_cObject);
  rb_define_method(rb_cRdeR, "initialize", RdeR_initialize, 0);
  rb_define_method(rb_cRdeR, "quitR", RdeR_finalize, 0);
  rb_define_method(rb_cRdeR, "eval_R", eval_R, 1);
}
