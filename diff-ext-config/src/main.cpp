#include <QApplication>
#include "diff-ext-config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DiffExtConfig configWindow;
    configWindow.setWindowTitle(QObject::tr("kdiff-ext Configuration"));
    configWindow.show();

    return app.exec();
}
