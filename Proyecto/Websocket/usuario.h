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
    bool update();
    bool insert();
    bool remove();


    bool registro();
    bool login(QString nombre, QString password);
    bool logout();
    bool nuevaEntrada(JSON receivedObject);
};

#endif // USUARIO_H
