#ifndef SSHCOMMANDS_H
#define SSHCOMMANDS_H

#include <QProcess>
#include <QDebug>
#include <memory>

class SshCommands : public QObject
{
private:
    QString _login;
    QString _password;
    QString _ip;
    QString _port;

    std::unique_ptr<QProcess> process;

private slots:

public:
    SshCommands();

    void setPassword(QString);
    void setIp(QString);
    void setLogin(QString);
    void setPort(QString);

    bool exportFile(QString localPathToFile, QString remotePathToDir);
    bool importFile(QString localPathToDir, QString remotePathToFile);
};

#endif // SSHCOMMANDS_H
