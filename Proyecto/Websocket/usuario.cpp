#include "usuario.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

Usuario::Usuario()
{

}

Usuario::Usuario(QString nombre, QString password)
{
    this->m_nombreUsuario=nombre;
    this->m_passwordUsuario=password;
}

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

bool Usuario::find(QString nombre)
{
    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE nombre_usuario = :nombreUsuario LIMIT 1");
    orden.bindValue(":nombreUsuario", nombre);
    bool result {orden.exec()};

    if (result)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Usuario::update()
{
    QSqlQuery q;

        /// UPDATE
        q.prepare("UPDATE usuario SET password_usuario = :passwordUsuario WHERE id_usuario = :idUsuario");
        q.bindValue(":idUsuario", m_idUsuario);
        q.bindValue(":passwordUsuario", m_passwordUsuario);

        bool result {q.exec()};
        return result;
}

bool Usuario::insert()
{
    QSqlQuery q;

    /// INSERT
    q.prepare("INSERT INTO usuario (nombre_usuario, password_usuario) VALUES (:nombreUsuario, :passwordUsuario)");
    q.bindValue(":nombreUsuario", m_nombreUsuario);
    q.bindValue(":passwordUsuario", m_passwordUsuario);

    bool result {q.exec()};
    return result;
}

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

bool Usuario::registro()
{
    //Se llama a esta función cuando un usuario intenta registrarse.
    //1. La función comprueba que el nombre de usuario no se encuentre en uso.

    //2. Si se encuentra en uso, se le notifica al usuario
    //   para que introduzca otro. (Devuelve false).

    //3. De lo contrario, se crea la entrada en la BD con el usuario
    //   y la contraseña codificada. (Devuelve true). -> Se llama a la función insert().

}

bool Usuario::login()
{

    QSqlQuery orden;
    orden.prepare("SELECT * FROM usuario WHERE nombre_usuario = :nombreUsuario AND password_usuario = :passwordUsuario LIMIT 1");
    orden.bindValue(":nombreUsuario", m_nombreUsuario);
    orden.bindValue(":passwordUsuario", m_passwordUsuario);
    bool result {orden.exec()};

    if (result)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Usuario::logout()
{
    //Se llama a esta función cuando un usuario intenta cerrar sesión.

    //1. La función comprueba que el usuario, efectivamente, está logeado.

    //2. Si no lo está, se le indica que no puede cerrar sesión si previamente
    //   no la ha iniciado. (Devuelve false).

    //3. Si se encontraba logeado, el usuario cierra sesión. (Devuelve true).
}

/*
bool Usuario::nuevaEntrada()
{

    //Crea una entrada en la sección indicada.
}
*/
