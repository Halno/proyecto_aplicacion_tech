#include "usuario.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

/**
 * Método constructor para la clase Usuario.
*/

Usuario::Usuario()
{

}

/**
 * Método constructor para la clase Usuario. Configura sus variables en función de los parámetros introducidos.
 * @param nombre Nombre del usuario.
 * @param password Contraseña del usuario.
*/

Usuario::Usuario(QString nombre, QString password)
{
    this->m_nombreUsuario=nombre;
    this->m_passwordUsuario=password;
}

/**
 * Se realiza una búsqueda de usuario en base a su ID.
 * Se cargan los datos del usuario encontrado en la base de datos en los parámetros del objeto.
*/

void Usuario::load(int id)
{
    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE id_usuario = :idUsuario LIMIT 1");
    orden.bindValue(":idUsuario", id);
    bool result {orden.exec()};

    if (result)
    {
        orden.next();
        m_idUsuario = orden.value("id_usuario").toInt();
        m_nombreUsuario = orden.value("nombre_usuario").toString();
        m_passwordUsuario = orden.value("password_usuario").toString();
        qDebug() << "load: " << m_nombreUsuario;
    } // end if
}

/**
 * Se realiza una búsqueda de usuario en base a su nombre.
 * Se cargan los datos del usuario encontrado en la base de datos en los parámetros del objeto.
*/

void Usuario::load(QString nombre)
{
    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE nombre_usuario = :nombreUsuario LIMIT 1");
    orden.bindValue(":nombreUsuario", nombre);
    bool result {orden.exec()};

    if (result)
    {
        orden.next();
        m_idUsuario = orden.value("id_usuario").toInt();
        m_nombreUsuario = orden.value("nombre_usuario").toString();
        m_passwordUsuario = orden.value("password_usuario").toString();
        qDebug() << "load: " << m_nombreUsuario;
    } // end if
}


/**
 * Actualiza la contraseña del usuario en la base de datos.
*/

bool Usuario::update()
{
    QSqlQuery q;

        q.prepare("UPDATE usuario SET password_usuario = :passwordUsuario WHERE id_usuario = :idUsuario");
        q.bindValue(":idUsuario", m_idUsuario);
        q.bindValue(":passwordUsuario", m_passwordUsuario);

        bool result {q.exec()};
        return result;
}

/**
 * Inserta al usuario en la base de datos.
*/

bool Usuario::insert()
{
    QSqlQuery q;

    q.prepare("INSERT INTO usuario (nombre_usuario, password_usuario) VALUES (:nombreUsuario, :passwordUsuario)");
    q.bindValue(":nombreUsuario", m_nombreUsuario);
    q.bindValue(":passwordUsuario", m_passwordUsuario);

    bool result {q.exec()};
    return result;
}

/**
 * Elimina al usuario de la base de datos, realizando la búsqueda por su ID.
*/

bool Usuario::remove()
{
    QSqlQuery q;
    bool result {false};

    if (m_idUsuario > 0)
    {
        q.prepare("DELETE FROM usuario WHERE id_usuario = :idUsuario");
        q.bindValue(":idUsuario", m_idUsuario);
        result = q.exec();
    } // end if

    return result;
}

/**
 * Comprueba la existencia del nombre de usuario en la base de datos.
 * Si existe, devuelve true. De lo contrario, devuelve false.
*/

bool Usuario::registro()
{
    bool result = false;
    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE nombre_usuario = :nombre_usuario LIMIT 1");
    orden.bindValue(":nombre_usuario", m_nombreUsuario);

    if (orden.exec())
    {
        if (orden.size() > 0) result = true;
    } // end if

    return result;
}

/**
 * Comprueba que el usuario en cuestión tiene la contraseña insertada por el usuario
 * Si la contraseña es correcta, devuelve true.
 * De lo contrario, devuelve false.
*/

bool Usuario::comprobarContrasenya()
{

    bool result = false;
    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE nombre_usuario = :nombreUsuario AND password_usuario = :passwordUsuario LIMIT 1");
    orden.bindValue(":nombreUsuario", m_nombreUsuario);
    orden.bindValue(":passwordUsuario", m_passwordUsuario);

    if (orden.exec())
    {
        if (orden.size() > 0) result = true;
    }

    return result;
}

/**
 * Esta función cambia el estado de inicio de sesión del usuario.
 * Si en la base de datos está en true lo cambia a false, y viceversa.
 * La función devuelve true si ha funcionado bien y false si se ha ocasionado algún error.
*/

bool Usuario::loginAndLogout()
{
    QSqlQuery orden;
    orden.prepare("UPDATE usuario SET sesion_iniciada = NOT sesion_iniciada WHERE nombre_usuario = :nombreUsuario");
    orden.bindValue(":nombreUsuario", m_nombreUsuario);
    if (orden.exec())
    {
        return true;
    }
    else
    {
        qDebug() <<orden.lastError().text();
        return false;
    } // end if
}

