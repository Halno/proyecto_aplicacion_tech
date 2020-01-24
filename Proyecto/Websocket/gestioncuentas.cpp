#include "gestioncuentas.h"
#include <QString>

GestionCuentas::GestionCuentas()
{
    // Esta clase se encarga de controlar las cuentas de los usuarios.
    // Esto incluye crearlas, logearse y cerrar sesión.
}

bool GestionCuentas::crearCuenta(QString usuario, QString password)
{
    //Se llama a esta función cuando un usuario intenta registrarse.
    //1. La función comprueba que el nombre de usuario no se encuentre en uso.

    //2. Si se encuentra en uso, se le notifica al usuario
    //   para que introduzca otro. (Devuelve false).

    //3. De lo contrario, se crea la entrada en la BD con el usuario
    //   y la contraseña codificada. (Devuelve true).

}

bool GestionCuentas::login(QString usuario, QString password)
{
    //Se llama a esta función cuando un usuario intenta iniciar sesión.

    //1. La función comprueba que el usuario y la contraseña coincidan en la BD.

    //2. Si no coinciden con la BD, se le notifica al usuario para que vuelva a escribir sus
    //   datos de inicio de sesión. (Devuelve false).

    //3. Si coinciden, el usuario inicia sesión. (Devuelve true).
}

bool GestionCuentas::logout()
{
    //Se llama a esta función cuando un usuario intenta cerrar sesión.

    //1. La función comprueba que el usuario, efectivamente, está logeado.

    //2. Si no lo está, se le indica que no puede cerrar sesión si previamente
    //   no la ha iniciado. (Devuelve false).

    //3. Si se encontraba logeado, el usuario cierra sesión. (Devuelve true).
}

