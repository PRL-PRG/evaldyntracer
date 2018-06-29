#ifndef __TOP_LEVEL_EXECUTION_CONTEXT_H__
#define __TOP_LEVEL_EXECUTION_CONTEXT_H__

#include "ExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>
#include <string>

class TopLevelExecutionContext : public ExecutionContext {
  public:
    explicit TopLevelExecutionContext(const SEXP environment)
        : ExecutionContext{}, environment_{environment}, result_{nullptr},
          error_{0} {}

    const sexptype_t get_type() const override { return TOPLEVELSXP; }

    const std::string get_name() const override { return "**top-level**"; }

    const SEXP get_environment() const { return environment_; }

    void set_result(SEXP result) { result_ = result; }

    const SEXP get_result() const { return result_; }

    void set_error(int error) { error_ = error; }

    int get_error() const { return error_; }

  private:
    const SEXP environment_;
    SEXP result_;
    int error_;
};

#endif /* __TOP_LEVEL_EXECUTION_CONTEXT_H__ */
