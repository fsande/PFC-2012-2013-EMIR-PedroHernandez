#ifndef DBSCAN_H
#define DBSCAN_H

#include <iostream>
#include <vector>
#include <list>
#include "element.h"

/************************************************************//**
 * \file dbscan.h
 * \brief Archivo de cabeceras
 * Definición de la clase Dbscan
 ****************************************************************/

/************************************************************//**
 * \class Dbscan
 * \brief Clase que implementa el algoritmo del DBScan
 ****************************************************************/

class Dbscan { 

    int e, minpt;
    vector<list<vector<Element> > > resultList;
    vector<Element> pointList;
    vector<Element> vecinos;
    vector<Element> visitList;
    
    void imprimir();

  public:
    /************************************************************//**
     * \fn Dbscan();
     * \brief Constructor por defecto.
     * \param - No necesita argumentos.
     ****************************************************************/
    Dbscan();
    /************************************************************//**
     * \fn void setList(const vector<Element> &lista);
     * \brief Setter de los puntos que se van a tratar
     * \param lista Lista de elementos
     ****************************************************************/
    void setList(const set<Element> &lista);
    /************************************************************//**
     * \fn  vector<Element> getList() {return pointList;}
     * \brief Getter de los puntos tratados.
     * \param - No necesita argumentos
     * \return Lista de puntos.
     ****************************************************************/
    vector<Element> getList() {return pointList;}
    /************************************************************//**
     * \fn void start();
     * \brief Función que ejecuta el algortimo DBScan
     * \param - No necesita argumentos
     ****************************************************************/
    void start();
    /************************************************************//**
     * \fn vector<Element> getVecinos(const Element &punto);
     * \brief Método que devuelve aquellos puntos que cumplan la
     *        característica de vecindad
     * \param punto Punto del que queremos saber los vecinos.
     * \return Vector de puntos vecinos al punto.
     ****************************************************************/
    vector<Element> getVecinos(const Element &punto);
    /************************************************************//**
     * \fn double getDistancia(const Element &p, const Element &q);
     * \brief Función que mide la distancia entre dos puntos.
     * \param p Primer punto
     * \param q Segundo punto
     * \return Distancia entre los puntos p y q.
     ****************************************************************/
    double getDistancia(const Element &p, const Element &q);
    /************************************************************//**
     * \fn vector<list<vector<Element> > > getResult()
     * \brief Devuelve un vector de clusters, que a su vez contienen un
     *        vector de puntos que los componen.
     * \param - No necesita argumentos
     * \return Listado de clusters
     ****************************************************************/
    vector<list<vector<Element> > > getResult(){return resultList;}
    /************************************************************//**
     * \fn void estadisticas();
     * \brief Función para mostrar el estado de la clase por consola
     * \param - No necesita argumentos
     ****************************************************************/
    void estadisticas();
};

#endif
