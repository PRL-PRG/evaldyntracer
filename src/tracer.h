#ifndef __TRACER_H__
#define __TRACER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "Rincludes.h"

SEXP create_dyntracer(SEXP evals, SEXP raw_analysis_dirpath,
                      SEXP analysis_flags, SEXP verbose);

SEXP destroy_dyntracer(SEXP dyntracer);

#ifdef __cplusplus
}
#endif

#endif /* __TRACER_H__ */
