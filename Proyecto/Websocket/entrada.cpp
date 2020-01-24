#include "entrada.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

Entrada::Entrada()
{

}

void Entrada::load(int id)
{
    QSqlQuery orden;
    orden.prepare("SELECT * FROM entrada WHERE id_entrada = :idEntrada LIMIT 1");
    orden.bindValue(":idEntrada", id);
    bool result {orden.exec()};

    if (result)
    {
        orden.next();
        m_idEntrada = orden.value("id_entrada").toInt();
        m_idSeccionEntrada = orden.value("id_seccion_entrada").toInt();
        m_idUsuarioEntrada = orden.value("id_usuario_entrada").toInt();
        m_contenidoEntrada = orden.value("contenido_entrada").toString();
    } // end if
}

bool Entrada::update()
{
    QSqlQuery q;

        /// UPDATE
        ///
        q.prepare("UPDATE entrada SET nombre_usuario = :nombreUsuario WHERE id_usuario = :idUsuario");
        q.bindValue(":idUsuario", m_idUsuarioEntrada);
        q.bindValue(":nombreUsuario", m_nombreUsuario);

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
