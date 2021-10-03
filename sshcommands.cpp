#include "sshcommands.h"

SshCommands::SshCommands()
{
    _port = "22";
}

void SshCommands::setLogin(QString login) {
    _login = login;
}

void SshCommands::setPassword(QString password) {
    _password = password;
}

void SshCommands::setIp(QString ip) {
    _ip = ip;
}

void SshCommands::setPort(QString port) {
    _port = port;
}

void SshCommands::exportFile(QString localPathToFile, QString remotePathToDir) {
    QString commandExport;
    commandExport = "sshpass -p "+_password+
                    " scp -P "+_port+" "+localPathToFile+" "+
                    _login+"@"+_ip+":"+remotePathToDir;
    qDebug() << commandExport;
    process.start(commandExport);
    if( !process.waitForStarted() || !process.waitForFinished() ) {
            return;
    }
}
void SshCommands::importFile(QString remotePathToFile, QString localPathToDir) {
    QString commandImport;
    commandImport = "sshpass -p "+_password+
                    " scp -P "+_port+" "+_login+"@"+_ip+":"+remotePathToFile+
                    " "+localPathToDir;
    qDebug() << commandImport;
    process.start(commandImport);
    if( !process.waitForStarted() || !process.waitForFinished() ) {
            return;
    }
}

