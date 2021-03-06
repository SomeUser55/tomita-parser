#pragma once

#include <util/system/defaults.h>

enum NLP_TYPE {
    NLP_END,
    NLP_WORD,
    NLP_INTEGER,
    NLP_FLOAT,
    NLP_MARK,
    NLP_SENTBREAK,
    NLP_PARABREAK,
    NLP_MISCTEXT,
};

class Stroka;
const Stroka& ToString(NLP_TYPE);
bool FromString(const Stroka& name, NLP_TYPE& ret);

NLP_TYPE GuessTypeByWord(const char *w, unsigned len);
NLP_TYPE GuessTypeByWord(const wchar16 *w, unsigned len);

enum ESpaceType {
    ST_NOBRK = 0,
    ST_SENTBRK = 1,
    ST_PARABRK = 3, // parabrk is a sentbrk too
    ST_ZONEOPN = 4,
    ST_ZONECLS = 8
};

const Stroka& ToString(ESpaceType);
bool FromString(const Stroka& name, ESpaceType& ret);

inline ESpaceType GetSpaceType(NLP_TYPE type) {
    if (type == NLP_PARABREAK)
        return ST_PARABRK;
    if (type == NLP_SENTBREAK)
        return ST_SENTBRK;
    return ST_NOBRK;
}

typedef ui32 TBreakType;

inline bool IsSentBrk(TBreakType brk) {
    return brk & ST_SENTBRK;
}

inline bool IsParaBrk(TBreakType brk) {
    return brk & 2;
}

inline bool IsZoneOpn(TBreakType brk) {
    return brk & ST_ZONEOPN;
}

inline bool IsZoneCls(TBreakType brk) {
    return brk & ST_ZONECLS;
}

inline bool IsNoBrk(TBreakType brk) {
    return brk == 0;
}

const char* GetSpaceTypeString(TBreakType type);

class TTokenStructure;
NLP_TYPE DetectNLPType(const TTokenStructure& subtokens);
