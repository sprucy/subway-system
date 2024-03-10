#include "ui_mainwindow.h"
#include "ui_addstation.h"
#include "ui_querytransfer.h"
#include "ui_about.h"
#include "mainwindow.h"
#include "about.h"
#include "global.h"

#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myView = new Graphics_view_zoom(ui->graphicsView);
    myView->set_modifiers(Qt::NoModifier);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    scene=new QGraphicsScene;
    scene->setSceneRect(-LINE_INFO_WIDTH,0,SCENE_WIDTH,SCENE_HEIGHT);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);


    addStation=new AddStation(this);
    querytransfer=new QueryTransfer(this);
    about=new About(this);

    myConnect();

    drawLineMap();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myView;
    delete scene;
    delete addStation;
    delete querytransfer;
    delete about;

}

//连接信号和槽函数
void MainWindow::myConnect()
{
    connect(addStation->ui->pushButtonAddLine, SIGNAL(clicked()), this, SLOT(appendLine()));
    connect(addStation->ui->pushButtonAddStation, SIGNAL(clicked()), this, SLOT(appendStation()));
    connect(addStation->ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(appendConnection()));
}

//由线路表计算混合颜色
QColor MainWindow::getLinesColor(const QList<int>& linesList)
{
    QColor color1=QColor(255,255,255);
    QColor color2;
    for (int i=0; i<linesList.size(); ++i)
    {
        color2=metroGraph->getLineColor(linesList[i]);
        color1.setRed(color1.red()*color2.red()/255);
        color1.setGreen(color1.green()*color2.green()/255);
        color1.setBlue(color1.blue()*color2.blue()/255);
    }
    return color1;
}

//获得线路表的名字集
QString MainWindow::getLinesName(const QList<int>& linesList)
{
    QString str;
    str+="\t";
    for (int i=0; i<linesList.size(); ++i)
    {
        str+=" ";
        str+=metroGraph->getLineName(linesList[i]);
    }
    return str;
}

//将站点的XY地理坐标转为视图坐标
QPointF MainWindow::transferCoord(QPointF coord)
{
    QPointF minCoord=metroGraph->getMinCoord();
    QPointF maxCoord=metroGraph->getMaxCoord();
    double x = (coord.x()-minCoord.x())/(maxCoord.x()-minCoord.x())*NET_WIDTH+MARGIN;
    double y = (maxCoord.y()-coord.y())/(maxCoord.y()-minCoord.y())*NET_HEIGHT+MARGIN;
    return QPointF(x,y);
}

//绘制网络图的边
void MainWindow::drawEdges(const QList<Edge>& edgesList)
{
    for(int i=0; i<edgesList.size(); ++i)
    {
        int s1=edgesList[i].first;
        int s2=edgesList[i].second;

        QList<int> linesList=metroGraph->getCommonLines(s1, s2);
        QColor color=getLinesColor(linesList);
        QPointF s1Pos=transferCoord(metroGraph->getStationCoord(s1));
        QPointF s2Pos=transferCoord(metroGraph->getStationCoord(s2));

        QGraphicsLineItem* edgeItem=new QGraphicsLineItem;
        edgeItem->setPen(QPen(color, EDGE_PEN_WIDTH));
        edgeItem->setCursor(Qt::PointingHandCursor);
        edgeItem->setPos(s1Pos);
        edgeItem->setLine(0, 0, s2Pos.x()-s1Pos.x(), s2Pos.y()-s1Pos.y());
        scene->addItem(edgeItem);
    }
}

//绘制网络图的站点节点
void MainWindow::drawStations (const QList<int>& stationsList)
{
    for (int i=0; i<stationsList.size(); ++i)
    {
        int s=stationsList[i];
        QString name=metroGraph->getStationName(s);
        QList<int> linesList=metroGraph->getStationLinesInfo(s);
        QColor color=getLinesColor(linesList);
        QPointF XY=metroGraph->getStationCoord(s);
        QPointF coord=transferCoord(XY);


        QGraphicsEllipseItem* stationItem=new QGraphicsEllipseItem;
        stationItem->setRect(-NODE_HALF_WIDTH, -NODE_HALF_WIDTH, NODE_HALF_WIDTH<<1, NODE_HALF_WIDTH<<1);
        stationItem->setPos(coord);
        stationItem->setPen(color);
        stationItem->setCursor(Qt::PointingHandCursor);

        if(linesList.size()<=1)
        {
            stationItem->setBrush(QColor(QRgb(0xffffff)));
        }

        scene->addItem(stationItem);

        QGraphicsTextItem* textItem=new QGraphicsTextItem;
        textItem->setPlainText(name);
        textItem->setFont(QFont("consolas",4,QFont::Bold));
        textItem->setPos(coord.x()-NODE_HALF_WIDTH,coord.y()-NODE_HALF_WIDTH*5);
        scene->addItem(textItem);
    }
}


//添加线路功能函数
void MainWindow::appendLine()
{
    QMessageBox box;
    addStation->lineName=addStation->ui->lineEditLineName->text();
    box.setWindowTitle(u8"添加线路");

    if(addStation->lineName.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"请输入线路名称！");
    }
    else if(metroGraph->getLineHash(addStation->lineName)==-1)
    {
        box.setIcon(QMessageBox::Information);
        box.setText(u8"线路："+addStation->lineName+u8" 添加成功！");

        qDebug()<<"linename:"<<addStation->lineName;

        metroGraph->addLine(addStation->lineName, addStation->lineColor);

        addStation->updateLinesListWidget();
        addStation->updateComboBox();


    }
    else
    {
        box.setIcon(QMessageBox::Critical);
        box.setText(u8"添加失败！\n错误原因：线路名已存在！");
    }

    box.addButton(u8"确定",QMessageBox::AcceptRole);
    if(box.exec()==QMessageBox::Accepted)
    {
        box.close();
    }

}

//添加站点功能函数
void MainWindow::appendStation()
{
    QMessageBox box;
    addStation->stationName=addStation->ui->lineEditStationName->text();
    addStation->X=addStation->ui->doubleSpinBoxX->value();
    addStation->Y=addStation->ui->doubleSpinBoxY->value();
    box.setWindowTitle(u8"添加站点");

    if(addStation->stationName.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"请输入站点名称！");
    }
    else if(addStation->linesSelected.isEmpty())
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"请选择站点所属线路！");
    }
    else
    {
        if(metroGraph->getStationHash(addStation->stationName)!=-1)
        {
            box.setIcon(QMessageBox::Critical);
            box.setText(u8"添加失败！\n错误原因：站点已存在！");
        }
        else
        {
            Station s(addStation->stationName, addStation->X, addStation->Y,
                      metroGraph->getLinesHash(addStation->linesSelected));
            metroGraph->addStation(s);
            drawLineMap();
            addStation->updateComboBox();
            box.setText(u8"站点："+addStation->stationName+u8" 添加成功！");
        }
    }

    box.addButton(u8"确定",QMessageBox::AcceptRole);
    if(box.exec()==QMessageBox::Accepted)
    {
        box.close();
    }

}

//添加连接功能函数
void MainWindow::appendConnection()
{
    QString station1=addStation->ui->comboBoxConnectStation1->currentText();
    QString station2=addStation->ui->comboBoxConnectStation2->currentText();
    int s1=metroGraph->getStationHash(station1);
    int s2=metroGraph->getStationHash(station2);
    int l=metroGraph->getLineHash(addStation->ui->comboBoxConnectLine->currentText());

    QMessageBox box;
    box.setWindowTitle(u8"添加连接");

    if(s1==-1||s2==-1||l==-1)
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"请选择已有的站点和线路！");
    }
    else if(s1==s2)
    {
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"无法连接相同站点！");
    }
    else if(!metroGraph->getStationLinesInfo(s1).contains(l))
    {
        box.setIcon(QMessageBox::Critical);
        box.setText(u8"连接失败！\n错误原因：所属线路不包含开始站点");
    }
    else if(!metroGraph->getStationLinesInfo(s2).contains(l))
    {
        box.setIcon(QMessageBox::Critical);
        box.setText(u8"连接失败！\n错误原因：所属线路不包含结束站点");
    }
    else
    {
        box.setIcon(QMessageBox::Information);
        box.setText(u8"添加连接成功！");
        metroGraph->addConnection(s1,s2,l);
        drawLineMap();
    }
    if(box.exec()==QMessageBox::Accepted)
    {
        box.close();
    }

}


//查看所有线路图
void MainWindow::drawLineMap()
{
    scene->clear();
    QList<int> stationsList;
    QList<Edge> edgesList;
    metroGraph->getGraph(stationsList,edgesList);
    drawEdges(edgesList);
    drawStations(stationsList);

}


//动作关闭程序槽函数
void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionquery_triggered()
{
    querytransfer->show();
}



void MainWindow::on_actionAdd_triggered()
{
    addStation->show();
}

void MainWindow::on_actionAbout_triggered()
{
    about->show();
}
