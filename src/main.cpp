#include "kournable.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    kournable w;
    w.show();

    return app.exec();
}

