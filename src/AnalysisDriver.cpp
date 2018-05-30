#include "AnalysisDriver.h"

AnalysisDriver::AnalysisDriver(const Configuration &configuration)
    : configuration_{configuration}, eval_expression_analysis_{configuration} {}

void AnalysisDriver::closure_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {
    if (configuration_.is_eval_expression_analysis_enabled())
        eval_expression_analysis_.closure_entry(call, op, args, rho);
}
