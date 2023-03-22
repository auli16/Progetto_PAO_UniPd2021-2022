#ifndef CHARTV_H
#define CHARTV_H

#include <QChartView>
#include <QtCharts>
#include <QChart>

#include "model.h"

class chartV{
protected:
    QChart* chart;
    Model* model;

public:
    chartV(QChart*, Model* m);
    virtual ~chartV();

    virtual void createC() =0; //permette la costruzione del chart

    QChart* getChart();
};

#endif // CHARTV_H
