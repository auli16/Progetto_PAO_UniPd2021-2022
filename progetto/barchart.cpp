#include "barchart.h"

barchart::barchart(QChart* ch, Model* m): chartV(ch, m){}

barchart::~barchart(){
    delete series;
    delete mapper;
    delete axisX;
    delete axisY;
}


void barchart::createC(){

    chart->setAnimationOptions(QChart::AllAnimations);

    series = new QBarSeries;


    mapper = new QVBarModelMapper();

    mapper->setFirstBarSetColumn(0);
    mapper->setLastBarSetColumn(model->columnCount()-1);
    mapper->setFirstRow(0);
    mapper->setRowCount(model->rowCount());
    mapper->setSeries(series);
    mapper->setModel(model);

    chart->addSeries(series);

    setX();
    setY();

    chart->setTitle(QString::fromStdString("BarChart"));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


}

void barchart::setMapperColumnCount(){
    mapper->setLastBarSetColumn(model->columnCount()-1);
}

void barchart::setMapperRowCount(){
    mapper->setRowCount(model->rowCount());
}

void barchart::setCategories(){

    for(u_int i=0; i<model->rowCount(); ++i){
        categories<<model->headerData(i, Qt::Vertical).toString();
    }
}



void barchart::setX(){

    categories.clear();
    setCategories();

    axisX = new QBarCategoryAxis();
    axisX->append(categories);

    if(chart->axisX())
        chart->removeAxis(chart->axisX());

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
}

void barchart::setY(){

    axisY = new QValueAxis();

    if(chart->axisY())
        chart->removeAxis(chart->axisY());

    chart->addAxis(axisY, Qt::AlignLeft);

    double min = model->min();
    double max = model->max();
    if (min == max)
        max++;
    if(min > 0)
        axisY->setRange(0, max);
    else
        axisY->setRange(min, max);

    series->attachAxis(axisY);
}



