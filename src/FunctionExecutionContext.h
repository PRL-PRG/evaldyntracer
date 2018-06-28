#ifndef __FUNCTION_EXECUTION_CONTEXT_H__
#define __FUNCTION_EXECUTION_CONTEXT_H__

#include "sexptype.h"
#include <Rinternals.h>

class FunctionExecutionContext {
  public:
    explicit FunctionExecutionContext(const SEXP call, const SEXP op,
                                      const SEXP args, const SEXP rho)
        : call_{call}, op_{op}, args_{args}, rho_{rho} {}

    const SEXP get_call() const { return call_; }

    const SEXP get_function() const { return op_; }

    const sexptype_t get_type() const { return TYPEOF(op_); }

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

    const std::string get_name() const {
        return std::string(serialize_sexp(CAR(call_)));
    }

  private:
    const SEXP call_;
    const SEXP op_;
    const SEXP args_;
    const SEXP rho_;
};

#endif /* __FUNCTION_EXECUTION_CONTEXT_H__ */
