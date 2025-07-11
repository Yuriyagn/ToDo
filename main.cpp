#include "ToDo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ToDo window;
    window.show();
    return app.exec();
}
