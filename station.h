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
    int id;                  
    QString name;             
    double X, Y; //站点XY
    QSet<int> linesInfo;        //Line
    static double minX, minY, maxX, maxY;// Boundary location of all sites
public:
    Station();    
    Station(QString nameStr, double x, double y, QList<int> linesList);
protected:
    int distance(Station other);

    friend class MetroGraph;
    friend class QTextStream;

};

#endif // STATION_H
