#include "seccion.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

Seccion::Seccion()
{

}

void Seccion::load(int id)
{
    QSqlQuery orden;
    orden.prepare("SELECT * FROM seccion WHERE id_seccion = :idSeccion LIMIT 1");
    orden.bindValue(":idSeccion", id);
    bool result {orden.exec()};

    if (result)
    {
        orden.next();
        m_idSeccion = orden.value("id_seccion").toInt();
        m_nombreSeccion = orden.value("nombre_seccion").toString();

    } // end if
}

bool Seccion::update()
{
    QSqlQuery q;

        /// UPDATE
        q.prepare("UPDATE seccion SET nombre_seccion = :nombreSeccion WHERE id_seccion = :idSeccion");
        q.bindValue(":idSeccion", m_idSeccion);
        q.bindValue(":nombreSeccion", m_nombreSeccion);

        bool result {q.exec()};
        return result;
}

bool Seccion::insert()
{
    QSqlQuery q;

    /// INSERT
    q.prepare("INSERT INTO seccion (nombre_seccion) VALUES (:nombreSeccion)");
    q.bindValue(":nombreSeccion", m_nombreSeccion);

    bool result {q.exec()};
    return result;
}

