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

    //动作关闭程序槽函数
    void on_actionClose_triggered();
    //添加线路功能函数
    void appendLine();
    //添加站点功能函数
    void appendStation();
    //添加连接功能函数
    void appendConnection();
    //换乘查询
    void on_actionquery_triggered();
    //站点增加
    void on_actionAdd_triggered();
    //关于
    void on_actionAbout_triggered();

protected:
    Ui::MainWindow *ui;             //主窗口UI
    Graphics_view_zoom *myView;     //自定义视图，用于鼠标缩放
    QGraphicsScene *scene;          //场景
    About * about;
    AddStation * addStation;       //增加线路和站点类
    QueryTransfer* querytransfer;       //查询换乘线路和站点类


    //由线路表计算混合颜色
    QColor getLinesColor(const QList<int>& linesList);
    //获得线路表的名字集
    QString getLinesName(const QList<int>& linesList);
    //将站点的XY地理坐标转为视图坐标
    QPointF transferCoord(QPointF coord);
    //绘制网络图的边
    void drawEdges (const QList<Edge>& edgesList);
    //绘制网络图的站点节点
    void drawStations (const QList<int>& stationsList);
    //绘制所有线路图
    void drawLineMap();

private:
    QLabel* statusLabel1, *statusLabel2, *statusLabel3;     //状态栏三个文本
    //连接信号和槽函数
    void myConnect();

};

#define LINE_INFO_WIDTH 0   //预留边框用于信息展示
#define MARGIN 30           //视图左边距
#define NET_WIDTH 1000      //网络图最大宽度
#define NET_HEIGHT 1000     //网络图最大高度
#define SCENE_WIDTH (LINE_INFO_WIDTH+MARGIN*2+NET_WIDTH)    //视图宽度
#define SCENE_HEIGHT (MARGIN*2+NET_HEIGHT)                  //视图高度

#define EDGE_PEN_WIDTH 2    //线路边宽
#define NODE_HALF_WIDTH 3   //节点大小

#endif // MAINWINDOW_H
