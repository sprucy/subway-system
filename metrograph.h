#ifndef METROGRAPH_H
#define METROGRAPH_H

#include "station.h"
#include "line.h"
#include <QString>
#include <QPoint>
#include <QVector>
#include <QHash>

//Neighbourhood structure of Graph
class Node{
public:
    int stationID;      //Neighbourhood ID
    double distance;    //Distance

    //Constructer
    Node(){}
    Node(int s, double dist) :stationID(s), distance(dist)
    {}

    bool operator > (const Node& n) const
    {
        return this->distance>n.distance;
    }
};

//Metro management category
class MetroGraph
{
protected:
    QVector<Station> stations; //store all stations
    QVector<Line> lines; //store all lines
    QHash<QString, int> stationsHash; //Station name to stored location hash
    QHash<QString, int> linesHash; //hash of line names to storage locations
    QSet<Edge> edges; //set of all edges
    QVector<QVector<Node>> graph; //metro line network graph

public:
    MetroGraph();

    //get line name
    QString getLineName(int l);
    //Get the line colour
    QColor getLineColor(int l); //Get the line hash value.
    //Get the line hash value
    int getLineHash(QString lineName); //Get the line hash value.
    //Get the line hash value
    QList<int> getLinesHash(QList<QString> linesList); //Get the lines collection hash value.
    //Get the set of line names
    QList<QString> getLinesNameList(); //Get the set of line names.
    //Get all contained stations of the line
    QList<QString> getLineStationsList(int l); //Get the set of line names.

    //Get station name
    QString getStationName(int s);
    //Get the geographic coordinates of the site
    QPointF getStationCoord(int s);
    //Get the minimum coordinates of the site
    QPointF getMinCoord();
    //Get the maximum coordinates of the site
    QPointF getMaxCoord();
    //Get information about the line the station belongs to
    QList<int> getStationLinesInfo(int s);
    //Get the publicly owned routes of the two stations
    QList<int> getCommonLines(int s1, int s2);
    //get site hash value
    int getStationHash(QString stationName);
    //Get the site collection hash value
    QList<QString> getStationsNameList();

    //Add new lines
    void addLine(QString lineName, QColor color);
    //Add new stations
    void addStation(Station s);
    //Add station connections
    void addConnection(int s1, int s2, int l);

    void getGraph(QList<int>&stationsList, QList<Edge>&edgesList);
    bool queryTransferMinTime(int s1, int s2,
                              QList<int>&stationsList,
                              QList<Edge>&edgesList);
    bool queryTransferMinTransfer(int s1, int s2,
                                  QList<int>&stationsList,
                                  QList<Edge>&edgesList);
    bool readFileData(QString fileName);

private:
    void clearData();
    bool insertEdge(int s1, int s2);
    void updateMinMaxXY();
    void makeGraph();
};

#endif // METROGRAPH_H
