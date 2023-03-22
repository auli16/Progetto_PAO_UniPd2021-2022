#ifndef NESTEDDONUT_H
#define NESTEDDONUT_H

#include "chartv.h"

class nestedDonut: public chartV{
public:
    nestedDonut(QChart*, Model*);
    ~nestedDonut() = default;

    void createC();

};

#endif // NESTEDDONUT_H
