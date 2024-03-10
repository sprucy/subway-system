#ifndef LINE_H
#define LINE_H

#include <QString>
#include <QColor>
#include <QPair>
#include <QSet>
#include <QVector>

// Define the edge type
typedef QPair<int,int> Edge;

Class MetroGraph;
class QTextStream;

// line class
class Line{
class
    int id; //line ID
    QString name; //line name
    QColor color; //Line colour
    QVector <QString> fromTo; //line start station
    QSet<int> stationsSet; //line stations set
    QSet<Edge> edges; //Line station connection relationship

public:
    //constructor
    Line(){}
    Line(QString lineName, QColor lineColor):name(lineName), colour(lineColor)
    {}

    // Declare friends
    friend class MetroGraph;
    friend class QTextStream;
};

#endif // LINE_H
