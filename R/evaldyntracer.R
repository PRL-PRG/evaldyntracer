create_dyntracer <- function() .Call(C_create_dyntracer)

destroy_dyntracer <- function(dyntracer)
    invisible(.Call(C_destroy_dyntracer, dyntracer))

dyntrace_eval <- function(expr) {
    dyntracer <- create_dyntracer()
    result <- dyntrace(dyntracer, expr)
    destroy_dyntracer(dyntracer)
    result
}
