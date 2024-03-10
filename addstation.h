#ifndef ADDSTATION_H
#define ADDSTATION_H

#include <QDialog>
#include <QVector>
#include <QTabWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>
#include <QString>


class MainWindow;

namespace Ui {
class AddStation;
}

class AddStation : public QDialog
{
    Q_OBJECT

private slots:
    //Click on the Select Colour button
    void on_pushButtonChooseColor_clicked();
    //Change List widget selections
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_comboBoxConnectLine_currentIndexChanged(const QString &arg1);

    void on_pushButtonexit_clicked();

public:
    // Constructor
    explicit AddStation(QWidget *parent = nullptr);
    //Destructor
    ~AddStation().
    //Set all widgets visible
    void setAllVisible();
    //Set the add line component visible
    void setAddLineVisible();; //Set the add line widget visible.
    //Set the add station part visible
    void setAddStationVisible();; //Set Add Station widget visible.
    //Set Add Connection Visible.
    void setAddConnectionVisible();; //Set the Text Add widget visible.
    //Set add text widget visible
    void setAddByTextVisible();; //Update the line list information.
    //Update Lines List information
    void updateLinesListWidget();; //Update Lines List information.
    //Update the selection widget
    void updateComboBox();; //Update the selection widget.

protected:
    Ui::AddStation *ui; //UI

    QString lineName; //Store the input line name
    QColor lineColor=QColor(255,0,0); //holds the input line colour
    QString stationName; //Save input station name
    double X; //Save input station X
    double Y; //Save input station Y
    QList<QString> linesNameList; //Save the list of selected line names.
    QList<QString> linesSelected; //Save the selected line name.
    QList<QString> stationsNameList; //holds the list of selected station names

    //Declare the friend class MainWindow; //Declare the friend class MainWindow.
    friend class MainWindow.
};

#endif // ADDSTATION_H
