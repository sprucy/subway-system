#include "station.h"
#include <math.h>

// Calculate the approximate straight-line distance between two points
int calcuDistance(double x1, double y1, double x2, double y2){
    double s = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return int(s);
}
double Station::minX = 200;
double Station::minY = 200;
double Station::maxX = 0;
double Station::maxY = 0;

Station::Station(){
}

Station::Station(QString nameStr, double x, double y, QList<int> linesList):
    name(nameStr), X(x), Y(y){
    linesInfo=linesList.toSet();
}

int Station::distance(Station other){
    return calcuDistance(X, Y, other.X, other.Y);
}
