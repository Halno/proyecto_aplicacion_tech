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
using JSON = nlohmann::json;

int g_idMensaje = 0;
bool logeado = false;

Servidor::Servidor()
{

}



int autocalcularIdServidor()
{
    g_idMensaje++;
    return g_idMensaje;
}

bool exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}


///Para probar, emplear la función "enviarLogin()" desde el navegador. Si usuario y contraseña no coinciden,
/// el socket devuelve error. Por defecto, devolverá error al insertar como nombre "HHH". Solo podemos
/// iniciar sesión si no lo hemos hecho antes.

JSON login(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["Error"] = 0;


    if (receivedObject["usuario"] == "HHH")
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


        if (logeado)
        {
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


    if (receivedObject["usuario"] == "HHH")
    {
        respuesta["Error"]= 1;
        respuesta["mensajeError"]= "Nombre de usuario en uso. Elige otro.";
    }
    else
    {

        std::string nombre=receivedObject["nombre"];
        std::string password=receivedObject["password"];

        QString nombreUsuario = QString::fromUtf8(nombre.c_str());
        QString passwordUsuario = QString::fromUtf8(nombre.c_str());
        Usuario u(nombreUsuario, passwordUsuario);
        u.insert();

        respuesta["mensaje"] = "Has completado el registro con éxito";
    }

    return respuesta;
}

JSON crearEntrada(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["Error"] = 0;
    if (respuesta["Error"]==0)
    {
        respuesta["mensaje"] = "Entrada creada.";
    }
    else
    {
        respuesta["mensaje"] = "Error al crear la entrada. Inténtalo de nuevo.";
    }

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

    server.setOnConnectionCallback(
        [&server](std::shared_ptr<ix::WebSocket> webSocket,
                  std::shared_ptr<ix::ConnectionState> connectionState)
        {
            webSocket->setOnMessageCallback(
                [webSocket, connectionState, &server](const ix::WebSocketMessagePtr msg)
                {
                    if (msg->type == ix::WebSocketMessageType::Open)
                    {
                        std::cout << "New connection" << std::endl;

                    }
                    else if (msg->type == ix::WebSocketMessageType::Close)
                    {
                        std::cout << "Bye bye connection" << std::endl;
                    }
                    else if (msg->type == ix::WebSocketMessageType::Message)
                    {
                        if (!msg->binary)
                        {
                            /// Text format
                            std::cout << "Received message: " << msg->str << std::endl;
                        }


                        auto receivedObject = JSON::parse(msg->str);

                        if (receivedObject.is_discarded())
                        {
                            std::cout << "error" << std::endl;
                        }
                        else
                        {
                                ///JSON válido
                                if (exists(receivedObject, "tipo"))
                                {
                                    std::string tipo = receivedObject["tipo"];
                                    /*
                                    if (tipo=="login")
                                    {
                                        JSON respuesta = login(receivedObject);
                                        //gestionador->login(receivedObject["usuario"], receivedObject["contrasenya"]);
                                        webSocket->send(respuesta.dump());
                                    }
                                    */

                                    if (tipo=="crearEntrada")
                                    {
                                        JSON respuesta=crearEntrada(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }




                                    if (tipo=="registro")
                                    {
                                        JSON respuesta = registro(receivedObject);
                                        webSocket->send(respuesta.dump());
                                    }

    //http://erickveil.github.io/2016/04/06/How-To-Manipulate-JSON-With-C++-and-Qt.html

                                    if (tipo=="logout")
                                    {
                                        JSON respuesta = logout(receivedObject);
                                        //Usuario *nuevo_usuario;
                                        //nuevo_usuario->load()
                                        webSocket->send(respuesta.dump());
                                    }

                                }
                                else
                                {
                                    std::cout << "error no hay tipo" << std::endl;
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
