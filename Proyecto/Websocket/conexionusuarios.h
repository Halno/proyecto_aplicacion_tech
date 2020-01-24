#ifndef CONEXIONUSUARIOS_H
#define CONEXIONUSUARIOS_H
#include <QString>


class ConexionUsuarios
{
public:
    ConexionUsuarios();
    bool gestionCola();
    void cola();
    bool emparejar();
    bool chat(QString);
};

#endif // CONEXIONUSUARIOS_H
