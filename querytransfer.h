#ifndef QUERYTRANSFER_H
#define QUERYTRANSFER_H

#include <QDialog>
#include "metroGraph.h"

class MainWindow;


namespace Ui {
class QueryTransfer;
}

class QueryTransfer : public QDialog
{
    Q_OBJECT

public:
    explicit QueryTransfer(QWidget *parent = nullptr);
    ~QueryTransfer();


public:
    Ui::QueryTransfer *ui;
    void updateTranserQueryInfo();
    QString getLinesName(const QList<int>& linesList);


private slots:
    void on_pushButtonexit_clicked();
    void transferDstLineChanged(QString lineName);
    void transferStartLineChanged(QString lineName);
    void transferQuery();

};

#endif // QUERYTRANSFER_H
