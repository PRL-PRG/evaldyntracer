#ifndef EVALDYNTRACER_SOURCE_LOCATION_H
#define EVALDYNTRACER_SOURCE_LOCATION_H

#include "Rincludes.h"
#include "utilities.h"

class SourceLocation {
  public:
    static SourceLocation of_function(SEXP function,
                                      SEXP environment = R_GlobalEnv);

    unsigned int get_line_number() const { return line_number_; }

    unsigned int get_column_number() const { return column_number_; }

    const std::string &get_directory_path() const { return directory_path_; }

    const std::string &get_filename() const { return filename_; }

  private:
    explicit SourceLocation(unsigned int line_number,
                            unsigned int column_number,
                            const std::string &directory_path,
                            const std::string &filename)
        : line_number_{line_number}, column_number_{column_number},
          directory_path_{directory_path}, filename_{filename} {}

    static unsigned int get_line_number_(SEXP function, SEXP environment);

    static unsigned int get_column_number_(SEXP function, SEXP environment);

    static std::string get_directory_path_(SEXP function, SEXP environment);

    static std::string get_filename_(SEXP function, SEXP environment);

    unsigned int line_number_;
    unsigned int column_number_;
    std::string directory_path_;
    std::string filename_;
};

#endif /* EVALDYNTRACER_SOURCE_LOCATION_H */
