#include "constant.hpp"
#include "gamemainclass.h"
#include <QApplication>
#include "resources.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    g_Resources = new Resources();
    GameMainClass w;
    return a.exec();
    delete g_Resources;
}
