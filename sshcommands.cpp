#include "sshcommands.h"

SshCommands::SshCommands()
{
    process = std::make_unique<QProcess>();
    process->setProcessChannelMode(QProcess::MergedChannels);
    _port = "22";
}

void SshCommands::setLogin(QString login) {
    if (login == "")
        _login = "root";
    else
        _login = login;
}

void SshCommands::setPassword(QString password) {
    if (password == "")
        _password = "0000";
    else
        _password = password;
}

void SshCommands::setIp(QString ip) {
    if (ip == "")
        _ip = "192.168.1.1";
    else
        _ip = ip;
}

void SshCommands::setPort(QString port) {
    _port = port;
}

bool SshCommands::exportFile(QString localPathToFile, QString remotePathToDir) {
    QString commandExport;
    commandExport = "sshpass -p "+_password+
                    " scp -P "+_port+" "+localPathToFile+" "+
                    _login+"@"+_ip+":"+remotePathToDir;
    process->start(commandExport);
    qDebug() << commandExport;
    if(process->waitForStarted(2000) & process->waitForFinished(5000) )
        if (process->readAll() == "")
            return true;
        else
            return false;
    else
        return false;
}

bool SshCommands::importFile(QString remotePathToFile, QString localPathToDir) {
    QString commandImport;
    commandImport = "sshpass -p "+_password+
                    " scp -P "+_port+" "+_login+"@"+_ip+":"+remotePathToFile+
                    " "+localPathToDir;
    process->start(commandImport);
    qDebug() << commandImport;
    if(process->waitForStarted(2000) & process->waitForFinished(5000) ) {
        if (process->readAll() == "")
            return true;
        else
            return false;
    }
    else {
        return false;
    }
}
