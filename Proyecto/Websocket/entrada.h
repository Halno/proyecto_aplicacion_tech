#ifndef ENTRADA_H
#define ENTRADA_H

#include <QString>
#include <QSqlDatabase>
#include "json.hpp"

using JSON = nlohmann::json;

class Entrada
{
    int m_idEntrada;
    int m_idUsuarioEntrada;
    QString m_contenidoEntrada;
    QString m_personajeEntrada;

public:
    Entrada();
    Entrada(int idUsuarioEntrada, QString contenidoEntrada, QString personajeEntrada);

    void load(int id);
    static JSON cargarEntradas(QString personaje, JSON respuesta);

    bool insert();
    bool remove();
};

#endif // ENTRADA_H
