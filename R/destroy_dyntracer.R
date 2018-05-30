#' @include evaldyntracer.R
NULL

#' Destroy evaldyntracer
#'
#' @param evaldyntracer evaldyntracer object to destroy
#'
#' @return None
#'
#' @examples
#' destroy_dyntracer(create_dyntracer("/tmp", list("eval_expression_analysis" = TRUE), TRUE))
#'
#' @export
destroy_dyntracer <- function(evaldyntracer)
    invisible(.Call(C_destroy_dyntracer, evaldyntracer))
