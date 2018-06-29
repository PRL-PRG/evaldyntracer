#ifndef __R_EXECUTION_CONTEXT_H__
#define __R_EXECUTION_CONTEXT_H__

#include "ExecutionContext.h"
#include "sexptype.h"
#include <Rinternals.h>
#include <string>

class RExecutionContext : public ExecutionContext {
  public:
    explicit RExecutionContext(const RCNTXT *context)
        : ExecutionContext{}, context_{context} {}

    const sexptype_t get_type() const override { return RCNTXTSXP; }

    const std::string get_name() const override { return "**r-context**"; }

    const RCNTXT *get_context() const { return context_; }

    bool operator==(const RExecutionContext &rhs) const {
        return (get_context() == rhs.get_context());
    }

    bool operator!=(const RExecutionContext &rhs) const {
        return !(*this == rhs);
    }

  private:
    const RCNTXT *context_;
};

#endif /* __TOP_LEVEL_EXECUTION_CONTEXT_H__ */
