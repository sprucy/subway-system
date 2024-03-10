#ifndef STATION_H
#define STATION_H

#include <QString>
#include <QPointF>
#include <QSet>

class MetroGraph;
class QTextStream;

//地铁站点类定义
class Station
{
protected:
    int id;                     //站点ID
    QString name;               //站点名称
    double X, Y; //站点XY
    QSet<int> linesInfo;        //站点所属线路
    static double minX, minY, maxX, maxY;//所有站点的边界位置
public:
    Station();    //构造函数
    Station(QString nameStr, double x, double y, QList<int> linesList);
protected:
    //求取站点间实地直线距离
    int distance(Station other);

    //声明友元
    friend class MetroGraph;
    friend class QTextStream;

};

#endif // STATION_H
