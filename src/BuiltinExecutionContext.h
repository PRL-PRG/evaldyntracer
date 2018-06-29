#ifndef __BUILTIN_EXECUTION_CONTEXT_H__
#define __BUILTIN_EXECUTION_CONTEXT_H__

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

#endif /* __BUILTIN_EXECUTION_CONTEXT_H__ */
