#include "linechart.h"

linechart::linechart(QChart* ch, Model* m): chartV(ch, m){}

linechart::~linechart(){
    for(auto it = series.begin(); it!=series.end(); ++it)
        delete *it;
    for(auto it = mapper.begin(); it!=mapper.end(); ++it)
        delete *it;
    delete axisX;
    delete axisY;
}

void linechart::createC(){

    chart->setAnimationOptions(QChart::AllAnimations);

    nCol = (model->columnCount() /2)*2;

    for(u_int i = 0; i<nCol; i+=2){

        QLineSeries* se = new QLineSeries;
        series.push_back(se);




        QVXYModelMapper* mm = new QVXYModelMapper;
        mapper.push_back(mm);

        mapper[i/2]->setXColumn(i);
        mapper[i/2]->setYColumn(i+1);
        chart->addSeries(series[i/2]);

        mapper[i/2]->setSeries(series[i/2]);
        mapper[i/2]->setModel(model);

    }

    setX();
    setY();

    chart->setTitle(QString::fromStdString("LineChart"));
    chart->legend()->setVisible(false);
}

void linechart::setMapper(){

    u_int colAt = nCol;
    nCol = (model->columnCount() /2)*2;



    for(u_int i = colAt; i<nCol; i+=2){


        QLineSeries* se = new QLineSeries;
        series.push_back(se);

        string s = "Linea " + std::to_string(i/2);
        series[i/2]->setName(QString::fromStdString(s));


        QVXYModelMapper* mm = new QVXYModelMapper;
        mapper.push_back(mm);

        mapper[i/2]->setXColumn(i);
        mapper[i/2]->setYColumn(i+1);
        chart->addSeries(series[i/2]);

        mapper[i/2]->setSeries(series[i/2]);
        mapper[i/2]->setModel(model);
    }
}

void linechart::setX(){

    axisX = new QValueAxis;

    if(chart->axisX())
        chart->removeAxis(chart->axisX());

    chart->addAxis(axisX, Qt::AlignBottom);

    double min = 0;
    double max = 0;
    int col = (model->columnCount() /2)*2;

    for(u_int i = 0; i< col; i+=2){
        if(model->minCol(i) < min)
            min = model->minCol(i);
        if(model->maxCol(i) > max)
            max = model->maxCol(i);
    }

    if (min == max)
        max++;
    if(min > 0)
        axisX->setRange(0, max);
    else
        axisX->setRange(min, max);

    for(u_int i = 0; i<series.size(); ++i)
        series[i]->attachAxis(axisX);


}

void linechart::setY(){

    axisY = new QValueAxis;



    if(chart->axisY())
        chart->removeAxis(chart->axisY());

    chart->addAxis(axisY, Qt::AlignLeft);

    double min = 0;
    double max = 0;

    u_int col = (model->columnCount() /2)*2;

    for(u_int i = 1; i< col; i+=2){
        if(model->minCol(i) < min)
            min = model->minCol(i);
        if(model->maxCol(i) > max){
            max = model->maxCol(i);
        }
    }

    if (min == max)
        max++;
    if(min > 0)
        axisY->setRange(0, max);
    else{
        axisY->setRange(min, max);
    }

    for(u_int i = 0; i<series.size(); ++i)
        series[i]->attachAxis(axisY);
}











