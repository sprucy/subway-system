#include "ui_addstation.h"
#include "addstation.h"
#include "global.h"


#include <QPixmap>
#include <QMessageBox>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Constructor
AddStation::AddStation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStation)
{
    ui->setupUi(this);

    updateLinesListWidget();
    updateComboBox();

}

//Destructor
AddStation::~AddStation()
{
    delete ui;
}


//Update route list information
void AddStation::updateLinesListWidget()
{
    QListWidget* listWidget=ui->listWidget;
    for(int i=0; i<linesNameList.size(); ++i)
    {
        QListWidgetItem *item =listWidget->takeItem(i);
        delete item;
    }
    listWidget->clear();
    linesSelected.clear();

    linesNameList=metroGraph->getLinesNameList();

    for(int i=0; i<linesNameList.size(); ++i)
    {
        QListWidgetItem *item=new QListWidgetItem(linesNameList[i]);
        item->setFlags(item->flags()|Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        listWidget->addItem(item);
    }
}

// Update selection widgets
void AddStation::updateComboBox()
{
    ui->comboBoxConnectStation1->clear();
    ui->comboBoxConnectStation2->clear();
    ui->comboBoxConnectLine->clear();
    linesNameList=metroGraph->getLinesNameList();
    stationsNameList=metroGraph->getLineStationsList(0);
    for (auto &a: stationsNameList)
    {
        ui->comboBoxConnectStation1->addItem(a);
        ui->comboBoxConnectStation2->addItem(a);
    }
    for (auto &a: linesNameList)
    {
        ui->comboBoxConnectLine->addItem(a);
    }
}

//Click on the Select Colour button
void AddStation::on_pushButtonChooseColor_clicked()
{
    QColorDialog colorDialog;
    colorDialog.setOptions(QColorDialog::ShowAlphaChannel);
    colorDialog.exec();
    lineColor=colorDialog.currentColor();
    return ;
}


//List widget selections change
void AddStation::on_listWidget_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    QString str;
    linesSelected.clear();

    for (int i=0; i<ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item=ui->listWidget->item(i);
        if(item->checkState()==Qt::Checked)
        {
            linesSelected.push_back(item->text());
            str+=item->text();
            str+="\n";
        }
    }
}



void AddStation::on_comboBoxConnectLine_currentIndexChanged(const QString &arg1)
{

    QComboBox* comboConnectStation1=ui->comboBoxConnectStation1;
    QComboBox* comboConnectStation2=ui->comboBoxConnectStation2;
    comboConnectStation1->clear();
    comboConnectStation2->clear();

    int lineHash=metroGraph->getLineHash(arg1);
    if(lineHash==-1)
    {
        return ;
    }

    QList<QString> stationsList=metroGraph->getLineStationsList(lineHash);
    for(auto &a:stationsList)
    {
        comboConnectStation1->addItem(a);
        comboConnectStation2->addItem(a);
    }

}

void AddStation::on_pushButtonexit_clicked()
{
    close();
}
