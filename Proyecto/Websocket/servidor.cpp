#include "servidor.h"
#include <QCoreApplication>
#include "json.hpp"
#include <iostream>
#include "./websocket/include/ixwebsocket/IXWebSocketServer.h"
#include "./websocket/include/ixwebsocket/IXWebSocket.h"
#include "./websocket/include/ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "entrada.h"
#include <QString>
#include <QSqlError>
#include <QDebug>
using JSON = nlohmann::json;

    static int g_idMensaje;
    static QSqlDatabase db;

/**
* Método constructor de la clase Servidor.
*/

Servidor::Servidor()
{

}


/**
 * Crea la base de datos, ajusta sus parámetros y la devuelve para ser empleada.
 */

QSqlDatabase Servidor::getDatabase()
{
    QSqlDatabase db;
    db = (QSqlDatabase::addDatabase("QPSQL"));
    db.setHostName("localhost");
    db.setDatabaseName("tech");
    db.setPort(5432);
    //3306
    db.setUserName("postgres");
    db.setPassword("");
    return db;
}


/**
* Calcula el ID de los mensajes que enviará a los clientes
* a través del websocket y lo devuelve.
*/

int Servidor::autocalcularIdServidor()
{
    g_idMensaje++;
    return g_idMensaje;
}

/**
* Comprueba que el JSON recibido contiene el campo indicado
*/

bool Servidor::exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}


/**
* Construye y envía el JSON de respuesta cuando se realiza una petición de login.
* Comprueba que exista el usuario con la contraseña y nombre indicados en la petición.
* Si existe, el usuario inicia sesión.
* De lo contrario, se le informa de que se ha equivocado al introducir sus credenciales.
*/


JSON Servidor::login(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["Error"] = 0;
    respuesta["tipo_respuesta"]="respuesta_login";

    std::string nombre=receivedObject["usuario"];
    QString nombreUsuario = QString::fromUtf8(nombre.c_str());

    std::string password=receivedObject["contrasenya_Usuario"];
    QString passwordUsuario = QString::fromUtf8(password.c_str());

    Usuario user(nombreUsuario, passwordUsuario);


    if (!user.comprobarContrasenya(db))
    {
        respuesta["Error"]= 1;
        respuesta["mensajeError"]= "Nombre de usuario y/o contraseña incorrecto(s).";
    }
    else
    {
        user.loginAndLogout(db);
        user.load(nombreUsuario);
        respuesta["idUsuario"]= user.m_idUsuario;
    } // end if

    return respuesta;
}


/**
* Construye y envía el JSON de respuesta cuando se realiza una petición de logout.
* Comprueba que exista el usuario con la contraseña y nombre indicados en la petición.
* Si existe, el usuario cierra sesión.
* De lo contrario, se muestra un mensaje de error.
*/

JSON Servidor::logout(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["Error"] = 0;
    respuesta["tipo_respuesta"]="respuesta_logout";

    std::string nombre=receivedObject["usuario"];
    QString nombreUsuario = QString::fromUtf8(nombre.c_str());

    std::string password=receivedObject["contrasenya_Usuario"];
    QString passwordUsuario = QString::fromUtf8(password.c_str());

    Usuario user(nombreUsuario, passwordUsuario);

        if (user.comprobarContrasenya(db))
        {
            user.loginAndLogout(db);
            respuesta["mensaje"]= "Has salido.";
        }
        else
        {
            respuesta["Error"] = 1;
            respuesta["mensaje"] = "Error al cerrar sesión";
        } // end if


    return respuesta;
}


/**
* Construye y envía el JSON de respuesta cuando se realiza una petición de registro.
* Comprueba que no exista otro usuario con el nombre que se ha insertado.
* Si no existe, se registra a este nuevo usuario en la base de datos.
* De lo contrario, se le informa de que ese nombre de usuario ya existe, y que elija otro.
*/

JSON Servidor::registro(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["Error"] = 0;

    std::string nombre=receivedObject["usuario"];
    QString nombreUsuario = QString::fromUtf8(nombre.c_str());

    std::string password=receivedObject["contrasenya_Usuario"];
    QString passwordUsuario = QString::fromUtf8(password.c_str());

    Usuario user(nombreUsuario, passwordUsuario);

    if (user.registro(db))
    {
        respuesta["Error"]= 2;
        respuesta["mensajeError"]= "Nombre de usuario en uso. Elige otro.";
    }
    else
    {
        user.insert(db);
        respuesta["mensaje"] = "Has completado el registro con éxito";
    } // end if

    return respuesta;
}

/**
 * Construye y envía el JSON de respuesta cuando se realiza una petición para crear una entrada.
 * Se cogen los parámetros del JSON recibido y se transforman en datos.
 * Se crea la entrada en la base de datos con el contenido introducido por el usuario.
 * @param receivedObject Es el JSON enviado por el cliente, que contiene toda la información necesaria para realizar el insert en la base de datos.
 *
*/

JSON Servidor::crearEntrada(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["tipo_respuesta"] ="respuesta_crearEntrada";
    respuesta["Error"]=0;

    std::string per=receivedObject["seccion"];
    QString personaje=QString::fromUtf8(per.c_str());

    std::string con=receivedObject["tech"];
    QString contenido=QString::fromUtf8(con.c_str());

    int id_usuario=receivedObject["usuario"];

    Entrada nuevaTech(id_usuario, contenido, personaje);
    nuevaTech.insert();

    respuesta["mensaje"] = "Entrada creada.";


    return respuesta;

}


/**
* Construye y envía el JSON de respuesta cuando se realiza una petición de consulta de sección.
* Se accede a la base de datos y se cargan en el JSON que se va a enviar todas las entradas encontradas de la sección indicada.
*/

JSON Servidor::consultarSeccion(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["tipo_respuesta"]="respuesta_seccion";
    respuesta["Error"]=0;

    std::string per=receivedObject["seccion"];

    QString personaje=QString::fromUtf8(per.c_str());

    qDebug() << personaje;

    respuesta=Entrada::cargarEntradas(personaje, respuesta);

    return respuesta;

}

/**
* Realiza la conexión con la base de datos.
* Inicia el servidor websocket.
* El Websocket recibe los mensajes que envía el cliente, y en función del tipo
* de mensaje indicado en el JSON accederá a la función que corresponda que se
* encargará de generar el mensaje de respuesta de JSON. A continuación, el
* mensaje se envía.
*
* Además de responder al mensaje, el servidor interactúa con la base de datos
* en función de los mensajes que recibe.
*
*
*/

int Servidor::iniciarServidor()
{
    //Conexión con la base de datos.


    db = getDatabase();
    bool ok = db.open();
    if (!ok)
    {
        qDebug() << QObject::tr("Error al intentar iniciar la base de datos");
        qDebug() << db.lastError().text();
    } // end if


    //Se crea el servidor Websocket

    ix::WebSocketServer server(9990, "0.0.0.0");

    //Comprobación de certificados

    //ix::SocketTLSOptions tlsOptions;

    //tlsOptions.tls = true;
    //tlsOptions.certFile = "./cert/localhost.crt";
    //tlsOptions.keyFile = "./cert/localhost.key";
    //tlsOptions.caFile = "NONE";

    //if (tlsOptions.isValid())
    //{
      //  std::cerr << "SSL valid" << std::endl;
    //} // end if

    //server.setTLSOptions(tlsOptions);

    qDebug() << QObject::tr("Bienvenido.");


    server.setOnConnectionCallback(
        [&server, this](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server, this](const ix::WebSocketMessagePtr msg)
                {

                //Avisos al abrir y cerrar conexiones.

                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        qDebug() << QObject::tr("Nueva conexion");

                    }
                    else if (msg->type == ix::WebSocketMessageType::Close)
                    {
                        qDebug() << QObject::tr("Conexion cerrada");
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        if (!msg->binary)
                        {
                            qDebug() << QObject::tr("Mensaje recibido:");
                        }


                        auto mensajeRecibido = JSON::parse(msg->str);

                        if (mensajeRecibido.is_discarded())
                        {
                            qDebug() << QObject::tr("Error");
                        }
                        else
                        {
                                //JSON válido
                                if (exists(mensajeRecibido, "tipo"))
                                {
                                    std::string tipo = mensajeRecibido["tipo"];

                                    //En función del parámetro "tipo" del JSON, se procederá
                                    //a realizar una función u otra.


                                    if (tipo=="login")
                                    {
                                        JSON respuesta = login(mensajeRecibido);
                                        webSocket->send(respuesta.dump());
                                    } // end if


                                    if (tipo=="crearEntrada")
                                    {
                                        JSON respuesta=crearEntrada(mensajeRecibido);
                                        webSocket->send(respuesta.dump());
                                    } // end if

                                    if (tipo=="consultarSeccion")
                                    {
                                        JSON respuesta = consultarSeccion(mensajeRecibido);
                                        webSocket->send(respuesta.dump());
                                    } // end if


                                    if (tipo=="registro")
                                    {
                                        JSON respuesta = registro(mensajeRecibido);
                                        webSocket->send(respuesta.dump());
                                    } // end if


                                    if (tipo=="logout")
                                    {
                                        JSON respuesta = logout(mensajeRecibido);
                                        webSocket->send(respuesta.dump());
                                    } // end if

                                }
                                else
                                {
                                    qDebug() << QObject::tr("Error: falta tipo en el mensaje.");
                                } // end if
                        } // end if
                    } // end if
                }
            );
        }
    );

    auto res = server.listen();
    if (!res.first)
    {
        // Error handling
        return 1;
    }

    server.start();
    server.wait();
    server.stop();

}
