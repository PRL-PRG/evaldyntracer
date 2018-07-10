#ifndef EVALDYNTRACER_UTILITIES_H
#define EVALDYNTRACER_UTILITIES_H

#include "Rincludes.h"
#include <cstdlib>
#include <functional>
#include <string>
#include <unordered_map>

#define verbose_log_info(verbose, info, ...)                                   \
    do {                                                                       \
        if (verbose)                                                           \
            dyntrace_log_info(info, ##__VA_ARGS__);                            \
    } while (0);

inline bool index_logical_rvector(const SEXP rvector, size_t index = 0) {
    return LOGICAL(rvector)[index] == TRUE;
}

inline int index_real_rvector(const SEXP rvector, size_t index = 0) {
    return REAL(rvector)[index];
}

inline unsigned int index_integer_rvector(const SEXP rvector,
                                          size_t index = 0) {
    return INTEGER(rvector)[index];
}

inline std::string index_character_rvector(const SEXP rvector,
                                           size_t index = 0) {
    return std::string(CHAR(STRING_ELT(rvector, index)));
}

inline bool rvector_to_bool(const SEXP rvector) {
    return index_logical_rvector(rvector, 0);
}

inline int rvector_to_int(const SEXP rvector) {
    return index_real_rvector(rvector, 0);
}

inline std::string rvector_to_string(const SEXP rvector) {
    return index_character_rvector(rvector, 0);
}

template <typename T> T identity(T value) { return value; }

inline std::string read_environment_variable(const char *envvar) {
    const char *value = std::getenv(envvar);
    return value ? value : "";
}

template <typename Value>
inline std::unordered_map<std::string, Value>
rlist_to_map(SEXP rlist, std::function<Value(SEXP)> transformer) {
    std::unordered_map<std::string, Value> mapping;
    SEXP keys = getAttrib(rlist, R_NamesSymbol);
    for (int index = 0; index < LENGTH(rlist); ++index) {
        mapping[index_character_rvector(keys, index)] =
            transformer(VECTOR_ELT(rlist, index));
    }
    return mapping;
}

inline void
transform_rlist(SEXP rlist,
                std::function<void(std::string, SEXP)> accumulator) {
    SEXP keys = getAttrib(rlist, R_NamesSymbol);
    for (int index = 0; index < LENGTH(rlist); ++index) {
        accumulator(index_character_rvector(keys, index),
                    VECTOR_ELT(rlist, index));
    }
}

#endif /* EVALDYNTRACER_UTILITIES_H */
