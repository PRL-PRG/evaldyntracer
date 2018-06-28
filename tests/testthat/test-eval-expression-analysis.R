context("eval expression analysis")

library(withr)
library(evaldyntracer)

test_that_in_temp_dir <- function(desc, ...) {
    path <- tempfile()
    unlink(path, recursive = TRUE, force = TRUE)
    dir.create(path)
    with_dir(path, test_that(desc, ...))
}

test_that_in_temp_dir("eval expression analysis captures all members of the 'eval' family", {

    analysis_dirpath <- file.path(getwd(), "analysis")

    evaldyntracer::dyntrace_evals({
        x <- 23
        y <- 15
        a <- "a"
        b <- "b"
        ab <- 25
        base::eval(quote(1 + 2 + 3))
        base::evalq(expr = "a")
        eval(envir = new.env(), expr = quote(eval.parent(evalq(x + y))))
        base::eval(quote(eval.parent(get(paste0(a, b))) + eval(5)))
        local(x + y)
    }, analysis_dirpath, verbose = FALSE)

    eval_expression_table <- read.csv(file.path(analysis_dirpath, "eval-expressions.tdf"),
                                      sep = "#",
                                      stringsAsFactors = FALSE)

    expect_gte(nrow(eval_expression_table), 9)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(1 + 2 + 3)")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(eval.parent(evalq(x + y)))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(eval.parent(get(paste0(a, b))) + eval(5))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "5")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::evalq" &
                             expression == "a")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::evalq" &
                             expression == "x + y")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval.parent" &
                             expression == "evalq(x + y)")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval.parent" &
                             expression == "get(paste0(a, b))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::local" &
                             expression == "x + y")), 1)
})

test_that_in_temp_dir("eval expression analysis captures aliased members of the 'eval' family", {

    analysis_dirpath <- file.path(getwd(), "analysis")

    evaldyntracer::dyntrace_evals({
        be <- base::eval
        beq <- base::evalq
        bep <- base::eval.parent
        bl <- base::local
        x <- 23
        y <- 15
        a <- "a"
        b <- "b"
        ab <- 25
        be(quote(1 + 2 + 3))
        beq(expr = "a")
        be(envir = new.env(), expr = quote(bep(beq(x + y))))
        be(quote(bep(get(paste0(a, b))) + be(5)))
        bl(x + y)
    }, analysis_dirpath, verbose = FALSE)

    eval_expression_table <- read.csv(file.path(analysis_dirpath, "eval-expressions.tdf"),
                                      sep = "#",
                                      stringsAsFactors = FALSE)

    expect_gte(nrow(eval_expression_table), 9)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(1 + 2 + 3)")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(bep(beq(x + y)))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "quote(bep(get(paste0(a, b))) + be(5))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval" &
                             expression == "5")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::evalq" &
                             expression == "a")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::evalq" &
                             expression == "x + y")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval.parent" &
                             expression == "beq(x + y)")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::eval.parent" &
                             expression == "get(paste0(a, b))")), 1)

    expect_equal(nrow(subset(eval_expression_table,
                             eval_type == "base::local" &
                             expression == "x + y")), 1)
})
