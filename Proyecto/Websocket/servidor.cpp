#include "servidor.h"
#include <QCoreApplication>
#include "json.hpp"
#include <iostream>
#include "../../IXWebSocket/ixwebsocket/IXWebSocketServer.h"
#include "../../IXWebSocket/ixwebsocket/IXWebSocket.h"
#include "../../IXWebSocket/ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "conexionusuarios.h"
#include <QString>
#include <QDebug>
using JSON = nlohmann::json;

int g_idMensaje = 0;
bool logeado = false;

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

int autocalcularIdServidor()
{
    g_idMensaje++;
    return g_idMensaje;
}

/**
* Comprueba que el JSON recibido contiene el campo indicado
*/

bool exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}


///Para probar, emplear la función "enviarLogin()" desde el cliente. Si usuario y contraseña no coinciden,
/// el websocket devuelve error. Solo podemos iniciar sesión si no lo hemos hecho antes.


JSON login(JSON receivedObject)
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


    if (!user.comprobarContrasenya())
    {
        respuesta["Error"]= 1;
        respuesta["mensajeError"]= "Nombre de usuario y/o contraseña incorrecto(s).";
    }
    else
    {
        if (logeado)
        {
            respuesta["mensaje"]= "Ya has iniciado sesión.";
        }
        else
        {
            user.loginAndLogout();
            respuesta["mensaje"] = "Has iniciado sesión con éxito";
            logeado=true;
        }

    }

    return respuesta;
}

///Para probar, emplear la función "enviarLogout()" desde el navegador. Solo podemos
/// cerrar sesión si ya la habíamos iniciado previamente.

JSON logout(JSON receivedObject)
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

        if (logeado)
        {
            user.loginAndLogout();
            respuesta["mensaje"]= "Has salido.";
            logeado=false;
        }
        else
        {
            respuesta["mensaje"] = "Aún no has iniciado sesión";
        }


    return respuesta;
}

///Para probar, emplear la función "enviarRegistro()" desde el navegador. Solo podemos
///registrarnos si el nombre de usuario no se encuentra en uso. Por defecto, "HHH" está en uso.

JSON registro(JSON receivedObject)
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

    if (user.registro(nombreUsuario))
    {
        respuesta["Error"]= 1;
        respuesta["mensajeError"]= "Nombre de usuario en uso. Elige otro.";
    }
    else
    {        
        user.insert();
        respuesta["mensaje"] = "Has completado el registro con éxito";
    }

    return respuesta;
}

JSON crearEntrada(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];

    //crearEntrada
    respuesta["mensaje"] = "Entrada creada.";


    return respuesta;

}

JSON consultarSeccion(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    //respuesta["listaEntradas"] = función para crear la lista de entradas

    return respuesta;

}


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
    }

    server.setTLSOptions(tlsOptions);

    qDebug() << QObject::tr("Bienvenido.");


    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
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
                            /// Text format
                            qDebug() << QObject::tr("Mensaje recibido:");
                        }


                        auto receivedObject = JSON::parse(msg->str);

                        if (receivedObject.is_discarded())
                        {
                            qDebug() << QObject::tr("Error");
                        }
                        else
                        {
                                ///JSON válido
                                if (exists(receivedObject, "tipo"))
                                {
                                    std::string tipo = receivedObject["tipo"];

                                    if (tipo=="login")
                                    {
                                        JSON respuesta = login(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }


                                    if (tipo=="crearEntrada")
                                    {
                                        JSON respuesta=crearEntrada(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }

                                    if (tipo=="consultarSeccion")
                                    {
                                        JSON respuesta = consultarSeccion(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }


                                    if (tipo=="registro")
                                    {
                                        JSON respuesta = registro(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }


                                    if (tipo=="logout")
                                    {
                                        JSON respuesta = logout(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }

                                }
                                else
                                {
                                    qDebug() << QObject::tr("Error: falta tipo en el mensaje.");
                                }
                        }
                    }
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
