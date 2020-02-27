#ifndef USUARIO_H
#define USUARIO_H

#include <QSqlDatabase>
#include <QString>
#include "json.hpp"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
using JSON = nlohmann::json;

class Usuario
{
private:


public:

    int m_idUsuario;
    QString m_nombreUsuario;
    QString m_passwordUsuario;


    Usuario();
    Usuario(QString nombre, QString password);

    void load(int id);
    void load(QString nombre);

    bool update();
    bool insert();
    bool remove();
    bool comprobarContrasenya();

    bool registro();
    bool loginAndLogout();
    bool nuevaEntrada(JSON jsonRecibido);
};

#endif // USUARIO_H
