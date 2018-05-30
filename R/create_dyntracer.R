#' @include evaldyntracer.R
NULL

#' Create evaldyntracer
#'
#' @param raw_analysis_dirpath directory path for storing raw analysis data
#' @param analysis_flags flags for enabling/disabling analyses
#' @param verbose enable echoing of information
#'
#' @return evaldyntracer
#'
#' @examples
#' create_dyntracer("/tmp", list("eval_expression_analysis" = TRUE), TRUE)
#'
#' @export
create_dyntracer <- function(raw_analysis_dirpath, analysis_flags, verbose) {
    dir.create(raw_analysis_dirpath, showWarnings=FALSE, recursive=TRUE)
    .Call(C_create_dyntracer, list("base::eval" = base::eval,
                                   "base::evalq" = base::evalq,
                                   "base::eval.parent" = base::eval.parent,
                                   "base::local" = base::local),
          raw_analysis_dirpath, analysis_flags, verbose)
}
