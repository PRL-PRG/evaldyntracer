#ifndef __ANALYSIS_DRIVER_H__
#define __ANALYSIS_DRIVER_H__

#include "Configuration.h"
#include "EvalExpressionAnalysis.h"
#include "ExecutionContextStack.h"
#include <memory>

class AnalysisDriver {

  public:
    explicit AnalysisDriver(const Configuration &configuration);

    void dyntrace_entry(const SEXP expression, const SEXP environment);

    void dyntrace_exit(const SEXP expression, const SEXP environment,
                       const SEXP result, const int error);

    void closure_entry(const SEXP call, const SEXP op, const SEXP args,
                       const SEXP rho);

    void closure_exit(const SEXP call, const SEXP op, const SEXP args,
                      const SEXP rho, const SEXP retval);

    void builtin_entry(const SEXP call, const SEXP op, const SEXP args,
                       const SEXP rho);

    void builtin_exit(const SEXP call, const SEXP op, const SEXP args,
                      const SEXP rho, const SEXP retval);

    void special_entry(const SEXP call, const SEXP op, const SEXP args,
                       const SEXP rho);

    void special_exit(const SEXP call, const SEXP op, const SEXP args,
                      const SEXP rho, const SEXP retval);

    void context_entry(const RCNTXT *rcontext);

    void context_exit(const RCNTXT *rcontext);

    void context_jump(const RCNTXT *context, const SEXP return_value,
                      int restart);

  private:
    const Configuration configuration_;
    std::shared_ptr<ExecutionContextStack> execution_context_stack_;
    EvalExpressionAnalysis eval_expression_analysis_;
};

#endif /* __ANALYSIS_DRIVER_H__ */
