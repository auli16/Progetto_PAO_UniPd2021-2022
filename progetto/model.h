#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

#include "datastructure.h"


class Model: public QAbstractTableModel{
private:
    DataStructure* d;

public:

    Model(DataStructure*);
    Model(Model&);
    Model();
    ~Model();

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;
    QVariant headerData(int , Qt::Orientation, int = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int = Qt::EditRole) override;
    bool setHeaderData(int, Qt::Orientation,const QVariant&, int = Qt::EditRole) override;

    bool insertRows(int, int, const QModelIndex& = QModelIndex()) override;
    bool insertColumns(int, int, const QModelIndex& = QModelIndex()) override;

    bool removeRows(int, int, const QModelIndex& = QModelIndex()) override;
    bool removeColumns(int, int, const QModelIndex& = QModelIndex()) override;

    void reset(); //i valori numerici vengono messi a 0, quelli del VerticalHaeder a 'v' e quelli dell`horizzontal a 'o'
    bool r(const QJsonObject&); //scrittura su file
    bool w(QJsonObject&) const; //caricamento da file

    double min() const; //ritorna il minimo valore della tabella
    double max() const; //ritorna massimo valore della tabella

    double minCol(u_int) const; //ritorna il minimo valore di una determinata colonna
    double maxCol(u_int) const; //ritorna il massimo valore di una determinata colonna

    head getIntOriz() const;



    Qt::ItemFlags flags(const QModelIndex&) const override;






};

#endif // MODEL_H
