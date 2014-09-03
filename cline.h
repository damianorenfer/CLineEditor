#ifndef CLINE_H
#define CLINE_H

#include <QString>
#include <QDebug>

class CLine
{
public:
    CLine(QString server="", int port=0, QString username="", QString password="");

    QString toString() const;

    static bool sortOnServerAsc(const CLine &cline1, const CLine &cline2);
    static bool sortOnServerDesc(const CLine &cline1, const CLine &cline2);
    static bool sortOnPortAsc(const CLine &cline1, const CLine &cline2);
    static bool sortOnPortDesc(const CLine &cline1, const CLine &cline2);
    static bool sortOnUsernameAsc(const CLine &cline1, const CLine &cline2);
    static bool sortOnUsernameDesc(const CLine &cline1, const CLine &cline2);
    static bool sortOnPasswordAsc(const CLine &cline1, const CLine &cline2);
    static bool sortOnPasswordDesc(const CLine &cline1, const CLine &cline2);

    static bool isServerValid(QString server);
    static bool isPortValid(int port);
    static bool isUsernameValid(QString username);
    static bool isPasswordValid(QString password);

    QString getServer() const;
    QString getUsername() const;
    QString getPassword() const;
    int getPort() const;

    void setServer(const QString &value);
    void setUsername(const QString &value);
    void setPassword(const QString &value);
    void setPort(int value);

    friend QDebug operator<<(QDebug dbg, const CLine &cline);

private:
    QString server;
    QString username;
    QString password;
    int port;
};

#endif // CLINE_H
