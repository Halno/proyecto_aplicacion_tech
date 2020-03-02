#ifndef TESTEO_H
#define TESTEO_H

#include "doctest.h"
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>



class BaseDatos
{

public:
    BaseDatos();
    ~BaseDatos();

    QSqlDatabase m_db;

    bool iniciar();
    void cerrar();
    QSqlError ultimoError();
    bool insertar(QString nombre, QString pass);
};


class Testeo : public QObject
{
   Q_OBJECT

   doctest::Context m_contexto;

public:
   Testeo(QObject *parent = nullptr);
   int autocalcularIdServidor();

public slots:

   void run();
};

#endif // TESTEO_H
