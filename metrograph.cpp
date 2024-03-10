#include "metrograph.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <queue>


MetroGraph::MetroGraph()
{

}

bool MetroGraph::readFileData(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QTextStream in(&file);
    while(!in.atEnd())
    {
        Line line;
        QString id, name, colour, fromTo, totalStations;
        QString color, froms, tos;
        bool ok;
        int total;
        Station station;
        int lvIndex, svIndex1, svIndex2;

        in>>id>>line.id;
        in>>name>>line.name;
        in>>colour>>color;
        line.color.setRgba(color.remove(0,1).toUInt(&ok, 16));
        in>>fromTo>>froms>>tos;
        in>>totalStations>>total;

        line.fromTo.push_back(froms);
        line.fromTo.push_back(tos);
        if (linesHash.count(line.name))
        {
            lvIndex = linesHash[line.name];
            lines[lvIndex].fromTo.push_back(froms);
            lines[lvIndex].fromTo.push_back(tos);
        }
        else
        {
            lvIndex = linesHash[line.name] = lines.size();
            lines.push_back(line);
        }

        QString longlat;
        QStringList strList;
        for (int i=0; !in.atEnd()&&i<total; ++i)
        {
            in>>station.id>>station.name>>longlat;
            strList=longlat.split(QChar(','));
            station.X=strList.first().toDouble();
            station.Y=strList.last().toDouble();

            if (stationsHash.count(station.name))
            {
                svIndex2 = stationsHash[station.name];
            }
            else
            {
                svIndex2 = stationsHash[station.name] = stations.size();
                stations.push_back(station);
            }

            stations[svIndex2].linesInfo.insert(lvIndex);
            lines[lvIndex].stationsSet.insert(svIndex2);

            if (i)
            {
                lines[lvIndex].edges.insert(Edge(svIndex1, svIndex2));
                lines[lvIndex].edges.insert(Edge(svIndex2, svIndex1));
                insertEdge(svIndex1, svIndex2);
            }
            svIndex1 = svIndex2;
        }

        bool flag = id=="id:" && name=="name:" && colour=="colour:" && fromTo=="fromTo:"
                && totalStations=="totalStations:" && ok && !in.atEnd();

        if(flag==false)
        {
            file.close();
            clearData();
            return false ;
        }
        in.readLine();
    }
    file.close();

    updateMinMaxXY();

    return true;
}

void MetroGraph::clearData()
{
    stations.clear();
    lines.clear();
    stationsHash.clear();
    linesHash.clear();
    edges.clear();
    graph.clear();
}

bool MetroGraph::insertEdge(int n1, int n2)
{
    if (edges.contains(Edge(n1, n2)) || edges.contains(Edge(n2, n1)))
    {
        return false;
    }
    edges.insert(Edge(n1, n2));
    return true;
}

void MetroGraph::makeGraph()
{
    graph.clear();
    graph=QVector<QVector<Node>>(stations.size(), QVector<Node>());
    for (auto &a : edges)
    {
        double dist=stations[a.first].distance(stations[a.second]);
        graph[a.first].push_back(Node(a.second, dist));
        graph[a.second].push_back(Node(a.first, dist));
    }
}


QColor MetroGraph::getLineColor(int l)
{
    return lines[l].color;
}

QString MetroGraph::getLineName(int l)
{
    return lines[l].name;
}


int MetroGraph::getLineHash(QString lineName)
{
    if(linesHash.contains(lineName))
    {
        return linesHash[lineName];
    }
    return -1;
}


QList<int> MetroGraph::getLinesHash(QList<QString> linesList)
{
    QList<int> hashList;
    for (auto &a:linesList)
    {
        hashList.push_back(getLineHash(a));
    }
    return hashList;
}


QList<QString> MetroGraph::getLinesNameList()
{
    QList<QString> linesNameList;
    for (auto a:lines)
    {
        linesNameList.push_back(a.name);
    }
    return linesNameList;
}

QList<QString> MetroGraph::getLineStationsList(int l)
{
    QList<QString> stationsList;
    for (auto &a:lines[l].stationsSet)
    {
        stationsList.push_back(stations[a].name);
    }
    return stationsList;
}



void MetroGraph::updateMinMaxXY()
{
    double minX=200, minY=200;
    double maxX=0, maxY=0;

    for (auto &s : stations)
    {
        minX = qMin(minX, s.X);
        minY = qMin(minY, s.Y);
        maxX = qMax(maxX, s.X);
        maxY = qMax(maxY, s.Y);
    }
    Station::minX = minX;
    Station::minY = minY;
    Station::maxX = maxX;
    Station::maxY = maxY;


}

QPointF MetroGraph::getMinCoord()
{
    return QPointF(Station::minX, Station::minY);
}

QPointF MetroGraph::getMaxCoord()
{
    return QPointF(Station::maxX, Station::maxY);
}

QList<int> MetroGraph::getCommonLines(int s1, int s2)
{
    QList<int> linesList;
    for (auto &s : stations[s1].linesInfo)
    {
        if(stations[s2].linesInfo.contains(s))
            linesList.push_back(s);
    }
    return linesList;
}

QString MetroGraph::getStationName(int s)
{
    return stations[s].name;
}

QPointF MetroGraph::getStationCoord(int s)
{
    return QPointF(stations[s].X, stations[s].Y);
}

QList<int> MetroGraph::getStationLinesInfo(int s)
{
    return stations[s].linesInfo.toList();
}

int MetroGraph::getStationHash(QString stationName)
{
    if(stationsHash.contains(stationName))
    {
        return stationsHash[stationName];
    }
    return -1;
}

QList<QString> MetroGraph::getStationsNameList()
{
    QList<QString> list;
    for (auto &a: stations)
    {
        list.push_back(a.name);
    }
    return list;
}




void MetroGraph::addLine(QString lineName, QColor color)
{
    linesHash[lineName]=lines.size();
    lines.push_back(Line(lineName,color));
}

void MetroGraph::addStation(Station s)
{
    int hash=stations.size();
    stationsHash[s.name]=hash;
    stations.push_back(s);
    for (auto &a: s.linesInfo)
    {
        lines[a].stationsSet.insert(hash);
    }
    updateMinMaxXY();
}


void MetroGraph::addConnection(int s1, int s2, int l)
{
    insertEdge(s1,s2);
    lines[l].edges.insert(Edge(s1,s2));
    lines[l].edges.insert(Edge(s2,s1));
}



void MetroGraph::getGraph(QList<int>&stationsList, QList<Edge>&edgesList)
{
    stationsList.clear();
    for (int i=0; i<stations.size(); ++i)
    {
        stationsList.push_back(i);
    }
    edgesList=edges.toList();
    return ;
}


bool MetroGraph::queryTransferMinTime(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList)
{
#define INF 999999999
    stationsList.clear();
    edgesList.clear();

    if(s1==s2)
    {
        stationsList.push_back(s2);
        stationsList.push_back(s1);
        return true;
    }
    makeGraph();

    std::vector<int> path(stations.size(), -1);
    std::vector<double> dist(stations.size(), INF);
    dist[s1]=0;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> priQ;
    priQ.push(Node(s1, 0));
    while(!priQ.empty())
    {
        Node top=priQ.top();
        priQ.pop();
        if(top.stationID==s2)
        {
            break ;
        }

        for (int i=0; i<graph[top.stationID].size(); ++i)
        {
            Node &adjNode=graph[top.stationID][i];
            if(top.distance+adjNode.distance<dist[adjNode.stationID])
            {
                path[adjNode.stationID]=top.stationID;
                dist[adjNode.stationID]=top.distance+adjNode.distance;
                priQ.push(Node(adjNode.stationID, dist[adjNode.stationID]));
            }
        }
    }

    if(path[s2]==-1)
    {
        return false;
    }
    int p=s2;
    while(path[p]!=-1)
    {
        stationsList.push_front(p);
        edgesList.push_front(Edge(path[p],p));
        p=path[p];
    }
    stationsList.push_front(s1);
    return true;
}


bool MetroGraph::queryTransferMinTransfer(int s1, int s2, QList<int>&stationsList, QList<Edge>&edgesList)
{
    stationsList.clear();
    edgesList.clear();

    if(s1==s2)
    {
        stationsList.push_back(s2);
        stationsList.push_back(s1);
        return true;
    }

    std::vector<bool> linesVisted(lines.size(),false);
    std::vector<int> path(stations.size(),-1);
    path[s1]=-2;
    std::queue<int> que;
    que.push(s1);

    while(!que.empty())
    {
        int top=que.front();
        que.pop();
        for (auto &l: stations[top].linesInfo)
        {
            if(!linesVisted[l])
            {
                linesVisted[l]=true;
                for (auto &s: lines[l].stationsSet)
                {
                    if(path[s]==-1)
                    {
                        path[s]=top;
                        que.push(s);
                    }
                }
            }
        }
    }

    if(path[s2]==-1)
    {
        return false;
    }
    int p=s2;
    while(path[p]!=-2)
    {
        stationsList.push_front(p);
        edgesList.push_front(Edge(path[p],p));
        p=path[p];
    }
    stationsList.push_front(s1);
    return true;
}
