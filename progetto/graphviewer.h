#ifndef GRAPHVIEWER_H
#define GRAPHVIEWER_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QPushButton>

#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>

#include <QDialog>
#include <QFormLayout>

#include <QString>


#include <utility>


#include <QChartView>
#include <QtCharts>
#include <QChart>

#include "model.h"
#include "chartv.h"
#include "barchart.h"
#include "linechart.h"
#include "nestedDonut.h"



class GraphViewer: public QWidget{
    Q_OBJECT

private:

    Model* model;

    QMenu* file;
    QMenu* tipo;

    QActionGroup* aG;
    QAction* menuAction;

    QMenu* context;
    QModelIndex index;


    QTableView* tab;

    QPushButton* addColonna;
    QPushButton* addRiga;
    QPushButton* reset;

    chartV* cV;
    QChartView* chartView;
    QChart* chart;



    void addMenu(QVBoxLayout*); //creazione del menu
    void addContextMenu(QPoint); //creazione del context menu
    void addPushButton(QHBoxLayout*); //inserimento dei bottoni
    void addTab(QVBoxLayout*); //creazione della tabella
    void disconnectionChart(); //rimozione di tutte le connection
    void createBarChart(); //creazione del BarChart
    void createLineChart(); //creazione del LineChart
    void createNestedDonut(); //creazione del NestedDonut


public:
    explicit GraphViewer(Model* m, QWidget* = nullptr);

    QString editHeader();
    void saveFile(); //salvataggio su file
    void loadFile(); //caricamento di un file


public slots:

    void setHHeader(int);
    void setVHeader(int);
    void setAxisX();
    void setAxisY();

    void addRow();
    void addColumn();

    void delRow();
    void delColumn();


    void setBarChart();
    void setLineChart();
    void setNestedDonut();

    void resetV();
    void contextM(QPoint);

    void save();
    void load();



};

#endif // GRAPHVIEWER_H
