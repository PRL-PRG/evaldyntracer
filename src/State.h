#ifndef EVALDYNTRACER_STATE_H
#define EVALDYNTRACER_STATE_H

#include "AnalysisDriver.h"
#include "Configuration.h"

class State {
  public:
    explicit State(const Configuration &configuration)
        : configuration_{configuration},
          analysis_driver_{std::make_unique<AnalysisDriver>(configuration)} {}

    const Configuration &get_configuration() const { return configuration_; }

    AnalysisDriver &get_analysis_driver() { return *analysis_driver_; }

  private:
    const Configuration configuration_;
    std::unique_ptr<AnalysisDriver> analysis_driver_;
};

#endif /* EVALDYNTRACER_STATE_H */
