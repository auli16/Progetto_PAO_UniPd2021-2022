#include "model.h"

Model::Model(DataStructure* ds): d(ds) {}

Model::Model(): d(new DataStructure){}

Model::Model(Model& model): d(model.d){}

Model::~Model(){
    delete d;
}

int Model::rowCount(const QModelIndex& parent) const{
    Q_UNUSED(parent);
    return d->getNRighe();
}

int Model::columnCount(const QModelIndex& parent) const{
    Q_UNUSED(parent);
    return d->getNColonne();
}

QVariant Model::data(const QModelIndex& index, int role) const{
    if (index.isValid() && role == Qt::DisplayRole) {
        return d->getDati()[index.row()][index.column()];
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const{

    if(role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal)
             return QString::fromStdString(d->getIntestazioneOriz()[section]);
        else
            return QString::fromStdString(d->getIntestazioneVert()[section]);
    }
    return QVariant();

}


bool Model::setData(const QModelIndex& index, const QVariant& value, int role){
    if (index.isValid() && role == Qt::EditRole) {
        d->modCella(index.row(), index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}


bool Model::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value , int role) {
    if(role == Qt::EditRole){
        if(orientation == Qt::Horizontal)
            d->modIntestazioneOriz(value.toString().toStdString(), section);
        else if(orientation == Qt::Vertical)
            d->modIntestazioneVert(value.toString().toStdString(), section);
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

bool Model::insertRows(int row, int count, const QModelIndex& parent){
    beginInsertRows(QModelIndex(), row, row+count-1);

    d->insertRows(row, count);

    endInsertRows();
    return true;
}

bool Model::insertColumns(int column, int count, const QModelIndex& parent){
    beginInsertColumns(QModelIndex(), column, column+count-1);

    d->insertColumns(column, count);

    endInsertColumns();
    return true;
}

bool Model::removeRows(int row, int count, const QModelIndex& parent){
    if(rowCount() == 1)
        throw std::out_of_range("Non puoi rimuovere l`ultima riga");

    beginRemoveRows(QModelIndex(), row, row+count-1);
    d->delRow(row);
    endRemoveRows();
    return true;
}

bool Model::removeColumns(int column, int count, const QModelIndex& parent){
    if(columnCount() == 1)
        throw std::out_of_range("Non puoi rimuovere l`ultima colonna");

    beginRemoveColumns(QModelIndex(), column, column+count-1);
    d->delColumn(column);
    endRemoveColumns();

    return true;
}



void Model::reset(){
    for(u_int i=0; i<columnCount(); ++i)
        setHeaderData(i, Qt::Horizontal, "o");
    for(u_int j=0; j<rowCount(); ++j)
        setHeaderData(j, Qt::Vertical, "v");
    for(u_int i = 0; i<rowCount(); ++i){
        for(u_int j =0; j<columnCount(); ++j)
            setData(index(i, j), 0);
    }
}

bool Model::r(const QJsonObject& json){
    if(json.contains("nRighe") && json["nRighe"].isDouble()){
        int r = (json["nRighe"]).toInt();
        if(r<0)
            return false;

        if(rowCount() < r){
            insertRows(0, r-rowCount());
        }else if(rowCount() > r){
            u_int a = rowCount();
            for(u_int i = 0; i<a-r; ++i)
                removeRows(0, 1);
        }


    }

    if(json.contains("nColonne") && json["nColonne"].isDouble()){
        int c = (json["nColonne"]).toInt();
        if(c<0)
            return false;

        if(columnCount() < c){
            insertColumns(0, c-columnCount());
        }else if(columnCount() > c){
            u_int a = columnCount();
            for(u_int i = 0; i<a-c; ++i){
                removeColumns(0, 1);
            }

        }

    }

    if(json.contains("dati") && json["dati"].isArray()){
        QJsonArray d = json["dati"].toArray();
        if(d.size() != (rowCount()*columnCount()))
            return false;

        u_int count=0;

        for(u_int i=0; i<rowCount(); ++i){
            for(u_int j=0; j<columnCount(); ++j){
                setData(index(i,j), d[count].toDouble());
                count++;
            }
        }
    }

    if(json.contains("intestazioneOriz") && json["intestazioneOriz"].isArray()){
        QJsonArray hO = json["intestazioneOriz"].toArray();

        if(hO.size() != columnCount())
            return false;

        for(u_int i=0; i<columnCount(); ++i){
            setHeaderData(i, Qt::Horizontal, hO[i].toString());
        }
    }

    if(json.contains("intestazioneVert") && json["intestazioneVert"].isArray()){
        QJsonArray hV = json["intestazioneVert"].toArray();
        if(hV.size() != rowCount())
            return false;

        for(u_int i=0; i<rowCount(); ++i){
            setHeaderData(i, Qt::Vertical, hV[i].toString());
        }
    }

    return true;

}


bool Model::w(QJsonObject& json) const{
    if(!(rowCount()) && !(columnCount()))
        return false;

    json["nRighe"] = static_cast<int>(rowCount());
    json["nColonne"] = static_cast<int>(columnCount());

    QJsonArray a;
    for(u_int i=0; i<rowCount(); ++i){
        for(u_int j=0; j<columnCount(); ++j)
            a.append(data(index(i,j)).toDouble());
    }
    json["dati"] = a;

    QJsonArray hO;
    for(u_int i=0; i<columnCount(); ++i){
        hO.append(headerData(i, Qt::Horizontal).toString());
    }
    json["intestazioneOriz"] = hO;

    QJsonArray hV;
    for(u_int i=0; i<rowCount(); ++i){
        hV.append(headerData(i, Qt::Vertical).toString());
    }
    json["intestazioneVert"] = hV;

    return true;
}

double Model::min() const{
    return d->min();
}

double Model::max() const{
    return d->max();
}

double Model::minCol(u_int c) const{
    return d->minCol(c);
}

double Model::maxCol(u_int c) const{
    return d->maxCol(c);
}

head Model::getIntOriz() const{
    return d->getIntestazioneOriz();
}




Qt::ItemFlags Model::flags(const QModelIndex& index) const {
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
