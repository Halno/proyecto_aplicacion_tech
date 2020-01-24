#ifndef SECCION_H
#define SECCION_H

#include <QSqlDatabase>
#include <QString>

class Seccion
{
private:
    int m_idSeccion;
    QString m_nombreSeccion;

public:
    Seccion();
    void load(int id);
    bool update();
    bool insert();
};

#endif // SECCION_H
