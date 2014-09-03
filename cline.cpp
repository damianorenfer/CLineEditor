#include "cline.h"
#include <QRegExp>

CLine::CLine(QString server, int port, QString username, QString password)
{
    setServer(server);
    setPort(port);
    setUsername(username);
    setPassword(password);
}

QString CLine::toString() const
{
    return QString("C: %1 %2 %3 %4").arg(getServer()).arg(getPort()).arg(getUsername()).arg(getPassword());
}

bool CLine::sortOnServerAsc(const CLine &cline1, const CLine &cline2)
{
    return cline1.getServer() < cline2.getServer();
}

bool CLine::sortOnServerDesc(const CLine &cline1, const CLine &cline2)
{
    return !sortOnServerAsc(cline1, cline2);
}

bool CLine::sortOnPortAsc(const CLine &cline1, const CLine &cline2)
{
    return cline1.getPort() < cline2.getPort();
}

bool CLine::sortOnPortDesc(const CLine &cline1, const CLine &cline2)
{
    return !sortOnPortAsc(cline1, cline2);
}

bool CLine::sortOnUsernameAsc(const CLine &cline1, const CLine &cline2)
{
    return cline1.getUsername() < cline2.getUsername();
}

bool CLine::sortOnUsernameDesc(const CLine &cline1, const CLine &cline2)
{
    return !sortOnUsernameAsc(cline1, cline2);
}

bool CLine::sortOnPasswordAsc(const CLine &cline1, const CLine &cline2)
{
    return cline1.getPassword() < cline2.getPassword();
}

bool CLine::sortOnPasswordDesc(const CLine &cline1, const CLine &cline2)
{
    return !sortOnPasswordAsc(cline1, cline2);
}

bool CLine::isServerValid(QString server)
{
    QRegExp re("^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$");
    return re.exactMatch(server);
}

bool CLine::isPortValid(int port)
{
    return port > 0 && port < 65536;
}

bool CLine::isUsernameValid(QString username)
{
    QRegExp re("^.{3,20}$");
    return re.exactMatch(username);
}

bool CLine::isPasswordValid(QString password)
{
    QRegExp re("^.{3,20}$");
    return re.exactMatch(password);
}

QDebug operator<<(QDebug dbg, const CLine &cline)
{
    dbg << cline.toString();
    return dbg;
}


int CLine::getPort() const
{
    return port;
}

void CLine::setPort(int value)
{
    port = value;
}

QString CLine::getPassword() const
{
    return password;
}

void CLine::setPassword(const QString &value)
{
    password = value;
}

QString CLine::getUsername() const
{
    return username;
}

void CLine::setUsername(const QString &value)
{
    username = value;
}

QString CLine::getServer() const
{
    return server;
}

void CLine::setServer(const QString &value)
{
    server = value;
}
