#ifndef ARCHIVOCONFIGURACION_H
#define ARCHIVOCONFIGURACION_H

#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <map>

class ArchivoConfiguracion
{

public:
    ArchivoConfiguracion();
    QSqlDatabase abrir();
    void cerrar();

private:
    QSqlDatabase m_db;

    QString m_hostName;
    QString m_baseDeDatos;
    QString m_usuario;
    QString m_contrasenya;

     std::map<std::string, std::string> m_propiedades;

    int m_puerto;


    void cargarPropiedades();
    void leerArchivo();
    void procesarLinea(std::string linea);

};

#endif // ARCHIVOCONFIGURACION_H
