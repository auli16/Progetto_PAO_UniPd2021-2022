#include "graphviewer.h"

void GraphViewer::addMenu(QVBoxLayout* mainLayout){

    QMenuBar* menuBar = new QMenuBar(this);

    menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    file = new QMenu("File", menuBar);
    menuBar->addMenu(file);

    file->addAction(new QAction("Chiudi", file));
    file->addAction(new QAction("Salva con nome", file));
    file->addAction(new QAction("Apri",  file));

    connect(file->actions().at(0), SIGNAL(triggered()), this, SLOT(close()));
    connect(file->actions().at(1), SIGNAL(triggered()), this, SLOT(save()));
    connect(file->actions().at(2), SIGNAL(triggered()), this, SLOT(load()));


    tipo = new QMenu("Tipo", menuBar);
    menuBar->addMenu(tipo);

    aG = new QActionGroup(tipo);
    aG->setExclusive(true);

    menuAction = tipo->addAction("BarChart");
    menuAction->setCheckable(true);
    menuAction->setChecked(true);
    aG->addAction(menuAction);

    menuAction = tipo->addAction("LineChart");
    menuAction->setCheckable(true);
    aG->addAction(menuAction);

    menuAction = tipo->addAction("NestedDonut");
    menuAction->setCheckable(true);
    aG->addAction(menuAction);

    connect(tipo->actions().at(0), SIGNAL(triggered()), this, SLOT(setBarChart()));
    connect(tipo->actions().at(1), SIGNAL(triggered()), this, SLOT(setLineChart()));
    connect(tipo->actions().at(2), SIGNAL(triggered()), this, SLOT(setNestedDonut()));



    mainLayout->addWidget(menuBar);
}

void GraphViewer::addContextMenu(QPoint pos){
    index = tab->indexAt(pos);

    context = new QMenu(this);
    context->addAction(new QAction(("Elimina riga"), this));
    context->addAction(new QAction(("Elimina colonna"), this));

    context->popup(tab->viewport()->mapToGlobal(pos));

    connect(context->actions().at(0), SIGNAL(triggered()), this, SLOT(delRow()));
    connect(context->actions().at(1), SIGNAL(triggered()), this, SLOT(delColumn()));


}

void GraphViewer::addPushButton(QHBoxLayout* buttonL){
    addColonna = new QPushButton("Colonna+");
    addRiga = new QPushButton("Riga+");
    reset = new QPushButton("Reset");

    buttonL->addWidget(addColonna);
    buttonL->addWidget(addRiga);
    buttonL->addWidget(reset);

    connect(addRiga, SIGNAL(clicked(bool)), this, SLOT(addRow()));
    connect(addColonna, SIGNAL(clicked(bool)), this, SLOT(addColumn()));
    connect(reset, SIGNAL(clicked(bool)), this, SLOT(resetV()));


}

void GraphViewer::addTab(QVBoxLayout* rBT){
    tab = new QTableView;
    tab->setModel(model);

    connect(tab->horizontalHeader() , SIGNAL(sectionClicked(int)), this, SLOT(setHHeader(int)));
    connect(tab->verticalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(setVHeader(int)));

    tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tab->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tab->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tab, SIGNAL(customContextMenuRequested(QPoint)), SLOT(contextM(QPoint)));

    rBT->addWidget(tab);
}

void GraphViewer::disconnectionChart(){
    model->disconnect(SIGNAL(headerDataChanged(Qt::Orientation, int, int)), this, SLOT(setAxisX()));
    model->disconnect(SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),  this, SLOT(setAxisY()));
    model->disconnect(SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),  this, SLOT(setAxisX()));

    model->disconnect(SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),  this, SLOT(setNestedDonut()));
    model->disconnect(SIGNAL(headerDataChanged(Qt::Orientation, int, int)), this,  SLOT(setNestedDonut()));
}

void GraphViewer::createBarChart(){

    disconnectionChart();

    connect(model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)), this, SLOT(setAxisX()));
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(setAxisY()));

    chart->removeAllSeries();
    cV = new barchart(chart, model);

    cV->createC();
}

void GraphViewer::createLineChart(){

    disconnectionChart();

    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(setAxisX()));
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(setAxisY()));

    chart->removeAllSeries();
    cV = new linechart(chart, model);

    cV->createC();
}

void GraphViewer::createNestedDonut(){

    disconnectionChart();

    connect(model, SIGNAL(headerDataChanged(Qt::Orientation, int, int)), this, SLOT(setNestedDonut()));
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(setNestedDonut()));

    chart->removeAllSeries();
    if(chart->axisX())
        chart->removeAxis(chart->axisX());
    if(chart->axisY())
        chart->removeAxis(chart->axisY());
    cV = new nestedDonut(chart, model);

    cV->createC();
}


GraphViewer::GraphViewer(Model* m, QWidget* parent): QWidget(parent){

    model = m;

    QVBoxLayout* mainLayout = new QVBoxLayout;


    //crea menu
    addMenu(mainLayout);

    //crea schermo
    QHBoxLayout* chGraf = new QHBoxLayout;
    QVBoxLayout* rBT = new QVBoxLayout;
    chGraf->addLayout(rBT);

    //stampa tabella
    addTab(rBT);

    //stampa bottoni
    QHBoxLayout* buttonL = new QHBoxLayout;
    addPushButton(buttonL);
    rBT->addLayout(buttonL);

    //grafico
    chart = new QChart;
    createBarChart();

    chartView = new QChartView(cV->getChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);


    chGraf->addWidget(chartView);

    mainLayout->addLayout(chGraf);
    setLayout(mainLayout);

}

//Finestre di dialogo

QString GraphViewer::editHeader(){

    bool ok;
    QString s = QInputDialog::getText(this, "Set header", "Modifica intestazione", QLineEdit::Normal, "", &ok);

    return s;
}

void GraphViewer::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva come"), "", "Grafico (*.json)");

    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        qDebug()<<"Erroe apertura file";
    else
        qDebug()<<"File Aperto";

    QJsonObject obj;
    model->w(obj);
    QJsonDocument jsonDoc;
    jsonDoc.setObject(obj);

    file.write(jsonDoc.toJson());

    qDebug()<<"Scrittura effettuata";
    file.close();

}

void GraphViewer::loadFile(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Apri grafico"), "", tr("Grafico (*.json)"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"Erroe apertura file";
    else
        qDebug()<<"File Aperto";

    QByteArray data = file.readAll();
    file.close();


    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);

    if(parseError.error!=QJsonParseError::NoError){
        qDebug()<<"errore di configurazione";
        return;
    }

    QJsonObject obj = jsonDoc.object();

    model->r(obj);

    qDebug()<<"Caricamento compiuto";

}


//slots

void GraphViewer::setHHeader(int i){
    QString s = editHeader();
    model->setHeaderData(i , Qt::Horizontal, s);
}

void GraphViewer::setVHeader(int i){
    QString s = editHeader();
    model->setHeaderData(i, Qt::Vertical, s);
}

void GraphViewer::setAxisX(){
    if(dynamic_cast<barchart*>(cV))
        dynamic_cast<barchart*>(cV)->setX();
    else if(dynamic_cast<linechart*>(cV))
        dynamic_cast<linechart*>(cV)->setX();
}

void GraphViewer::setAxisY(){
    if(dynamic_cast<barchart*>(cV))
        dynamic_cast<barchart*>(cV)->setY();
    else if(dynamic_cast<linechart*>(cV))
        dynamic_cast<linechart*>(cV)->setY();
}

void GraphViewer::addRow(){
    model->insertRows(model->rowCount(),1);
    if(dynamic_cast<barchart*>(cV)){
        dynamic_cast<barchart*>(cV)->setMapperRowCount();
        setAxisX();
    }
}

void GraphViewer::addColumn(){
    model->insertColumns(model->columnCount(),1);
    if(dynamic_cast<barchart*>(cV))
        dynamic_cast<barchart*>(cV)->setMapperColumnCount();
    if(dynamic_cast<linechart*>(cV)){
        dynamic_cast<linechart*>(cV)->setMapper();
        setAxisX();
    }
}

void GraphViewer::delRow(){
    try{
        model->removeRows(index.row(), 1);

        tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tab->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        if(dynamic_cast<barchart*>(cV)){
            dynamic_cast<barchart*>(cV)->setMapperRowCount();
            setAxisX();
            setAxisY();
        }else if(dynamic_cast<linechart*>(cV)){
            dynamic_cast<linechart*>(cV)->setMapper();
            setAxisX();
            setAxisY();
        }else
            setNestedDonut();

    }catch(std::out_of_range e){
        QMessageBox::critical(this, "Attenzione!" ,e.what());
    }
}

void GraphViewer::delColumn(){
    try{
        model->removeColumns(index.column(), 1);

        tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tab->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        if(dynamic_cast<barchart*>(cV)){
            setAxisY();
            setAxisX();
            dynamic_cast<barchart*>(cV)->setMapperColumnCount();
        }else if(dynamic_cast<linechart*>(cV)){
            dynamic_cast<linechart*>(cV)->setMapper();
            setAxisX();
            setAxisY();
        }else
            setNestedDonut();


    }catch(std::out_of_range e){
        QMessageBox::critical(this, "Attenzione!" ,e.what());
    }
}

void GraphViewer::setBarChart(){
    createBarChart();
}

void GraphViewer::setLineChart(){
    createLineChart();
}

void GraphViewer::setNestedDonut(){
    createNestedDonut();
}

void GraphViewer::resetV(){
    model->reset();
}

void GraphViewer::contextM(QPoint p){
    addContextMenu(p);
}

void GraphViewer::save(){
    saveFile();
}

void GraphViewer::load(){
    loadFile();
    if(dynamic_cast<barchart*>(cV)){
        dynamic_cast<barchart*>(cV)->setMapperColumnCount();
        dynamic_cast<barchart*>(cV)->setMapperRowCount();
    }
    if(dynamic_cast<linechart*>(cV)){
        dynamic_cast<linechart*>(cV)->setMapper();
        setAxisX();
        setAxisY();
    }

}







