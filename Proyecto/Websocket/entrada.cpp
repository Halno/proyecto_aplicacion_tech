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



bool Entrada::insert()
{
    QSqlQuery q;

    /// INSERT
    q.prepare("INSERT INTO entrada (id_seccion_entrada, id_usuario_entrada, contenido_entrada) VALUES (:idSeccion, :idUsuario, :contenidoEntrada)");
    q.bindValue(":idSeccion", m_idSeccionEntrada);
    q.bindValue(":idUsuario", m_idUsuarioEntrada);
    q.bindValue(":contenidoEntrada", m_contenidoEntrada);

    bool result {q.exec()};
    return result;
}

bool Entrada::remove()
{
    QSqlQuery q;
    bool result {false};

    if (m_idEntrada > 0)
    {
        q.prepare("DELETE FROM entrada WHERE id_entrada = :idEntrada");
        q.bindValue(":idEntrada", m_idEntrada);
        result = q.exec();
    } // end if

    return result;
}
