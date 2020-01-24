#include "conexionusuarios.h"
#include <QString>

ConexionUsuarios::ConexionUsuarios()
{
    // Esta clase se encarga de todo lo relacionado con conectar a diferentes usuarios
    // y gestionar las interacciones que ocurren en dicha conexión.

}

bool ConexionUsuarios::gestionCola()
{
    // Esta función se encarga de meter y sacar a los usuarios de
    // la cola de búsqueda.

    //Devolverá true si todo ha ido bien, y false si ha habido algún error.
}

void ConexionUsuarios::cola()
{
    // Se encontrará la programación requerida para el sistema de
    // cola.

    // En el momento en el que se realiza una conexión entre dos usuarios,
    // se llama a la función "emparejar".
}

bool ConexionUsuarios::emparejar()
{
    // Una vez conectados ambos jugadores en la cola, se les empareja y se inicia el chat.

    //Si todo ha ido bien, devuelve true.
    //Si se ha ocasionado algún error, devuelve false.
}

bool ConexionUsuarios::chat(QString mensaje)
{
    //Gestiona el chat entre los dos usuarios.

    //Devuelve true si uno de los dos usuarios cierra el chat de manera normal.
    //Devuelve false si la conexión se ha interrumpido de manera imprevista.

}
