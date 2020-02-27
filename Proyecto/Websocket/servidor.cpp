#include "servidor.h"
#include <QCoreApplication>
#include "json.hpp"
#include <iostream>
#include "../../IXWebSocket/ixwebsocket/IXWebSocketServer.h"
#include "../../IXWebSocket/ixwebsocket/IXWebSocket.h"
#include "../../IXWebSocket/ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "entrada.h"
#include <QString>
#include <QDebug>
using JSON = nlohmann::json;

    static int g_idMensaje;

/**
* Método constructor de la clase Servidor.
*/

Servidor::Servidor()
{

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


    if (!user.comprobarContrasenya())
    {
        respuesta["Error"]= 1;
        respuesta["mensajeError"]= "Nombre de usuario y/o contraseña incorrecto(s).";
    }
    else
    {
        user.loginAndLogout();
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

        if (user.comprobarContrasenya())
        {
            user.loginAndLogout();
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

    if (user.registro())
    {
        respuesta["Error"]= 2;
        respuesta["mensajeError"]= "Nombre de usuario en uso. Elige otro.";
    }
    else
    {
        user.insert();
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
    ix::WebSocketServer server(9990, "0.0.0.0");

    ix::SocketTLSOptions tlsOptions;

    tlsOptions.tls = true;
    tlsOptions.certFile = "./cert/localhost.crt";
    tlsOptions.keyFile = "./cert/localhost.key";
    tlsOptions.caFile = "NONE";

    if (tlsOptions.isValid())
    {
        std::cerr << "SSL valid" << std::endl;
    } // end if

    server.setTLSOptions(tlsOptions);

    qDebug() << QObject::tr("Bienvenido.");


    server.setOnConnectionCallback(
        [&server, this](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server, this](const ix::WebSocketMessagePtr msg)
                {
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
                            // Text format
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
