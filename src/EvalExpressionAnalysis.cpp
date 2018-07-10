#include "EvalExpressionAnalysis.h"

EvalExpressionAnalysis::EvalExpressionAnalysis(
    const Configuration &configuration,
    std::shared_ptr<ExecutionContextStack> execution_context_stack)
    : configuration_{configuration},
      execution_context_stack_{std::move(execution_context_stack)},
      expression_table_writer_{
          configuration.get_raw_analysis_dirpath() + "/" +
              "eval-expressions.tdf",
          {"eval_type", "caller", "caller_type", "line_number", "column_number",
           "directory_path", "filename", "callsite", "builtin", "special",
           "closure", "expression_type", "expression"}},
      opcounts_{} {}

void EvalExpressionAnalysis::closure_entry(
    const ClosureExecutionContext &context) {

    auto eval_type = configuration_.get_eval_type(context.get_function());

    if (eval_type) {
        opcounts_.push_back({0, 0, 0});
    } else {
        std::for_each(opcounts_.begin(), opcounts_.end(),
                      [](opcount_t &opcount) { opcount.closure_count++; });
    }
}

void EvalExpressionAnalysis::closure_exit(
    const ClosureExecutionContext &context) {

    auto eval_type = configuration_.get_eval_type(context.get_function());

    if (!eval_type) {
        return;
    }

    std::string eval_name{get_eval_name(*eval_type)};

    const opcount_t opcount{opcounts_.back()};
    opcounts_.pop_back();

    SEXP value = context.get_argument("expr", true);

    if (value == R_UnboundValue) {
        dyntrace_log_error("'expr' not bound to a value in a call to '%s'",
                           eval_name.c_str());
    }

    sexptype_t type = TYPEOF(value);

    const auto[caller_name, caller_type, caller_function] =
        get_caller_information_();

    unsigned int line_number = 0;
    unsigned int column_number = 0;
    std::string directory_path;
    std::string filename;

    if (caller_function != nullptr) {
        SourceLocation source_location{
            SourceLocation::of_function(caller_function)};
        line_number = source_location.get_line_number();
        column_number = source_location.get_column_number();
        directory_path = source_location.get_directory_path().c_str();
        filename = source_location.get_filename().c_str();
    }

    expression_table_writer_.write_row(
        eval_name, caller_name, sexptype_to_string(caller_type), line_number,
        column_number, directory_path.c_str(), filename.c_str(),
        std::string(serialize_sexp(context.get_call())), opcount.builtin_count,
        opcount.special_count, opcount.closure_count, sexptype_to_string(type),
        std::string(serialize_sexp(value)));
}

void EvalExpressionAnalysis::builtin_entry(
    const BuiltinExecutionContext &context) {
    std::for_each(opcounts_.begin(), opcounts_.end(),
                  [](opcount_t &opcount) { opcount.builtin_count++; });
}

void EvalExpressionAnalysis::special_entry(
    const SpecialExecutionContext &context) {
    std::for_each(opcounts_.begin(), opcounts_.end(),
                  [](opcount_t &opcount) { opcount.special_count++; });
}

void EvalExpressionAnalysis::context_jump(
    const execution_contexts_t &unwound_contexts) {

    for (auto iter = unwound_contexts.begin(); iter != unwound_contexts.end();
         ++iter) {
        if (std::holds_alternative<ClosureExecutionContext>(*iter)) {
            if (configuration_.get_eval_type(
                    std::get<ClosureExecutionContext>(*iter).get_function())) {
                opcounts_.pop_back();
            }
        }
    }
}

std::tuple<std::string, sexptype_t, SEXP>
EvalExpressionAnalysis::get_caller_information_() {
    std::string caller_name;
    sexptype_t caller_type;
    SEXP caller_function = nullptr;

    auto last_context =
        execution_context_stack_
            ->get_last_execution_context<ClosureExecutionContext>(CLOSXP);

    if (last_context) {
        auto closure_context = *last_context;
        caller_name = closure_context.get_name();
        caller_type = closure_context.get_type();
        caller_function = closure_context.get_function();
    } else {
        auto top_level_context =
            execution_context_stack_->get_top_level_execution_context();
        caller_name = top_level_context.get_name();
        caller_type = top_level_context.get_type();
    }

    return std::make_tuple(caller_name, caller_type, caller_function);
}
