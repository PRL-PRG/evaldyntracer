#ifndef __R_INCLUDES_H__
#define __R_INCLUDES_H__

#define USE_RINTERNALS
#include <Rinternals.h>
#undef TRUE
#undef FALSE
#undef length
#undef eval
#undef error

#include <config.h>
#include <stdint.h>
#define R_USE_SIGNALS 1
#define HAVE_DECL_SIZE_MAX 1

#include <Defn.h>
#include <Rdyntrace.h>

#endif /* __R_INCLUDES_H__ */
