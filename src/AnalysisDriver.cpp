#include "AnalysisDriver.h"

AnalysisDriver::AnalysisDriver(const Configuration &configuration)
    : configuration_{configuration},
      execution_context_stack_{std::make_shared<ExecutionContextStack>()},
      eval_expression_analysis_{configuration, execution_context_stack_} {}

void AnalysisDriver::dyntrace_entry(const SEXP expression,
                                    const SEXP environment) {

    TopLevelExecutionContext context{environment};
    execution_context_stack_->push(context);
}

void AnalysisDriver::dyntrace_exit(const SEXP expression,
                                   const SEXP environment, const SEXP result,
                                   const int error) {

    TopLevelExecutionContext context{
        std::get<TopLevelExecutionContext>(execution_context_stack_->pop())};
    context.set_result(result);
    context.set_error(error);
}

void AnalysisDriver::closure_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    ClosureExecutionContext context{call, op, args, rho};

    if (configuration_.is_eval_expression_analysis_enabled()) {
        eval_expression_analysis_.closure_entry(context);
    }

    execution_context_stack_->push(context);
}

void AnalysisDriver::closure_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {

    ClosureExecutionContext context{
        std::get<ClosureExecutionContext>(execution_context_stack_->pop())};
    context.set_return_value(retval);

    if (configuration_.is_eval_expression_analysis_enabled()) {
        eval_expression_analysis_.closure_exit(context);
    }
}

void AnalysisDriver::builtin_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    BuiltinExecutionContext context{call, op, args, rho};
    execution_context_stack_->push(context);

    if (configuration_.is_eval_expression_analysis_enabled()) {
        eval_expression_analysis_.builtin_entry(context);
    }
}

void AnalysisDriver::builtin_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {

    BuiltinExecutionContext context{
        std::get<BuiltinExecutionContext>(execution_context_stack_->pop())};
    context.set_return_value(retval);
}

void AnalysisDriver::special_entry(const SEXP call, const SEXP op,
                                   const SEXP args, const SEXP rho) {

    SpecialExecutionContext context{call, op, args, rho};
    execution_context_stack_->push(context);

    if (configuration_.is_eval_expression_analysis_enabled()) {
        eval_expression_analysis_.special_entry(context);
    }
}

void AnalysisDriver::special_exit(const SEXP call, const SEXP op,
                                  const SEXP args, const SEXP rho,
                                  const SEXP retval) {
    SpecialExecutionContext context{
        std::get<SpecialExecutionContext>(execution_context_stack_->pop())};
    context.set_return_value(retval);
}

void AnalysisDriver::context_entry(const RCNTXT *rcontext) {
    RExecutionContext context{rcontext};
    execution_context_stack_->push(context);
}

void AnalysisDriver::context_exit(const RCNTXT *rcontext) {
    RExecutionContext context{
        std::get<RExecutionContext>(execution_context_stack_->pop())};
}

void AnalysisDriver::context_jump(const RCNTXT *context,
                                  const SEXP return_value, int restart) {
    execution_contexts_t unwound_contexts{
        execution_context_stack_->unwind(RExecutionContext{context})};

    if (configuration_.is_eval_expression_analysis_enabled()) {
        eval_expression_analysis_.context_jump(unwound_contexts);
    }
}
