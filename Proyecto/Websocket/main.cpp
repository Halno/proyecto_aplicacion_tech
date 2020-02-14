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
#include <QTranslator>
#include "QSqlError"
using JSON = nlohmann::json;

/*!\file */


/**
* Función principal del programa.
*/

int main(int argc, char *argv[])
{
    /**
    * Implementación de soporte para traducciones.
    */

    QCoreApplication app(argc, argv);
    QTranslator traductor;

    if (traductor.load("traductor_"+QLocale::system().name(), "../Websocket"))
    {
        app.installTranslator(&traductor);
    };

    /**
    * Conexión con la base de datos.
    */

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
        qDebug() << QObject::tr("Error al intentar iniciar la base de datos");
        qDebug() << db.lastError().text();
    }


    /**
    * Se crea instancia de la clase servidor, y se llama a la función
    * para iniciarlo.
    */

    Servidor *servidor;
    servidor->iniciarServidor();
}
