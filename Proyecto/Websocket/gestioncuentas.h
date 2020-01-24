#ifndef GESTIONCUENTAS_H
#define GESTIONCUENTAS_H
#include <QString>


class GestionCuentas
{
public:
    GestionCuentas();
    bool crearCuenta(QString usuario, QString password);
    bool login(QString usuario, QString password);
    bool logout();
};

#endif // GESTIONCUENTAS_H
