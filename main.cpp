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
    QSplashScreen splash(pixmap); //Display startup screen
    for(qint64 i=0;i<5000000;i++)
      splash.show();
    bool flag = metroGraph->readFileData(":/data/data/metroLine.txt");
    if (!flag)
    {
        QMessageBox box;
        box.setWindowTitle(u8"Error");
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"Error reading data! \n Will not be able to display metro lines!");
        box.addButton(u8"Confirm", QMessageBox::AcceptRole);
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
