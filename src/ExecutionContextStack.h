#ifndef __EXECUTION_CONTEXT_STACK_H__
#define __EXECUTION_CONTEXT_STACK_H__

#include "FunctionExecutionContext.h"
#include "TopLevelExecutionContext.h"
#include <variant>
#include <vector>

using execution_context_t =
    std::variant<TopLevelExecutionContext, FunctionExecutionContext>;

class ExecutionContextStack {
    using execution_contexts_t = std::vector<execution_context_t>;

  public:
    using const_iterator = execution_contexts_t::const_iterator;

    explicit ExecutionContextStack() : stack_{} {}

    template <typename T> void push(const T &context) {
        stack_.push_back(context);
    }

    execution_context_t pop() {
        execution_context_t context{peek(1)};
        stack_.pop_back();
        return context;
    }

    execution_context_t peek(size_t n = 2) const {
        n = stack_.size() - std::min(n, stack_.size());
        return stack_[n];
    }

    std::vector<execution_context_t> unwind() { return {}; }

    size_t size() const { return stack_.size(); }

    const_iterator begin() const { return stack_.begin(); }

    const_iterator end() const { return stack_.end(); }

    const_iterator cbegin() const { return stack_.cbegin(); }

    const_iterator cend() const { return stack_.cend(); }

  private:
    execution_contexts_t stack_;
};

#endif /* __EXECUTION_CONTEXT_STACK_H__ */
