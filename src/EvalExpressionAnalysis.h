#ifndef __EVAL_EXPRESSION_ANALYSIS_H__
#define __EVAL_EXPRESSION_ANALYSIS_H__

#include "Configuration.h"
#include "ExecutionContextStack.h"
#include "Rincludes.h"
#include "SourceLocation.h"
#include "TableWriter.h"
#include <memory>

class EvalExpressionAnalysis {
  public:
    explicit EvalExpressionAnalysis(
        const Configuration &configuration,
        std::shared_ptr<ExecutionContextStack> execution_context_stack);
    void closure_entry(const ClosureExecutionContext &context);
    void closure_exit(const ClosureExecutionContext &context);
    void builtin_entry(const BuiltinExecutionContext &context);
    void special_entry(const SpecialExecutionContext &context);
    void context_jump(const execution_contexts_t &unwound_contexts);

  private:
    const Configuration configuration_;
    const std::shared_ptr<ExecutionContextStack> execution_context_stack_;
    TableWriter expression_table_writer_;
    std::tuple<std::string, sexptype_t, SEXP> get_caller_information_();

    struct opcount_t {
        size_t closure_count;
        size_t builtin_count;
        size_t special_count;
    };
    std::vector<opcount_t> opcounts_;
};

#endif /* __EVAL_EXPRESSION_ANALYSIS_H__ */
