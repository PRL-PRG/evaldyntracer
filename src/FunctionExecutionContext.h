#ifndef EVALDYNTRACER_FUNCTION_EXECUTION_CONTEXT_H
#define EVALDYNTRACER_FUNCTION_EXECUTION_CONTEXT_H

#include "ExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>

class FunctionExecutionContext : public ExecutionContext {
  public:
    explicit FunctionExecutionContext(const SEXP call, const SEXP op,
                                      const SEXP args, const SEXP rho)
        : ExecutionContext{}, call_{call}, op_{op}, args_{args}, rho_{rho},
          return_value_{nullptr} {}

    const SEXP get_call() const { return call_; }

    const SEXP get_function() const { return op_; }

    const SEXP get_arguments() const { return args_; }

    const SEXP get_environment() const { return rho_; }

    const SEXP get_argument(std::string name, bool extract = false) const {
        SEXP argument =
            lookup_environment(get_environment(), install(name.c_str()));

        if (extract)
            while (TYPEOF(argument) == PROMSXP)
                argument = get_promise_expression(argument);

        return argument;
    }

    const std::string get_name() const override {
        return std::string(serialize_sexp(CAR(call_)));
    }

    void set_return_value(SEXP return_value) { return_value_ = return_value; }

    const SEXP get_return_value() const { return return_value_; }

    virtual ~FunctionExecutionContext() {}

  private:
    const SEXP call_;
    const SEXP op_;
    const SEXP args_;
    const SEXP rho_;
    SEXP return_value_;
};

#endif /* EVALDYNTRACER_FUNCTION_EXECUTION_CONTEXT_H */
