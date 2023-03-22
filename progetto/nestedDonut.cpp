#include "nestedDonut.h"

nestedDonut::nestedDonut(QChart* ch,  Model* m): chartV(ch, m){}

void nestedDonut::createC(){

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTitle(QString::fromStdString("NestedDonut"));
    chart->legend()->setVisible(false);

    head s = model->getIntOriz();

    qreal minSize = 0.1;
    qreal maxSize = 0.9;

    u_int donutCount = model->rowCount();
    u_int sliceCount = model->columnCount();

    for(u_int i= 0; i<donutCount; ++i){
        QPieSeries* donut = new QPieSeries;
        for(u_int j = 0; j<sliceCount; ++j){
            qreal value = (model->data(model->index(i, j))).toDouble();
            QPieSlice *slice = new QPieSlice(QString::fromStdString(s[j]), value);

            slice->setLabelVisible(true);
            slice->setLabelColor(Qt::white);
            slice->setLabelPosition(QPieSlice::LabelInsideTangential);

            donut->append(slice);

            donut->setHoleSize(minSize + i*(maxSize-minSize)/ donutCount);
            donut->setPieSize(minSize + (i + 1) * (maxSize - minSize) / donutCount);
        }
        chart->addSeries(donut);
    }
}
