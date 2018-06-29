#ifndef __EXECUTION_CONTEXT_STACK_H__
#define __EXECUTION_CONTEXT_STACK_H__

#include "BuiltinExecutionContext.h"
#include "ClosureExecutionContext.h"
#include "RExecutionContext.h"
#include "SpecialExecutionContext.h"
#include "TopLevelExecutionContext.h"
#include <optional>
#include <variant>
#include <vector>

using execution_context_t =
    std::variant<TopLevelExecutionContext, RExecutionContext,
                 BuiltinExecutionContext, SpecialExecutionContext,
                 ClosureExecutionContext>;

using execution_contexts_t = std::vector<execution_context_t>;

class ExecutionContextStack {
  public:
    using const_iterator = execution_contexts_t::const_iterator;
    using const_reverse_iterator = execution_contexts_t::const_reverse_iterator;

    explicit ExecutionContextStack() : stack_{} {}

    template <typename T> void push(const T &context) {
        stack_.push_back(context);
    }

    execution_context_t pop() {
        execution_context_t context{peek(1)};
        stack_.pop_back();
        return context;
    }

    execution_context_t peek(size_t n = 1) const {
        n = stack_.size() - std::min(n, stack_.size());
        return stack_[n];
    }

    execution_contexts_t unwind(const RExecutionContext &context) {
        execution_contexts_t unwound_contexts;

        while (size() > 1) {

            execution_context_t temp_context{pop()};

            if (std::holds_alternative<RExecutionContext>(temp_context)) {

                if (context == std::get<RExecutionContext>(temp_context)) {
                    push(temp_context);
                    return unwound_contexts;
                }
            }
            unwound_contexts.push_back(temp_context);
        }

        dyntrace_log_error("cannot find matching execution context\n");
    }

    std::optional<execution_context_t>
    get_last_execution_context(sexptype_t type) const {
        sexptype_t current_type;
        for (const_reverse_iterator iter = crbegin(); iter != crend(); ++iter) {
            current_type = std::visit(
                [](auto &&arg) -> sexptype_t { return arg.get_type(); }, *iter);
            if (current_type == type)
                return *iter;
        }
        return {};
    }

    TopLevelExecutionContext get_top_level_execution_context() const {
        return std::get<TopLevelExecutionContext>(stack_[0]);
    }

    size_t size() const { return stack_.size(); }

    const_iterator cbegin() const { return stack_.cbegin(); }

    const_iterator cend() const { return stack_.cend(); }

    const_reverse_iterator crbegin() const { return stack_.crbegin(); }

    const_reverse_iterator crend() const { return stack_.crend(); }

  private:
    execution_contexts_t stack_;
};

#endif /* __EXECUTION_CONTEXT_STACK_H__ */
