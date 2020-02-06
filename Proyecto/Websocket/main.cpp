#include <QCoreApplication>
#include "json.hpp"
#include <iostream>
#include "../../IXWebSocket/ixwebsocket/IXWebSocketServer.h"
#include "../../IXWebSocket/ixwebsocket/IXWebSocket.h"
#include "../../IXWebSocket/ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "servidor.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>
#include "QSqlError"
using JSON = nlohmann::json;



int main(int argc, char *argv[])
{

    QSqlDatabase db;
    db = (QSqlDatabase::addDatabase("QPSQL"));
    db.setHostName("localhost");
    db.setDatabaseName("tech");
    db.setPort(5432);
    //3306
    db.setUserName("postgres");
    db.setPassword("");
    bool ok = db.open();
    if (!ok)
    {
        qDebug("Error al intentar iniciar la base de datos");
        qDebug() << db.lastError().text();
    }

  Servidor *servidor;
  servidor->iniciarServidor();
}
