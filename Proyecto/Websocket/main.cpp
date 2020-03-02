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
*
* Se implementa el soporte para traducciones.
*
* A continuación, se procede a iniciar el servidor.
*/

int main(int argc, char *argv[])
{

    // Implementación de soporte para traducciones.

    QCoreApplication app(argc, argv);
    QTranslator traductor;

    if (traductor.load("traductor_"+QLocale::system().name(), "../Websocket"))
    {
        app.installTranslator(&traductor);
    }; // end if



    //Se crea instancia de la clase servidor, y se llama a la función para iniciarlo.


    Servidor *servidor;
    servidor->iniciarServidor();
}
