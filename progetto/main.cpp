#include "graphviewer.h"
#include "model.h"

#include <QApplication>


int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    Model m;
    GraphViewer w(&m);

    w.show();

    return a.exec();
}
