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
bool g_logeado = false;

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

void Servidor::iniciarServidor()
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
                        //webSocket->send(msg->str, msg->binary);

                        auto receivedObject = JSON::parse(msg->str);
                        //std::cout << receivedObject["message"] << std::endl;
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
                                        Usuario *nuevo_usuario;
                                        JSON respuesta=nuevo_usuario->nuevaEntrada(receivedObject);
                                    }



                                    /*
                                    if (tipo=="registro")
                                    {
                                        JSON respuesta = registro(receivedObject);
                                        //gestionador->crearCuenta(receivedObject["usuario"], receivedObject["contrasenya"]);
                                        webSocket->send(respuesta.dump());
                                    }



                                    if (tipo=="logout")
                                    {
                                        JSON respuesta = logout(receivedObject);
                                        //gestionador->logout();
                                        webSocket->send(respuesta.dump());
                                    }
                                    */
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
