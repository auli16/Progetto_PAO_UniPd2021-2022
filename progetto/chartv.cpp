#include "chartv.h"

chartV::chartV(QChart* ch, Model* m): chart(ch), model(m){}

chartV::~chartV(){
    delete chart;
    delete model;
}

QChart* chartV::getChart(){
    return chart;
}

