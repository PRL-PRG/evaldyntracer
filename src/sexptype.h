#ifndef EVALDYNTRACER_SEXPTYPE_H
#define EVALDYNTRACER_SEXPTYPE_H

#include <Rinternals.h>

using sexptype_t = int;

const int TOPLEVELSXP = 10001;
const int RCNTXTSXP = 10002;

inline std::string sexptype_to_string(const sexptype_t sexptype) {
    switch (sexptype) {
        case TOPLEVELSXP:
            return "Top Level";
        case NILSXP:
            return "Null";
        case LANGSXP:
            return "Function Call";
        case NEWSXP:
            return "New";
        case FREESXP:
            return "Free";
        case FUNSXP:
            return "Closure or Builtin";
        default:
            std::string str(type2char(sexptype));
            str[0] = std::toupper(str[0]);
            return str;
    }
}

#endif /* EVALDYNTRACER_SEXPTYPE_H */
