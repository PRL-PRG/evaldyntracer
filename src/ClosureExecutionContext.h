#ifndef EVALDYNTRACER_CLOSURE_EXECUTION_CONTEXT_H
#define EVALDYNTRACER_CLOSURE_EXECUTION_CONTEXT_H

#include "FunctionExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>

class ClosureExecutionContext : public FunctionExecutionContext {
  public:
    explicit ClosureExecutionContext(const SEXP call, const SEXP op,
                                     const SEXP args, const SEXP rho)
        : FunctionExecutionContext{call, op, args, rho} {}

    bool operator==(const ClosureExecutionContext &rhs) const {
        return (get_call() == rhs.get_call() &&
                get_function() == rhs.get_function() &&
                get_arguments() == rhs.get_arguments() &&
                get_environment() == rhs.get_environment());
    }

    bool operator!=(const ClosureExecutionContext &rhs) const {
        return !(*this == rhs);
    }

    const sexptype_t get_type() const override { return CLOSXP; }
};

#endif /* EVALDYNTRACER_CLOSURE_EXECUTION_CONTEXT_H */
