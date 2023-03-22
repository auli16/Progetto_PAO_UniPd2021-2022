#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <vector>
#include <string>
#include <iostream>

//per salvataggio in file json
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>

using std::string;
using std::vector;
using std::cout;
using std::endl;

using tab = vector<vector<double>>;
using u_int = unsigned int;
using head = vector<string>;

class DataStructure{
private:
    u_int nRighe;
    u_int nColonne;
    tab dati;
    head intestazioneOriz;
    head intestazioneVert;

public:

    DataStructure(u_int, u_int, tab, head, head);
    DataStructure();
    DataStructure(const DataStructure&);
    virtual ~DataStructure() = default;

    u_int size() const; //grandezza della tabella
    double max() const; //ritorna il valore massimo presente all`interno della tabella
    double min() const; //ritorna il valore minimo presente all`interno della tabella
    double maxCol(u_int) const; //ritorna il valore massimo presente all`interno di una determinata colonna
    double minCol(u_int) const; //ritorna il valore massimo presente all`interno di una determinata colonna

    void stampaDataStructure() const;

    //operazioni di sostituzione
    string modIntestazioneVert(string, u_int); //modifica una cella dell`intestazione verticale e ritorna il valore sostituito
    string modIntestazioneOriz(string, u_int); //modifica una cella dell`intestazione orizzontale e ritorna il valore sostituito
    double modCella(u_int, u_int, double); //modifica un valore numerico e ritorna il valore sostituito

    //operazioni di modifica della struttura
    void addRows(u_int =1); //aggiugne n righe dopo l`ultima riga
    void addColumns(u_int =1); //aggiunge n colonne in dopo l`ultima colonna
    void insertRows(u_int =0, u_int=1); //aggiunge q righe a partire dalla posizione n
    void insertColumns(u_int =0, u_int=1); //aggiunge q colonne a partire dalla posizione n
    void delRow(u_int); //cancella la riga in posizione n
    void delColumn(u_int); //cancella la colonna in posizione n

    //get
    u_int getNColonne() const;
    u_int getNRighe() const;
    head getIntestazioneOriz() const;
    head getIntestazioneVert() const;
    tab getDati() const;


};

#endif // DATASTRUCTURE_H
