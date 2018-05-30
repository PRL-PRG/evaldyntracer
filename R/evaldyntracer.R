#' evaldyntracer: a dynamic tracer for eval
#'
#' evaldyntracer is an R package for tracing usage of the eval function. It
#' intercepts and analyzes the usage and impact of eval in R code. It also
#' exports the intercepted data for further summarization and analysis.
#'
#' @useDynLib evaldyntracer, .registration = TRUE, .fixes="C_"
"_PACKAGE"
