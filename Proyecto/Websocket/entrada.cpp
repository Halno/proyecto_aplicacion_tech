#include "entrada.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

/**
 * Método constructor de la clase Entrada.
*/

Entrada::Entrada()
{

}

/**
 * Método constructor de la clase Entrada. Los parámetros se usan para cambiar las variables del objeto.
 * @param id_usuario El ID del usuario que ha realizado la entrada.
 * @param contenido El contenido de la entrada.
 * @param personaje El personaje al que pertenece la entrada.
*/

Entrada::Entrada(int id_usuario, QString contenido, QString personaje)
{
    this->m_idUsuarioEntrada=id_usuario;
    this->m_contenidoEntrada=contenido;
    this->m_personajeEntrada=personaje;
}

/**
 * Realiza una búsqueda en la base de datos según el ID de la entrada.
 * Carga los datos de la entrada encontrada en el objeto.
 * @param id Es el ID de la entrada que se desea buscar.
*/

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
        m_idUsuarioEntrada = orden.value("id_usuario_entrada").toInt();
        m_contenidoEntrada = orden.value("contenido_entrada").toString();
        m_personajeEntrada = orden.value("personaje").toString();

    } // end if
}

/**
 * Busca todas las entradas de un personaje y las carga en un JSON.
 * @param personaje Personaje del que se quieren buscar las entradas.
 * @param respuesta JSON sobre el que se van a añadir todas las entradas. También es el JSON que devuelve la función tras cargar las entradas.
 */

JSON Entrada::cargarEntradas(QString personaje, JSON respuesta)
{

    QSqlQuery orden;
    orden.prepare("SELECT * FROM entrada WHERE personaje = :personaje");
    orden.bindValue(":personaje", personaje);
    bool result {orden.exec()};
    respuesta["numeroResultados"]=orden.size();

    if (result)
    {
        while (orden.next())
        {
            JSON entradaEncontrada;
            entradaEncontrada["contenido"] = orden.value("contenido_entrada").toString().toStdString();
            respuesta["lista"].push_back(entradaEncontrada);
        } //end while

    } //end if

    return respuesta;
}


/**
 * Inserta la entrada en la base de datos.
*/

bool Entrada::insert()
{
    QSqlQuery q;

    q.prepare("INSERT INTO entrada (id_usuario_entrada, contenido_entrada, personaje) VALUES (:idUsuario, :contenidoEntrada, :personaje)");
    q.bindValue(":idUsuario", m_idUsuarioEntrada);
    q.bindValue(":contenidoEntrada", m_contenidoEntrada);
    q.bindValue(":personaje", m_personajeEntrada);

    bool result {q.exec()};
    return result;
}


/**
 * Elimina la entrada de la base de datos.
*/

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
