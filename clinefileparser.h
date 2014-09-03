#ifndef CLINEFILEPARSER_H
#define CLINEFILEPARSER_H

#include "cline.h"
#include <QList>

class CLineFileParser
{
public:
    CLineFileParser();
    static QList<CLine> getCLines(QString filepath);
    static bool isCLine(QString txt);
    static CLine parseCLine(QString txt);
};

#endif // CLINEFILEPARSER_H
