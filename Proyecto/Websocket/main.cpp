#include <QCoreApplication>
#include "json.hpp"
#include <iostream>
#include "../../IXWebSocket/ixwebsocket/IXWebSocketServer.h"
#include "../../IXWebSocket/ixwebsocket/IXWebSocket.h"
#include "../../IXWebSocket/ixwebsocket/IXConnectionState.h"
#include "usuario.h"
#include "conexionusuarios.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
using JSON = nlohmann::json;


///TAREAS:
/// 1. CREAR LA BD CON LAS TABLAS Y CAMPOS PERTINENTES:   X
///     USUARIOS: ID, NOMBRE, CONTRASEÑA CIFRADA DE ALGUNA MANERA.
///     ENTRADAS: ID, ID_SECCION, ID_USUARIO, CONTENIDO.
///     SECCIÓN: ID, NOMBRE.
/// 2. CREAR LAS CLASES EN QT QUE SE CORRESPONDAN CON LA BD (PROPIEDADES = CAMPOS).   X
/// 3. CREAR LA PROGRAMACIÓN PARA PODER EMPLEAR LA BD DESDE EL SERVIDOR.
/// 4. CREAR EL DISEÑO TANTO DEL CLIENTE COMO DEL BACKEND.
/// 5. CREAR LA PROGRAMACIÓN PARA COMUNICAR EL CLIENTE Y EL SERVIDOR.
/// 6. CREAR LA PROGRAMACIÓN PARA COMUNICAR EL BACKEND Y EL SERVIDOR.
/// 7. DOCUMENTAR EL PROYECTO (DOXYGEN).
/// * EL PROGRAMA DEBE TENER SOPORTE PARA TRADUCCIONES (NO SIGNIFICA QUE ESTÉ TRADUCIDO,
/// SINO QUE SE PUEDA TRADUCIR, QUE EL PROGRAMA ESTÉ PREPARADO PARA ELLO.).
/// * EL PROGRAMA DEBERÍA ESTAR CREADO DE MANERA MODULAR (ESTE MAIN QUEDARÁ CASI VACÍO,
/// HAY QUE CREAR LA CLASE "SERVIDOR" APARTE Y DEJAR LA PROGRAMACIÓN AHÍ).
/// *TRAS ACABAR, REVISAR TEMA DE REFACTORIZACIÓN; DEJAR BIEN EL CÓDIGO (VARIABLES GLOBALES,
/// DE MÓDULO, NÚMEROS MÁGICOS, CÓDIGO REDUNDANTE, CÓDIGO INEFICIENTE).
///
/// TAREAS CASA:
/// ADAPTAR LAS CLASES AL MODELO PARA QUE TENGAN UPDATE, INSERT...
/// DISEÑOS BACKEND Y CLIENTE
///
///
///
/// LOGIN:
///
/// FORMULARIO: USUARIO CONTRASEÑA -> SERVIDOR
/// USUARIO EXISTE?
/// SI EXISTE, CUÁL ES SU SALT? EL CÓDIGO DE LA PASSWORD
/// CODIFICA LA CONTRASEÑA CON LA SALT, TEXTO PLANO DE LA CONTRASEÑA + SALT PARA OBTENER LA PASSWORD CIFRADA
/// CONTRASEÑA + SALT = CONTRASEÑA CIFRADA EN LA BBDD?
/// SI ES IGUAL, ENTONCES...
/// TABLA EN OTRO SITIO DE TOKENS VÁLIDOS Y ASIGNAS EL ID_USUARIO + EL TOKEN + FECHA DE CADUCIDAD
/// ESTA TOKEN DURA X, QUE ES LO QUE TE PERMITIRÁ ENTRAR
/// TABLA DE TOKENS:
/// ID_USER, TOKEN, FECHA VALIDEZ
/// ENVIAR TOKEN AL USUARIO, A PARTIR DE AHORA ESE USUARIO PUEDE HACER FUNCIONES DE USUARIO VALIDADO
/// LAS FUNCIONES LO PRIMERO QUE HARÁN SERÁ VER SI EL TOKEN ES VÁLIDO (LA FECHA TAMBIÉN DEBE SER VÁLIDA)
/// SI ES ASÍ, EJECUTO LA FUNCIÓN
/// SI NO, DEVUELVE UN ERROR.
///
/// CON WEBSOCKET NO HACE FALTA HACER TODO, ESTO ES MÁS HTTP.
/// CON WEBSOCKET SE PUEDE GENERAR EL TOKEN PERO NO HACE FALTA QUE EL TOKEN SE MUEVA CADA VEZ QUE HACES ALGO
/// TIENES EL ID CONEXION DEL WEBSOCKET Y EL ID USUARIO
/// CREAS QHASH DE USUARIOS LOGEADOS CON IDENTIFICADOR DE CONEXION E ID USUARIO. (QHash <int, int>)
/// SE PUEDE SIMPLIFICAR... EN ESTE CASO. PRIMERO HACER SIN NADA DE ESTO
///
/// END_LOGIN

int g_idMensaje = 0;
bool logeado = false;

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
        QString str = QString::fromUtf8(nombre.c_str());
        Usuario u();
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


///Para probar, emplear la función "mensajeChat()" desde el navegador. Por defecto
/// se envía "mensaje".
/*
JSON mensajeChat(JSON receivedObject)
{
    JSON respuesta;

    respuesta["idServidor"] = autocalcularIdServidor();
    respuesta["idCliente"] = receivedObject["id"];
    respuesta["mensaje"]= receivedObject["chat"];


    return respuesta;
}
*/
int main(int argc, char *argv[])
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
                                        Usuario *nuevo_usuario;
                                        JSON respuesta=crearEntrada(receivedObject);
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
                                        Usuario *nuevo_usuario;
                                        nuevo_usuario->load()
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
