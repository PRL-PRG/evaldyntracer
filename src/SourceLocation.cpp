#include "SourceLocation.h"

SourceLocation SourceLocation::of_function(SEXP function, SEXP environment) {
    return SourceLocation(get_line_number_(function, environment),
                          get_column_number_(function, environment),
                          get_directory_path_(function, environment),
                          get_filename_(function, environment));
}

unsigned int SourceLocation::get_line_number_(SEXP function, SEXP environment) {
    dyntrace_enable_privileged_mode();

    SEXP line_number_sexp;
    unsigned int line_number;

    PROTECT(line_number_sexp =
                Rf_eval(lang3(install("getSrcLocation"), function,
                              ScalarString(mkChar("line"))),
                        environment));

    if (LENGTH(line_number_sexp) > 0)
        line_number = index_integer_rvector(line_number_sexp);

    UNPROTECT(1);

    dyntrace_disable_privileged_mode();

    return line_number;
}

unsigned int SourceLocation::get_column_number_(SEXP function,
                                                SEXP environment) {
    dyntrace_enable_privileged_mode();

    SEXP column_number_sexp;
    unsigned int column_number;

    PROTECT(column_number_sexp =
                Rf_eval(lang3(install("getSrcLocation"), function,
                              ScalarString(mkChar("column"))),
                        environment));

    if (LENGTH(column_number_sexp) > 0)
        column_number = index_integer_rvector(column_number_sexp);

    UNPROTECT(1);

    dyntrace_disable_privileged_mode();

    return column_number;
}

std::string SourceLocation::get_directory_path_(SEXP function,
                                                SEXP environment) {
    dyntrace_enable_privileged_mode();

    SEXP directory_path_sexp;
    std::string directory_path;

    PROTECT(directory_path_sexp = Rf_eval(
                lang2(install("getSrcDirectory"), function), environment));

    if (LENGTH(directory_path_sexp) > 0)
        directory_path = index_character_rvector(directory_path_sexp);

    UNPROTECT(1);

    dyntrace_disable_privileged_mode();

    return directory_path;
}

std::string SourceLocation::get_filename_(SEXP function, SEXP environment) {
    dyntrace_enable_privileged_mode();

    SEXP filename_sexp;
    std::string filename;

    PROTECT(filename_sexp = Rf_eval(lang2(install("getSrcFilename"), function),
                                    environment));

    if (LENGTH(filename_sexp) > 0)
        filename = index_character_rvector(filename_sexp);

    UNPROTECT(1);

    dyntrace_disable_privileged_mode();

    return filename;
}
