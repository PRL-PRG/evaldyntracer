#ifndef __PROBES_H__
#define __PROBES_H__

#define R_INLINES_H_
#include "State.h"
#include "utilities.h"
#include <Rdyntrace.h>

inline const Configuration &configuration(dyntracer_t *dyntracer) {
    return static_cast<State *>(dyntracer->state)->get_configuration();
}

inline AnalysisDriver &analysis_driver(dyntracer_t *dyntracer) {
    return static_cast<State *>(dyntracer->state)->get_analysis_driver();
}

void probe_dyntrace_entry(dyntracer_t *dyntracer, const SEXP expression,
                          const SEXP environment);

void probe_dyntrace_exit(dyntracer_t *dyntracer, const SEXP expression,
                         const SEXP environment, const SEXP result,
                         const int error);

void probe_closure_entry(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                         const SEXP args, const SEXP rho);

void probe_closure_exit(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                        const SEXP args, const SEXP rho, const SEXP retval);

void probe_builtin_entry(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                         const SEXP args, const SEXP rho);

void probe_builtin_exit(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                        const SEXP args, const SEXP rho, const SEXP retval);

void probe_special_entry(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                         const SEXP args, const SEXP rho);

void probe_special_exit(dyntracer_t *dyntracer, const SEXP call, const SEXP op,
                        const SEXP args, const SEXP rho, const SEXP retval);

void probe_promise_force_entry(dyntracer_t *dyntracer, const SEXP promise);

void probe_promise_force_exit(dyntracer_t *dyntracer, const SEXP promise);

void probe_promise_value_lookup(dyntracer_t *dyntracer, const SEXP promise);

void probe_promise_value_assign(dyntracer_t *dyntracer, const SEXP promise,
                                const SEXP value);

void probe_promise_expression_lookup(dyntracer_t *dyntracer,
                                     const SEXP promise);

void probe_promise_expression_assign(dyntracer_t *dyntracer, const SEXP promise,
                                     const SEXP expression);

void probe_promise_environment_lookup(dyntracer_t *dyntracer,
                                      const SEXP promise);

void probe_promise_environment_assign(dyntracer_t *dyntracer,
                                      const SEXP promise,
                                      const SEXP environment);

void probe_eval_entry(dyntracer_t *dyntracer, const SEXP expression,
                      const SEXP rho);

void probe_eval_exit(dyntracer_t *dyntracer, const SEXP expression,
                     const SEXP rho, const SEXP return_value);

void probe_gc_entry(dyntracer_t *dyntracer, size_t size_needed);

void probe_gc_exit(dyntracer_t *dyntracer, int gc_count);

void probe_gc_unmark(dyntracer_t *dyntracer, const SEXP object);

void probe_gc_allocate(dyntracer_t *dyntracer, const SEXP object);

void probe_context_entry(dyntracer_t *dyntracer, const RCNTXT *context);

void probe_context_exit(dyntracer_t *dyntracer, const RCNTXT *context);

void probe_context_jump(dyntracer_t *dyntracer, const RCNTXT *context,
                        const SEXP return_value, int restart);

void probe_S3_generic_entry(dyntracer_t *dyntracer, const char *generic,
                            const SEXP object);

void probe_S3_generic_exit(dyntracer_t *dyntracer, const char *generic,
                           const SEXP object, const SEXP retval);

void probe_S3_dispatch_entry(dyntracer_t *dyntracer, const char *generic,
                             const char *cls, const SEXP method,
                             const SEXP object);

void probe_S3_dispatch_exit(dyntracer_t *dyntracer, const char *generic,
                            const char *cls, const SEXP method,
                            const SEXP object, const SEXP retval);

void probe_environment_variable_define(dyntracer_t *dyntracer,
                                       const SEXP symbol, const SEXP value,
                                       const SEXP rho);

void probe_environment_variable_assign(dyntracer_t *dyntracer,
                                       const SEXP symbol, const SEXP value,
                                       const SEXP rho);

void probe_environment_variable_remove(dyntracer_t *dyntracer,
                                       const SEXP symbol, const SEXP rho);

void probe_environment_variable_lookup(dyntracer_t *dyntracer,
                                       const SEXP symbol, const SEXP value,
                                       const SEXP rho);

void probe_environment_variable_exists(dyntracer_t *dyntracer,
                                       const SEXP symbol, const SEXP rho);

#endif /* __PROBES_H__ */
