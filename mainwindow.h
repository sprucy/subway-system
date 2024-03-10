#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphics_view_zoom.h"
#include "metrograph.h"
#include "addstation.h"
#include "querytransfer.h"
#include "about.h"

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    //Action to close the programme slot function
    void on_actionClose_triggered();
    //Add line function function
    void appendLine();
    //Add site function function
    void appendStation();
    //Add connection function
    void appendConnection();
    // Interchange Enquiry
    void on_actionquery_triggered();
    //Add Stations
    void on_actionAdd_triggered();
    //About
    void on_actionAbout_triggered();

protected:
    Ui::MainWindow *ui; //Main window UI
    Graphics_view_zoom *myView; //Custom view for mouse zoom
    QGraphicsScene *scene; //scene
    About * about; //Custom view for mouse zoom
    AddStation * addStation; //Add line and station classes
    QueryTransfer* querytransfer; //query transfer line and station class


    //Calculation of mixing colours by line table
    QColor getLinesColor(const QList<int>& linesList);
    //Get the name set of the line table
    QString getLinesName(const QList<int>& linesList);
    // Convert XY geographic coordinates of the site to view coordinates
    QPointF transferCoord(QPointF coord);
    //Drawing the edges of the network diagram
    void drawEdges (const QList<Edge>& edgesList);
    //Mapping site nodes for network diagrams
    void drawStations (const QList<int>& stationsList);
    //Mapping of all lines
    void drawLineMap();

private:
    QLabel* statusLabel1, *statusLabel2, *statusLabel3;     // Three texts in the status bar
    //Connecting signals and slot functions
    void myConnect();

};

#define LINE_INFO_WIDTH 0   //Reserve borders for information display
#define MARGIN 30           //View Left Margin
#define NET_WIDTH 1000      //Maximum width of network diagram
#define NET_HEIGHT 1000     //Maximum height of network diagram
#define SCENE_WIDTH (LINE_INFO_WIDTH+MARGIN*2+NET_WIDTH)    //view width
#define SCENE_HEIGHT (MARGIN*2+NET_HEIGHT)                  //view height

#define EDGE_PEN_WIDTH 2    //Line edge width
#define NODE_HALF_WIDTH 3   //node size

#endif // MAINWINDOW_H
