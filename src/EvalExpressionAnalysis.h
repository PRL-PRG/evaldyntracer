#ifndef __EVAL_EXPRESSION_ANALYSIS_H__
#define __EVAL_EXPRESSION_ANALYSIS_H__

#include "Configuration.h"
#include "Rincludes.h"
#include "TableWriter.h"

class EvalExpressionAnalysis {
  public:
    explicit EvalExpressionAnalysis(const Configuration &configuration);
    void closure_entry(const SEXP call, const SEXP op, const SEXP args,
                       const SEXP rho);

  private:
    const Configuration configuration_;
    TableWriter expression_table_writer_;
};

#endif /* __EVAL_EXPRESSION_ANALYSIS_H__ */
