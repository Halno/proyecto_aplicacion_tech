#ifndef TESTEO_H
#define TESTEO_H

#include "doctest.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>



class BaseDatos
{
    QSqlDatabase m_db;
public:
    BaseDatos();
    ~BaseDatos();
    bool iniciar();
    void cerrar();
    QSqlError ultimoError();
    bool insertar();
};


class Testeo : public QObject
{
   Q_OBJECT

   doctest::Context m_contexto;

public:
   Testeo(QObject *parent = nullptr);
   int autocalcularIdServidor();

public slots:

   void bucle();
};

#endif // TESTEO_H
