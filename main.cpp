#include "mainwindow.h"
#include "global.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QMessageBox>


MetroGraph *metroGraph=new MetroGraph();

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    QPixmap pixmap(":/icon/icon/splash.png");
    QSplashScreen splash(pixmap);//显示启动画面
    for(qint64 i=0;i<5000000;i++)
      splash.show();
    bool flag = metroGraph->readFileData(":/data/data/metroLine.txt");
    if (!flag)
    {
        QMessageBox box;
        box.setWindowTitle(u8"错误");
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"读取数据错误!\n将无法展示地铁线路！");
        box.addButton(u8"确定", QMessageBox::AcceptRole);
        if (box.exec() == QMessageBox::Accepted)
        {
            box.close();
        }
    }
    MainWindow w;
    w.show();

    splash.finish(&w);

    return a.exec();
}
