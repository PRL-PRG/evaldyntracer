#' @include evaldyntracer.R
NULL

#' Trace eval
#'
#' @param expr expression whose evaluation will be traced
#' @param raw_analysis_dirpath directory path for storing raw analysis data
#' @param analysis_flags flags for enabling/disabling analyses
#' @param verbose enable echoing of information
#'
#' @return result of evaluating expr or R_NilValue if an error occurs
#'
#' @examples
#' dyntrace_evals({ print(eval("Hello World")) }, "/tmp")
#'
#' @export
dyntrace_evals <- function(expr, raw_analysis_dirpath,
                           analysis_flags = list("eval_expression_analysis" = TRUE),
                           verbose=FALSE) {
    dyntracer <- create_dyntracer(raw_analysis_dirpath,
                                  analysis_flags, verbose)
    result <- dyntrace(dyntracer, expr)
    destroy_dyntracer(dyntracer)
    result
}
