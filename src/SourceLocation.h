#ifndef EVALDYNTRACER_SOURCE_LOCATION_H
#define EVALDYNTRACER_SOURCE_LOCATION_H

#include "Rincludes.h"
#include "utilities.h"

class SourceLocation {
  public:
    explicit SourceLocation(SEXP function, SEXP environment = R_GlobalEnv)
        : line_number_{0}, column_number_{0}, directory_path_{""},
          filename_{""} {
        dyntrace_enable_privileged_mode();

        SEXP line_number;
        PROTECT(line_number = Rf_eval(lang3(install("getSrcLocation"), function,
                                            ScalarString(mkChar("line"))),
                                      environment));
        if (LENGTH(line_number) > 0)
            line_number_ = index_integer_rvector(line_number);

        SEXP column_number;
        PROTECT(column_number =
                    Rf_eval(lang3(install("getSrcLocation"), function,
                                  ScalarString(mkChar("column"))),
                            environment));
        if (LENGTH(column_number) > 0)
            column_number_ = index_integer_rvector(column_number);

        SEXP directory_path;
        PROTECT(directory_path = Rf_eval(
                    lang2(install("getSrcDirectory"), function), environment));
        if (LENGTH(directory_path) > 0)
            directory_path_ = index_character_rvector(directory_path);

        SEXP filename;
        PROTECT(filename = Rf_eval(lang2(install("getSrcFilename"), function),
                                   environment));
        if (LENGTH(filename) > 0)
            filename_ = index_character_rvector(filename);

        UNPROTECT(4);
        dyntrace_disable_privileged_mode();
    }

    unsigned int get_line_number() const { return line_number_; }

    unsigned int get_column_number() const { return column_number_; }

    const std::string &get_directory_path() const { return directory_path_; }

    const std::string &get_filename() const { return filename_; }

  private:
    unsigned int line_number_;
    unsigned int column_number_;
    std::string directory_path_;
    std::string filename_;
};

#endif /* EVALDYNTRACER_SOURCE_LOCATION_H */
