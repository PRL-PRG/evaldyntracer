#include "tracer.h"
#include "State.h"
#include "probes.h"

SEXP create_dyntracer(SEXP evals, SEXP raw_analysis_dirpath,
                      SEXP analysis_flags, SEXP verbose) {

    /* calloc initializes the memory to zero. This ensures that probes not
       attached will be NULL. Replacing calloc with malloc will cause
       segfaults. */
    dyntracer_t *dyntracer = (dyntracer_t *)calloc(1, sizeof(dyntracer_t));
    dyntracer->state = new State(
        Configuration(evals, raw_analysis_dirpath, analysis_flags, verbose));

    dyntracer->probe_dyntrace_entry = probe_dyntrace_entry;
    dyntracer->probe_dyntrace_exit = probe_dyntrace_exit;

    dyntracer->probe_closure_entry = probe_closure_entry;
    dyntracer->probe_closure_exit = probe_closure_exit;
    dyntracer->probe_builtin_entry = probe_builtin_entry;
    dyntracer->probe_builtin_exit = probe_builtin_exit;
    dyntracer->probe_special_entry = probe_special_entry;
    dyntracer->probe_special_exit = probe_special_exit;

    dyntracer->probe_gc_entry = probe_gc_entry;
    dyntracer->probe_gc_exit = probe_gc_exit;
    dyntracer->probe_gc_allocate = probe_gc_allocate;
    dyntracer->probe_gc_unmark = probe_gc_unmark;

    dyntracer->probe_promise_force_entry = probe_promise_force_entry;
    dyntracer->probe_promise_force_exit = probe_promise_force_exit;
    dyntracer->probe_promise_value_lookup = probe_promise_value_lookup;
    dyntracer->probe_promise_value_assign = probe_promise_value_assign;
    dyntracer->probe_promise_expression_lookup =
        probe_promise_expression_lookup;
    dyntracer->probe_promise_expression_assign =
        probe_promise_expression_assign;
    dyntracer->probe_promise_environment_lookup =
        probe_promise_environment_lookup;
    dyntracer->probe_promise_environment_assign =
        probe_promise_environment_assign;

    dyntracer->probe_context_entry = probe_context_entry;
    dyntracer->probe_context_jump = probe_context_jump;
    dyntracer->probe_context_exit = probe_context_exit;

    dyntracer->probe_environment_variable_define =
        probe_environment_variable_define;
    dyntracer->probe_environment_variable_assign =
        probe_environment_variable_assign;
    dyntracer->probe_environment_variable_remove =
        probe_environment_variable_remove;
    dyntracer->probe_environment_variable_lookup =
        probe_environment_variable_lookup;
    dyntracer->probe_environment_variable_exists =
        probe_environment_variable_exists;

    return dyntracer_to_sexp(dyntracer, "evaldyntracer");
}

static void destroy_evaldyntracer(dyntracer_t *dyntracer) {
    /* free dyntracer iff it has not already been freed.
       this check ensures that multiple calls to destroy_dyntracer on the same
       object do not crash the process. */
    if (dyntracer) {
        State *state = static_cast<State *>(dyntracer->state);
        delete state;
        free(dyntracer);
    }
}

SEXP destroy_dyntracer(SEXP dyntracer) {
    return dyntracer_destroy_sexp(dyntracer, destroy_evaldyntracer);
}
