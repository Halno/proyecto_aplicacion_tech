#define DOCTEST_CONFIG_IMPLEMENT
#include <QCoreApplication>
#include "testeo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Testeo testeo;

    return a.exec();
}
