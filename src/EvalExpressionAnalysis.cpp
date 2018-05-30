#include "EvalExpressionAnalysis.h"

EvalExpressionAnalysis::EvalExpressionAnalysis(
    const Configuration &configuration)
    : configuration_{configuration},
      expression_table_writer_{configuration.get_raw_analysis_dirpath() + "/" +
                                   "eval-expressions.csv",
                               {"function_name", "expression"}} {}

void EvalExpressionAnalysis::closure_entry(const SEXP call, const SEXP op,
                                           const SEXP args, const SEXP rho) {
    for (auto &key_value : configuration_.get_evals()) {
        const std::string eval_name = key_value.first;
        const SEXP eval_function = key_value.second;
        if (op == eval_function) {
            SEXP value = lookup_environment(rho, install("expr"));
            if (value != R_UnboundValue) {
                if (TYPEOF(value) == PROMSXP)
                    value = get_promise_expression(value);
                expression_table_writer_.write_row(eval_name,
                                                   serialize_sexp(value));
            } else {
                dyntrace_log_error(
                    "'expr' not bound to a value in a call to '%s'",
                    eval_name.c_str());
            }
            break;
        }
    }
}
