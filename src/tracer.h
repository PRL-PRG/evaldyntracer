#ifndef EVALDYNTRACER_TRACER_H
#define EVALDYNTRACER_TRACER_H

#include "Rincludes.h"

#ifdef __cplusplus
extern "C" {
#endif

SEXP create_dyntracer(SEXP evals, SEXP raw_analysis_dirpath,
                      SEXP analysis_flags, SEXP verbose);

SEXP destroy_dyntracer(SEXP dyntracer);

#ifdef __cplusplus
}
#endif

#endif /* EVALDYNTRACER_TRACER_H */
