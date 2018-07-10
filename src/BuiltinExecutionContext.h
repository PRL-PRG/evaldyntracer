#ifndef EVALDYNTRACER_BUILTIN_EXECUTION_CONTEXT_H
#define EVALDYNTRACER_BUILTIN_EXECUTION_CONTEXT_H

#include "FunctionExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>

class BuiltinExecutionContext : public FunctionExecutionContext {
  public:
    explicit BuiltinExecutionContext(const SEXP call, const SEXP op,
                                     const SEXP args, const SEXP rho)
        : FunctionExecutionContext{call, op, args, rho} {}

    const sexptype_t get_type() const override { return BUILTINSXP; }
};

#endif /* EVALDYNTRACER_BUILTIN_EXECUTION_CONTEXT_H */
