#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "json.hpp"
using JSON = nlohmann::json;

class Servidor
{


public:

    Servidor();

    int iniciarServidor();
    int autocalcularIdServidor();

    JSON login(JSON receivedObject);
    JSON logout(JSON receivedObject);
    JSON registro(JSON receivedObject);
    JSON consultarSeccion(JSON receivedObject);
    JSON crearEntrada(JSON receivedObject);

    bool exists(const JSON& json, const std::string& key);




};

#endif // SERVIDOR_H
