#include "robobrew.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    robobrew w;
    w.show();

    return app.exec();
}

