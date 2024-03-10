#include "station.h"
#include <math.h>

// 计算两个点之间的大致直线距离
int calcuDistance(double x1, double y1, double x2, double y2){
    double s = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return int(s);
}
double Station::minX = 200;
double Station::minY = 200;
double Station::maxX = 0;
double Station::maxY = 0;

//构造函数
Station::Station(){
}

//构造函数
Station::Station(QString nameStr, double x, double y, QList<int> linesList):
    name(nameStr), X(x), Y(y){
    linesInfo=linesList.toSet();
}

//求取站点间实地直线距离
int Station::distance(Station other){
    return calcuDistance(X, Y, other.X, other.Y);
}
