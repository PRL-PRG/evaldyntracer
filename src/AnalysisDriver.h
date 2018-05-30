#ifndef __ANALYSIS_DRIVER_H__
#define __ANALYSIS_DRIVER_H__

#include "Configuration.h"
#include "EvalExpressionAnalysis.h"
#include <memory>

class AnalysisDriver {

  public:
    explicit AnalysisDriver(const Configuration &configuration);
    void closure_entry(const SEXP call, const SEXP op, const SEXP args,
                       const SEXP rho);

  private:
    const Configuration configuration_;
    EvalExpressionAnalysis eval_expression_analysis_;
};

#endif /* __ANALYSIS_DRIVER_H__ */
