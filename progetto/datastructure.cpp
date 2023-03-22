#include "datastructure.h"

DataStructure::DataStructure(u_int nR, u_int nC, tab t, head oriz, head vert) : nRighe(nR), nColonne(nC),
            dati(t), intestazioneOriz(oriz), intestazioneVert(vert) {}

DataStructure::DataStructure(): nRighe(3), nColonne(3), dati(nRighe, vector<double>(nColonne)),
            intestazioneOriz(3), intestazioneVert(3) {
    for(u_int i=0; i<3 ; ++i){
        intestazioneOriz[i].push_back('o');
        intestazioneVert[i].push_back('v');
    }
}

DataStructure::DataStructure(const DataStructure& d): nRighe(d.nRighe), nColonne(d.nColonne), dati(d.dati),
            intestazioneOriz(d.intestazioneOriz), intestazioneVert(d.intestazioneVert){}


u_int DataStructure::size() const{
    return nRighe*nColonne;
}

double DataStructure::max() const{
    double d = dati[0][0];
    for(u_int i=0; i<nRighe; ++i){
        for(u_int j=0; j<nColonne; ++j){
            if(dati[i][j]>d)
                d = dati[i][j];
        }
    }
    return d;
}

double DataStructure::min() const{
    double d = dati[0][0];
    for(u_int i=0; i<nRighe; ++i){
        for(u_int j=0; j<nColonne; ++j){
            if(dati[i][j]<d)
                d = dati[i][j];
        }
    }
    return d;
}

double DataStructure::maxCol(u_int c) const{
    double d = 0;
    for(u_int i=0; i<nRighe; ++i){
        if(dati[i][c]>d)
            d = dati[i][c];
    }
    return d;
}

double DataStructure::minCol(u_int c) const{
    double d = 0;
    for(u_int i=0; i<nRighe; ++i){
        if(dati[i][c]<d)
            d = dati[i][c];
    }
    return d;
}


void DataStructure::stampaDataStructure() const{
    for(auto it = intestazioneOriz.begin(); it != intestazioneOriz.end(); ++it)
        cout<<*it<<" ";
    cout<<endl;
    for(u_int i=0; i<nRighe; ++i){
        cout<<intestazioneVert[i]<<" ";
        for(u_int j=0; j<nColonne; ++j){
            cout<<dati[i][j];
        }
        cout<<endl;
    }

}

string DataStructure::modIntestazioneVert(string s, u_int n){
    if(n>=intestazioneVert.size())
        throw std::out_of_range("L`indice non e` valido");
    string aux = intestazioneVert[n];
    intestazioneVert[n] = s;
    return aux;
}

string DataStructure::modIntestazioneOriz(string s, u_int n){
    if(n>=intestazioneOriz.size())
        throw std::out_of_range("L`indice non e` valido");
    string aux = intestazioneOriz[n];
    intestazioneOriz[n] = s;
    return aux;
}

double DataStructure::modCella(u_int r, u_int c, double m){
    if(r>=nRighe)
        throw std::out_of_range("L`indice inserito per le righe non e` corretto");
    if(c>=nColonne)
        throw std::out_of_range("L`indice inseruto per le colonne non e` corretto");

    double d = dati[r][c];
    dati[r][c] = m;
    return d;
}

void DataStructure::addRows(u_int n){
    nRighe +=n;
    for(u_int i=0; i<n; ++i){
        intestazioneVert.push_back("v");
        dati.push_back(vector<double>(nColonne, 0));
    }
}

void DataStructure::addColumns(u_int n){
    nColonne +=n;
    for(u_int i=0; i<n; ++i){
        intestazioneOriz.push_back("o");
        for(u_int j=0; j<nRighe; ++j)
            dati[i].push_back(0);
    }
}

void DataStructure::insertRows(u_int n, u_int q){
    if(n>nRighe)
        throw std::out_of_range("La posizione di inserimento non e` valida");

    nRighe+=q;
    auto it = intestazioneVert.begin();
    intestazioneVert.insert(it+n, q, "v");

    auto itR = dati.begin();
    dati.insert(itR+n, q, vector<double>(nColonne, 0));

}

void DataStructure::insertColumns(u_int n, u_int q){
    if(n>nColonne)
        throw std::out_of_range("La posizione di inserimento non e` valida");

    nColonne+=q;
    auto it = intestazioneOriz.begin();
    intestazioneOriz.insert(it+n, q, "o");

    for(u_int i=0; i<nRighe; ++i){
        auto itC = dati[i].begin();
        dati[i].insert(itC+n, q, 0);
    }
}

void DataStructure::delRow(u_int n){
    if(n>=nRighe)
        throw std::out_of_range("La posizione di eliminazione non e` valida");

    auto it = intestazioneVert.begin();
    intestazioneVert.erase(it+n);

    auto itR = dati.begin();
    dati.erase(itR+n);

    nRighe--;
}

void DataStructure::delColumn(u_int n){
    if(n>=nColonne)
        throw std::out_of_range("La posizione di eliminazione non e` valida");

    auto it=intestazioneOriz.begin();
    intestazioneOriz.erase(it+n);

    for(u_int i=0; i<nRighe; ++i){
        auto itC = dati[i].begin();
        dati[i].erase(itC+n);
    }

    nColonne--;
}

u_int DataStructure::getNColonne() const{
    return nColonne;
}

u_int DataStructure::getNRighe() const{
    return nRighe;
}

head DataStructure::getIntestazioneOriz() const{
    return intestazioneOriz;
}

head DataStructure::getIntestazioneVert() const{
    return intestazioneVert;
}

tab DataStructure::getDati() const{
    return dati;
}











