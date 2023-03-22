#ifndef LINECHART_H
#define LINECHART_H

#include <QVXYModelMapper>

#include "chartv.h"

class linechart: public chartV{
private:
    vector<QLineSeries*> series;
    vector<QVXYModelMapper*> mapper;
    QValueAxis* axisY;
    QValueAxis* axisX;
    u_int nCol;

public:
    linechart(QChart*, Model*);
    ~linechart();

    void createC();
    void setCategories();
    void setMapper();
    void setX();
    void setY();

};

#endif // LINECHART_H
