#include "AnalysisDriver.h"

AnalysisDriver::AnalysisDriver(const Configuration &configuration)
    : configuration_{configuration},
      execution_context_stack_{std::make_shared<ExecutionContextStack>()},
      eval_expression_analysis_{configuration, execution_context_stack_} {}

void AnalysisDriver::dyntrace_entry(const SEXP expression,
                                    const SEXP environment) {

    TopLevelExecutionContext context{environment};

    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->push(context);
}

void AnalysisDriver::dyntrace_exit(const SEXP expression,
                                   const SEXP environment, const SEXP result,
                                   const int error) {

    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->pop();
}

void AnalysisDriver::closure_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    FunctionExecutionContext context{call, op, args, rho};

    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->push(context);

    if (configuration_.is_eval_expression_analysis_enabled())
        eval_expression_analysis_.closure_entry(context);
}

void AnalysisDriver::closure_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {

    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->pop();
}

void AnalysisDriver::builtin_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    FunctionExecutionContext context{call, op, args, rho};
    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->push(context);
}

void AnalysisDriver::builtin_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {

    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->pop();
}

void AnalysisDriver::special_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    FunctionExecutionContext context{call, op, args, rho};
    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->push(context);
}

void AnalysisDriver::special_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {
    if (configuration_.is_execution_context_stack_needed())
        execution_context_stack_->pop();
}
