#include "clinefileparser.h"
#include <QFile>
#include <QRegExp>
#include <QMessageBox>

CLineFileParser::CLineFileParser()
{
}

QList<CLine> CLineFileParser::getCLines(QString filepath)
{    
    QList<CLine> listClines;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,QObject::tr("Download fail"), QObject::tr("Failed to open : %1").arg(file.fileName()));
        return QList<CLine>();
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        CLine cline = parseCLine(line);

        if(!cline.getServer().isEmpty())        
            listClines.append(cline);        
    }    
    file.close();

    return listClines;
}

bool CLineFileParser::isCLine(QString txt)
{    
    QRegExp re("^C: +(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9]) +[0-9]{2,5} +.{3,20} +.{3,20}$");
    return re.exactMatch(txt);
}

CLine CLineFileParser::parseCLine(QString txt)
{
    if(isCLine(txt))
    {
        txt.replace(QRegExp(" +"), " ");
        QStringList tokens = txt.split(' ');
        if(tokens.size() >= 5)
        {
            QString server = tokens[1];
            QString username = tokens[3];
            QString password = tokens[4];

            bool ok;
            int port = tokens[2].toInt(&ok);

            if(ok && port > 0 && port < 65535)
            {
                CLine cline(server, port, username, password);
                return cline;
            }
        }
    }
    return CLine();
}
