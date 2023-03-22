#ifndef BARCHART_H
#define BARCHART_H


#include "chartv.h"


class barchart: public chartV{
private:
    QBarSeries* series;
    QVBarModelMapper* mapper;
    QStringList categories;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;

public:
    barchart(QChart*, Model*);
    ~barchart();

    void createC();
    void setCategories();
    void setMapperColumnCount();
    void setMapperRowCount();
    void setX();
    void setY();

};

#endif // BARCHART_H
