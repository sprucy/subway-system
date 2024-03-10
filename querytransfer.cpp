#include "querytransfer.h"
#include "global.h"
#include "ui_querytransfer.h"
#include <QMessageBox>

QueryTransfer::QueryTransfer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryTransfer)
{
    ui->setupUi(this);

    connect(ui->comboBoxStartLine, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(transferStartLineChanged(QString)));
    connect(ui->comboBoxDstLine, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(transferDstLineChanged(QString)));
    connect(ui->pushButtonTransfer, SIGNAL(clicked()), this, SLOT(transferQuery()));

    updateTranserQueryInfo();

}

QueryTransfer::~QueryTransfer()
{
    delete ui;
}

void QueryTransfer::on_pushButtonexit_clicked()
{
    close();
}

QString QueryTransfer::getLinesName(const QList<int>& linesList)
{
    QString str;
    str+="\t";
    for (int i=0; i<linesList.size(); ++i)
    {
        str+=" ";
        str+=metroGraph->getLineName(linesList[i]);
    }
//    qDebug()<<"tip="<<str<<"\n";
    return str;
}

void QueryTransfer::updateTranserQueryInfo()
{
    QComboBox* comboL1=ui->comboBoxStartLine;
    QComboBox* comboL2=ui->comboBoxDstLine;

    comboL1->clear();
    comboL2->clear();
    QList<QString> linesList=metroGraph->getLinesNameList();
    for(auto &a:linesList)
    {
        comboL1->addItem(a);
        comboL2->addItem(a);
    }
    transferStartLineChanged(comboL1->itemText(0));
    transferDstLineChanged(comboL2->itemText(0));
}

void QueryTransfer::transferStartLineChanged(QString lineName)
{
    QComboBox* comboS1=ui->comboBoxStartStation;
    comboS1->clear();

    int lineHash=metroGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=metroGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS1->addItem(a);
    }
}

//Transfer destination line change slot function
void QueryTransfer::transferDstLineChanged(QString lineName)
{
    QComboBox* comboS2=ui->comboBoxDstStation;
    comboS2->clear();

    int lineHash=metroGraph->getLineHash(lineName);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=metroGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboS2->addItem(a);
    }
}

//Transfer query slot function
void QueryTransfer::transferQuery()
{
    int s1=metroGraph->getStationHash(ui->comboBoxStartStation->currentText());
    int s2=metroGraph->getStationHash(ui->comboBoxDstStation->currentText());
    int way=ui->radioButtonMinTime->isChecked()?1:2;

    if(s1==-1||s2==-1)
    {
        QMessageBox box;
        box.setWindowTitle(u8"Transfer enquiry");
        box.setIcon(QMessageBox::Warning);
        box.setText(u8"Please choose a route with a stop");
        box.addButton(u8"Confirm",QMessageBox::AcceptRole);
        if(box.exec()==QMessageBox::Accepted)
        {
            box.close();
        }
    }
    else
    {
        QList<int> stationsList;
        QList<Edge> edgesList;
        bool flag=true;
        if(way==1)
        {
            flag=metroGraph->queryTransferMinTime(s1, s2, stationsList, edgesList);
        }
        else
        {
            flag=metroGraph->queryTransferMinTransfer(s1, s2, stationsList, edgesList);
        }

        if(flag)
        {
//            scene->clear();
//            drawEdges(edgesList);
//            drawStations(stationsList);
            QString text=way==1?(u8"换乘实现最短：共换乘"+QString::number(stationsList.size()-1)+u8"个站点\n\n"):(u8"换乘站数最少：共换乘"+QString::number(stationsList.size()-1)+u8"条线路\n\n");
            for(int i=0; i<stationsList.size(); ++i)
            {
                if(i)
                {
                    text+=u8"\n   ↓\n";
                }
                text+=metroGraph->getStationName(stationsList[i]);
                QString linesStr=getLinesName(metroGraph->getStationLinesInfo(stationsList[i]));
                text+=linesStr;
            }
            QTextBrowser* browser=ui->textBrowserRoute;
            browser->clear();
            browser->setText(text);
        }
        else
        {
            QMessageBox box;
            box.setWindowTitle(u8"换乘查询");
            box.setIcon(QMessageBox::Warning);
            box.setText(u8"您选择的起始和终止站点暂时无法到达！");
            box.addButton(u8"确定",QMessageBox::AcceptRole);
            if(box.exec()==QMessageBox::Accepted)
            {
                box.close();
            }
        }
    }
}
