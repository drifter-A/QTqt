#include "mainwindow.h"
#include <QPixmap>
#include <QSplashScreen>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow f;
    f.setWindowTitle("贝塞尔曲线");//标题
    f.resize(1388,768);
    //f.resize(f.desktop()->availableGeometry().size());

    //f.showMaximized();;
    f.show();

    return a.exec();
}
