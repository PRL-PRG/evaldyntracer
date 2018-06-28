#include "EvalExpressionAnalysis.h"

EvalExpressionAnalysis::EvalExpressionAnalysis(
    const Configuration &configuration,
    std::shared_ptr<ExecutionContextStack> execution_context_stack)
    : configuration_{configuration},
      execution_context_stack_{execution_context_stack},
      expression_table_writer_{configuration.get_raw_analysis_dirpath() + "/" +
                                   "eval-expressions.tdf",
                               {"eval_type", "caller", "caller_type",
                                "callsite", "function", "expression_type",
                                "expression"}} {}

void EvalExpressionAnalysis::closure_entry(
    const FunctionExecutionContext &context) {

    for (auto &key_value : configuration_.get_evals()) {

        const std::string eval_name = key_value.first;
        const SEXP eval_function = key_value.second;

        if (context.get_function() == eval_function) {

            SEXP value = context.get_argument("expr", true);

            if (value == R_UnboundValue) {
                dyntrace_log_error(
                    "'expr' not bound to a value in a call to '%s'",
                    eval_name.c_str());
            }

            sexptype_t type = TYPEOF(value);
            SEXP function = R_NilValue;

            if (type == LANGSXP)
                function = CAR(value);

            const std::string caller_name{std::visit(
                [](auto &&arg) -> std::string { return arg.get_name(); },
                execution_context_stack_->peek())};

            const std::string caller_type{sexptype_to_string(std::visit(
                [](auto &&arg) -> sexptype_t { return arg.get_type(); },
                execution_context_stack_->peek()))};

            expression_table_writer_.write_row(
                eval_name, caller_name, caller_type,
                std::string(serialize_sexp(context.get_call())),
                std::string(serialize_sexp(function)), sexptype_to_string(type),
                std::string(serialize_sexp(value)));

            break;
        }
    }
}
