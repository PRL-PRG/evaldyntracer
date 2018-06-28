#ifndef __SEXPTYPE_H__
#define __SEXPTYPE_H__

#include <Rinternals.h>

typedef int sexptype_t;

const int TOPLEVELSXP = 10001;

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

#endif /* __SEXPTYPE_H__ */
