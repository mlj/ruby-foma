#include "ruby.h"
#include <fomalib.h>

/*:enddoc:*/

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
    fsm_destroy(t->net);
    apply_clear(t->ah);
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

  if (!t) {
    rb_raise(rb_eRuntimeError, "Error allocating memory");
  }

  file = fopen(RSTRING(filename)->ptr, "rb");

  if (!file) {
    free(t);
    rb_raise(rb_eRuntimeError, "Unable to open file %s", RSTRING(filename)->ptr);
  }

  fclose(file);

  t->net = fsm_read_binary_file(RSTRING(filename)->ptr);

  if (!t->net) {
    free(t);
    rb_raise(rb_eRuntimeError, "Unable to read file %s", RSTRING(filename)->ptr);
  }

  t->ah = apply_init(t->net);

  DATA_PTR(obj) = t;
  return Qnil;
}

static VALUE foma_fsm_apply(VALUE self, VALUE string, char *(*applyer)())
{
  struct foma_fsm *t;
  char *result;

  Check_Type(string, T_STRING);

  Data_Get_Struct(self, struct foma_fsm, t);

  result = applyer(t->ah, RSTRING(string)->ptr);

  if (result) {
    if (rb_block_given_p()) {
      rb_yield(rb_str_new2(result));

      while (result = applyer(t->ah, NULL))
        rb_yield(rb_str_new2(result));
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
