#ifndef SSHCOMMANDS_H
#define SSHCOMMANDS_H

#include <QProcess>
#include <QDebug>

class SshCommands
{
private:
    QString _login;
    QString _password;
    QString _ip;
    QString _port;

    QProcess process;

public:
    SshCommands();

    void setPassword(QString);
    void setIp(QString);
    void setLogin(QString);
    void setPort(QString);

    void exportFile(QString localPathToFile, QString remotePathToDir);
    void importFile(QString localPathToDir, QString remotePathToFile);
};

#endif // SSHCOMMANDS_H
