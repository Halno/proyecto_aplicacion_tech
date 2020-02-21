#include "testeo.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QSqlQuery>
#include "../../Proyecto/Websocket/usuario.h"
#include "../../Proyecto/Websocket/usuario.cpp"
#include "../../Proyecto/Websocket/servidor.h"

int g_idMensaje = 0;

Testeo::Testeo(QObject *parent) : QObject(parent)
{
    QTimer::singleShot(0, this, SLOT(run()));
}


void Testeo::run()
{
    qDebug() << "Iniciando...";

    m_contexto.run(); // run
    if (m_contexto.shouldExit())
    {
        QCoreApplication::quit();
    } // end if

}

BaseDatos::~BaseDatos()
{
    if (m_db.isOpen())
    {
        m_db.close();
    } // end if
}

bool BaseDatos::insertar(QString nombre, QString pass)
{

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO usuarios (nombre_usuario, password_usuario) VALUES (:nombre_Usuario, :passwordUsuario)");
    query.bindValue(":nombre_Usuario", nombre);
    query.bindValue(":passwordUsuario", pass);

    bool result = query.exec();
    qDebug() << query.lastError().text();
    return result;

}

BaseDatos::BaseDatos()
{
    if (!QSqlDatabase::contains("MyDb"))
    {
        m_db = QSqlDatabase::addDatabase("QPSQL", "MyDb");
    }
    else
    {
        m_db = QSqlDatabase::database("MyDb");
    }
    m_db.setHostName("localhost");
    m_db.setPort(5432);
    m_db.setUserName("postgres");
    m_db.setPassword("");
}

void BaseDatos::cerrar()
{
    m_db.close();
}

bool BaseDatos::iniciar()
{
    bool result = 0;

    m_db.close();
    m_db.setDatabaseName("template1");

    bool ok = m_db.open();

    if (ok)
    {

        qDebug() << "Borrando...";
        QSqlQuery q0("DROP DATABASE IF EXISTS tests_tech", m_db);
        if (q0.lastError().type() == QSqlError::NoError)
        {
            qDebug() << "Creando...";
            QSqlQuery q1("CREATE DATABASE tests_tech", m_db);
            if (q1.lastError().type() == QSqlError::NoError)
            {
                m_db.close();
                m_db.setDatabaseName("tests_tech");
                m_db.open();

                /// Crea estructura en la base de datos
                QString sql {"CREATE TABLE usuarios ( \
                    id_usuario     SERIAL, \
                    nombre_usuario    varchar(20), \
                    password_usuario    varchar(30), \
                    PRIMARY KEY(id_usuario) \
                )"};



                qDebug() << "Iniciando...";
                QSqlQuery q2(sql, m_db);
                if (q2.lastError().type() == QSqlError::NoError)
                {
                    result = true;
                } // end if
            }
            else
            {
                qDebug() << "BB:" << m_db.lastError().text();
            } // end if

        }
        else
        {
            qDebug() << "AA:" << m_db.lastError().text();
        } // end if

    } // end if


    return result;
}

QSqlError BaseDatos::ultimoError()
{
    return m_db.lastError();
}

int autocalcularIdServidor()
{
    g_idMensaje++;
    return g_idMensaje;
}

bool exists(const JSON& json, const std::string& key)
{
    return json.find(key) != json.end();
}


TEST_CASE("Test autocalcularIdServidor()")
{
    CHECK(autocalcularIdServidor());
}

TEST_CASE("Test clase Usuario")
{
    BaseDatos db;
    int ok = db.iniciar();

    if (ok)
    {
        QString nombre, contrasenya;
        nombre="NombreDeEjemplo";
        contrasenya="PasswordDeEjemplo";

        Usuario user(nombre, contrasenya);

        CHECK( user.m_nombreUsuario == "NombreDeEjemplo" );
        CHECK( user.m_passwordUsuario == "PasswordDeEjemplo");
        qDebug () << user.m_nombreUsuario;
        qDebug () << user.m_passwordUsuario;

        SUBCASE("Insertar usuario")
        {
            CHECK(db.insertar(user.m_nombreUsuario, user.m_passwordUsuario) == true);
        }

    }
    else
    {
        qDebug() << db.ultimoError().text();
    }

     db.cerrar();
}

TEST_CASE("Funcion exists()")
{
    JSON jsonDeEjemplo;
    jsonDeEjemplo["parametroDeEjemplo"] = 3;
    CHECK( exists(jsonDeEjemplo, "parametroDeEjemplo") == true);
}
