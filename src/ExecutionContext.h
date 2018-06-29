#ifndef __EXECUTION_CONTEXT_H__
#define __EXECUTION_CONTEXT_H__

#include "sexptype.h"
#include <string>

class ExecutionContext {
  public:
    explicit ExecutionContext() {}

    virtual const sexptype_t get_type() const = 0;

    virtual const std::string get_name() const = 0;

    virtual ~ExecutionContext() {}
};

#endif /* __EXECUTION_CONTEXT_H__ */
