#include "archivoconfiguracion.h"
#include <iostream>
#include <QFile>
#include <QIODevice>
#include <QDebug>
#include <QString>
#include <QSqlError>


/**
 * Método constructor de la clase ArchivoConfiguracion.
 */
ArchivoConfiguracion::ArchivoConfiguracion()
{

}

/**
 * Procesa la línea del archivo de configuración y la guarda en el mapa de strings como propiedad.
 */

void ArchivoConfiguracion::procesarLinea(std::string linea)
{

    std::string nuevaLinea = linea.substr(0, linea.rfind("\n"));

    std::string elemento = nuevaLinea.substr(0, nuevaLinea.rfind("="));
    std::string valor = nuevaLinea.substr(nuevaLinea.rfind("=") + 1, nuevaLinea.size());

    m_propiedades[elemento] = valor;

}

/**
 * Busca el archivo, y una vez encontrado se crea un bucle para coger todas las propiedades del
 * archivo.
 */

void ArchivoConfiguracion::leerArchivo()
{

    QString nombreArchivo = "tech.conf";

    if(QFile::exists(nombreArchivo) ){

        QFile file(nombreArchivo);


        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!file.atEnd())
            {
                std::string linea = QString(file.readLine()).toUtf8().constData();
                procesarLinea(linea);

            }
        } // end if

    }
    else
    {
        qDebug() << "Archivo no encontrado: " + nombreArchivo;
        exit(0);
    } // end if

}

/**
 * Carga toda la información del archivo de configuración en las propiedades de la clase.
 */

void ArchivoConfiguracion::cargarPropiedades()
{

    leerArchivo();

    m_hostName = QString::fromUtf8(m_propiedades["hostname"].c_str());
    m_baseDeDatos = QString::fromUtf8(m_propiedades["databaseName"].c_str());
    m_puerto = std::stoi(m_propiedades["port"]);
    m_usuario = QString::fromUtf8(m_propiedades["username"].c_str());;
    m_contrasenya = QString::fromUtf8(m_propiedades["password"].c_str());;

}

/**
 * Genera la conexión cogiendo los datos del archivo de configuración.
 */


QSqlDatabase ArchivoConfiguracion::abrir()
{

    // 1) Cargar propiedades
    cargarPropiedades();
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName(m_hostName);
    m_db.setDatabaseName(m_baseDeDatos);
    m_db.setPort(5432);
    m_db.setUserName(m_usuario);
    m_db.setPassword(m_contrasenya);


    // 2) Abrir conexión
    bool ok = m_db.open();
    if (!ok)
    {
         qDebug() << QObject::tr("Error al intentar iniciar la base de datos");
         qDebug() << m_db.lastError().text();
    }

    return m_db;

}

void ArchivoConfiguracion::cerrar()
{

    m_db.close();

}
