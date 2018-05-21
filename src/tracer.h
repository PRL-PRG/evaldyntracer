#ifndef __TRACER_H__
#define __TRACER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Rinternals.h>
#include <Rdyntrace.h>

SEXP create_dyntracer();

SEXP destroy_dyntracer(SEXP dyntracer);

#ifdef __cplusplus
}
#endif

#endif /* __TRACER_H__ */
