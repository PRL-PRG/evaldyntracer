#ifndef EVALDYNTRACER_SPECIAL_EXECUTION_CONTEXT_H
#define EVALDYNTRACER_SPECIAL_EXECUTION_CONTEXT_H

#include "FunctionExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>

class SpecialExecutionContext : public FunctionExecutionContext {
  public:
    explicit SpecialExecutionContext(const SEXP call, const SEXP op,
                                     const SEXP args, const SEXP rho)
        : FunctionExecutionContext{call, op, args, rho} {}

    const sexptype_t get_type() const override { return SPECIALSXP; }
};

#endif /* EVALDYNTRACER_SPECIAL_EXECUTION_CONTEXT_H */
