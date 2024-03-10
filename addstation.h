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
    //点击选择颜色按钮
    void on_pushButtonChooseColor_clicked();
    //列表部件选择项改变
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_comboBoxConnectLine_currentIndexChanged(const QString &arg1);

    void on_pushButtonexit_clicked();

public:
    //构造函数
    explicit AddStation(QWidget *parent = nullptr);
    //析构函数
    ~AddStation();
    //设置所有部件可见
    void setAllVisible();
    //设置添加线路部件可见
    void setAddLineVisible();
    //设置添加站点部件可见
    void setAddStationVisible();
    //设置添加连接部件可见
    void setAddConnectionVisible();
    //设置文本添加部件可见
    void setAddByTextVisible();
    //更新线路列表信息
    void updateLinesListWidget();
    //更新选择部件
    void updateComboBox();

protected:
    Ui::AddStation *ui;                //UI

    QString lineName;                   //保存输入线路名
    QColor lineColor=QColor(255,0,0);                   //保存输入线路颜色
    QString stationName;                //保存输入站点名
    double X;                   //保存输入站点X
    double Y;                    //保存输入站点Y
    QList<QString> linesNameList;       //保存选择线路名表
    QList<QString> linesSelected;       //保存选择的线路名
    QList<QString> stationsNameList;    //保存选择站点名表

    //声明友元
    friend class MainWindow;
};

#endif // ADDSTATION_H
