#ifndef ENTRADA_H
#define ENTRADA_H

#include <QString>
#include <QSqlDatabase>

class Entrada
{
    int m_idEntrada;
    int m_idSeccionEntrada;
    int m_idUsuarioEntrada;
    QString m_contenidoEntrada;

public:
    Entrada();
    void load(int id);
    bool update();
    bool insert();
    bool remove();
};

#endif // ENTRADA_H
