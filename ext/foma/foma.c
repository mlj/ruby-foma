#include "ruby.h"
#include <fomalib.h>

/*:enddoc:*/

#ifndef RSTRING_PTR /* Ruby 1.8 compatibility */
#define RSTRING_PTR(ptr) RSTRING(ptr)->ptr
#endif

VALUE mFOMA = Qnil;
VALUE mFSM = Qnil;

struct foma_fsm {
  struct fsm *net;
  struct apply_handle *ah;
};

static void foma_fsm_mark(struct foma_fsm *t)
{
}

static void foma_fsm_free(struct foma_fsm *t)
{
  if (t) {
    apply_clear(t->ah);
    fsm_destroy(t->net);
    free(t);
  }
}

static VALUE foma_fsm_alloc(VALUE klass)
{
  struct foma_fsm *t = NULL;

  return Data_Wrap_Struct(klass, foma_fsm_mark, foma_fsm_free, t);
}

static VALUE foma_fsm_init(VALUE obj, VALUE filename)
{
  FILE *file;
  struct foma_fsm *t;

  t = malloc(sizeof(struct foma_fsm));

  if (!t)
    rb_raise(rb_eRuntimeError, "error allocating memory");

  file = fopen(RSTRING_PTR(filename), "rb");

  if (!file) {
    free(t);
    rb_raise(rb_eRuntimeError, "unable to open file");
  }

  fclose(file);

  t->net = fsm_read_binary_file(RSTRING_PTR(filename));

  if (!t->net) {
    free(t);
    rb_raise(rb_eRuntimeError, "unable to read file");
  }

  t->ah = apply_init(t->net);

  DATA_PTR(obj) = t;
  return Qnil;
}

static VALUE foma_fsm_apply(VALUE self, VALUE string, char *(*applyer)())
{
  int enc = rb_enc_find_index("UTF-8");
  struct foma_fsm *t;
  char *result;

  Check_Type(string, T_STRING);

  Data_Get_Struct(self, struct foma_fsm, t);

  result = applyer(t->ah, RSTRING_PTR(string));

  if (result) {
    if (rb_block_given_p()) {
      VALUE string = rb_str_new2(result);
#ifdef HAVE_RUBY_ENCODING_H
      rb_enc_associate_index(string, enc);
#endif
      rb_yield(string);

      while (result = applyer(t->ah, NULL)) {
        VALUE string = rb_str_new2(result);
#ifdef HAVE_RUBY_ENCODING_H
        rb_enc_associate_index(string, enc);
#endif
        rb_yield(string);
      }
    }

    return Qtrue;
  } else {
    return Qfalse;
  }
}

static VALUE foma_fsm_apply_down(VALUE self, VALUE string)
{
  return foma_fsm_apply(self, string, &apply_down);
}

static VALUE foma_fsm_apply_up(VALUE self, VALUE string)
{
  return foma_fsm_apply(self, string, &apply_up);
}

void Init_foma(void)
{
  mFOMA = rb_define_module("FOMA");
  mFSM = rb_define_class_under(mFOMA, "FSM", rb_cObject);
  rb_define_alloc_func(mFSM, foma_fsm_alloc);
  rb_define_method(mFSM, "initialize", foma_fsm_init, 1);
  rb_define_method(mFSM, "apply_down", foma_fsm_apply_down, 1);
  rb_define_method(mFSM, "apply_up", foma_fsm_apply_up, 1);
}
