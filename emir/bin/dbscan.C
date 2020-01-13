#include "dbscan.h"
#include <algorithm>
#include <math.h>

/************************************************************//**
 * \file dbscan.C
 * \brief Archivo de definiciones de la clase Dbscan
 *
 * Implementación de los métodos de la clase Dbscan
 ****************************************************************/

using namespace std;

Dbscan::Dbscan() {
  resultList.clear();
  pointList.clear();
  visitList.clear();
  e = 86;
  minpt = 4;
}

void Dbscan::imprimir() {
  vector<Element>::iterator it = pointList.begin();
  for (it; it != pointList.end(); it++)
    cout << "(" << it->getx() << "," << it->gety() << ")" << endl;
}

void Dbscan :: setList(const set<Element> &lista) {
  for (set<Element>::iterator it = lista.begin(); it != lista.end(); it++)
    pointList.push_back(*it);
}

double Dbscan::getDistancia(const Element &p, const Element &q) {
  double dx = p.getx()-q.getx();
  double dy = p.gety()-q.gety();
  double distancia = sqrt(dx*dx+dy*dy);
  return distancia;
}

vector <Element> Dbscan::getVecinos(const Element &punto) {
  vector<Element> neig;
  neig.clear();
  vector<Element>::iterator it = pointList.begin();
  while (it != pointList.end()) {
    Element q = *it;
    if (getDistancia(punto,q) <= e)
      neig.push_back(q);
    it++;
  }
  return neig;
}

void Dbscan::start() {
  int index = 0;
  while (pointList.size() > index) {
    Element p = pointList[index];
    if (find(visitList.begin(), visitList.end(), p) == visitList.end()) {
      visitList.push_back(p);
      vecinos = getVecinos(p);
      if (vecinos.size() >= minpt) {
        int ind = 0;
        while (vecinos.size() > ind) {
          Element r = vecinos[ind];
          if (find(visitList.begin(), visitList.end(), r) == visitList.end()) {
            visitList.push_back(r);
            vector<Element> neig = getVecinos(r);
            if (neig.size() >= minpt) {
              vector<Element>::iterator it = neig.begin();
              for (it; it != neig.end(); it++)
                vecinos.push_back(*it);
            }
          }
          ind++;
        }
      }
      list<vector<Element> > aux;
      aux.clear();
      aux.push_back(vecinos);
      resultList.push_back(aux);
    }
    index++;
  }
}

void Dbscan :: estadisticas() {
  cout << "Entrada = " << pointList.size() << endl;
  cout << "Visitados = " << visitList.size() << endl;
  cout << "Listas totales = " << resultList.size() << endl;
  int clist = 0;
  vector<list<vector<Element> > >::iterator it = resultList.begin();
  for (it; it != resultList.end(); it++) { 
    clist++;
    int cel, cvec = 0;
    list<vector<Element> >::iterator l = it->begin();
    for (l; l != it->end(); l++) { 
      cvec++;
      vector<Element>::iterator v = l->begin(); 
      cel = 0;
      for (v; v != l->end(); v++) { 
        cel++;
      }
    }
    cout << "Lista " << clist << " contiene " << it->size() << " vector con " << cel << " elementos" << endl;
  }
}
