#ifndef __TOP_LEVEL_EXECUTION_CONTEXT_H__
#define __TOP_LEVEL_EXECUTION_CONTEXT_H__

#include "sexptype.h"
#include <Rinternals.h>
#include <string>

class TopLevelExecutionContext {
  public:
    explicit TopLevelExecutionContext(const SEXP environment)
        : environment_{environment} {}

    const std::string get_name() const { return std::string("**top-level**"); }

    const sexptype_t get_type() const { return TOPLEVELSXP; }

    const SEXP get_environment() const { return environment_; }

  private:
    const SEXP environment_;
};

#endif /* __TOP_LEVEL_EXECUTION_CONTEXT_H__ */
