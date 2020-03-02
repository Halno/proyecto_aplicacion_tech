#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "json.hpp"
#include <QSqlDatabase>
using JSON = nlohmann::json;

class Servidor
{


public:

    Servidor();

    QSqlDatabase getDatabase();

    int iniciarServidor();
    int autocalcularIdServidor();

    JSON login(JSON jsonRecibido);
    JSON logout(JSON jsonRecibido);
    JSON registro(JSON jsonRecibido);
    JSON consultarSeccion(JSON jsonRecibido);
    JSON crearEntrada(JSON jsonRecibido);

    bool exists(const JSON& json, const std::string& key);




};

#endif // SERVIDOR_H
