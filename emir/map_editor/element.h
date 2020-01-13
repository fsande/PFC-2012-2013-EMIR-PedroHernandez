#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <allegro.h>

/************************************************************//**
 * \file element.h
 * \brief Archivo de cabeceras
 * Definición de las clases Element y CSU
 ****************************************************************/

using namespace std;

const double CERO    = 0;
const double PIMEDIO = 3.14159265/2;
const double PI      = 3.14159265;
const double T3PIMED = 3*PIMEDIO;
const double DIST_BARRAS = 7.2727;
const int NUM_BARRAS = 55;
const int ANCHO = 120;
const int ALTO = 200;
const int CIEN = 100;
const double INF = 1000.0;
const double ALCANCE = 233.238;

/****************************************************************
 * Constantes de ordenación
 ****************************************************************/
const int MENORX = 0,
          MAYORX = 1,
          MENORY = 2,
          MAYORY = 3,
          PRIORI = 4,
          TAMPUN = 5;
/****************************************************************/

#ifndef CLASSCONFIG
#define CLASSCONFIG

class Config {
  public:
    bool dbscan, grasp, verbose, grafico;
    int ancho, alto, rotaciones;
    Config () {
      dbscan = verbose = grafico = false;
      grasp = true;
      ancho = alto = 900;
      rotaciones = 20;
    }
    void operator = (const Config &c) {
      dbscan = c.dbscan;
      grasp = c.grasp;
      verbose = c.verbose;
      grafico = c.grafico;
      ancho = c.ancho;
      alto = c.alto;
      rotaciones = c.rotaciones;
    }
};
#endif

//class CSU;

/************************************************************//**
 * \class Element
 * \brief Un elemento es un punto que se desea observar en el espacio
 ****************************************************************/

class Element {
  static int orden, identificador;
  int id, /**< Identificador único de cada elemento */
      prioridad, /**< Prioridad para ser visualizado, 1 más importante, 99 menos importante */
      barra; /**< Barra del apuntado en la que se encuentra el punto */
  double x, /**< Posición en el eje X donde se encuentra el punto */
         y, /**< Posición en el eje Y donde se encuentra el punto */ 
         dist; /**< Distancia respecto al extremo de la barra */
  public:
    static Config conf;
    /************************************************************//**
     * \fn Element(int ident, double posx, double posy, int pri);
     * \brief Constructor de un elemento con valores determinados
     * \param ident Identificador del punto
     * \param posx Posición en el eje X
     * \param posy Posición en el eje Y
     * \param pri Prioridad del elemento (1 muy importante - 99 no importante)
     ****************************************************************/
    Element(double posx, double posy, int pri);
    /************************************************************//**
     * \fn Element();
     * \brief Constructor por defecto.
     * Este constructor crea un elemento vacío
     * \param - No se le pasan parametros.
     ****************************************************************/
    Element() {}
    /************************************************************//**
     * \fn setid(const int &i); 
     * \brief Setter del identificador del punto
     * \param i Nuevo valor del infentificador
     ****************************************************************/
    void setid(const int &i) {id = i;}
    /************************************************************//**
     * \fn int getid() const;
     * \brief Getter del identificador de punto
     * \param - No necesita argumentos
     * \return Devuelve el valor del identificador
     ****************************************************************/
    int getid() const {return id;}
    /************************************************************//**
     * \fn void setx(const double &i);
     * \brief Setter de la posición horizontal
     * \param i Nueva posición en el eje X
     ****************************************************************/
    void setx(const double &i) {x = i;}
    /************************************************************//**
     * \fn double getx() const;
     * \brief Getter de la posición horizontal
     * \param - No necesita argumentos
     * \return Devuelve el valor de la posición en el eje X
     ****************************************************************/
    double getx() const {return x;}
    /************************************************************//**
     * \fn void sety(const double &i);
     * \brief Setter de la posición vertical
     * \param i Nueva posición en el eje Y
     ****************************************************************/
    void sety(const double &i) {y = i;}
    /************************************************************//**
     * \fn double gety() const;
     * \brief Getter de la posición vertical
     * \param - No necesita argumentos
     * \return Devuelve el valor de la posición en el eje Y
     ****************************************************************/
    double gety() const {return y;}
    /************************************************************//**
     * \fn void setprio(const int &i);
     * \brief Setter de la prioridad
     * \param i Nueva prioridad del punto
     ****************************************************************/
    void setprio(const int &i) {prioridad = i;}
    /************************************************************//**
     * \fn int getprior() const;
     * \brief Getter de la prioridad
     * \param - No necesita argumentos
     * \return Devuelve el valor de la prioridad
     ****************************************************************/
    int getprior() const {return prioridad;}
    /************************************************************//**
     * \fn void setbarra(int b);
     * \brief Setter de la barra en la que se encuentra el punto.
     * \param b Nuevo valor de la barra.
     ****************************************************************/
    void setbarra(int b) {barra = b;}
    /************************************************************//**
     * \fn int getbarra() const;
     * \brief Getter de la barra en la que se encuentra el punto.
     * \param - No necesita argumentos.
     * \return Devuelve el valor de la barra.
     ****************************************************************/
    int getbarra() const {return barra;}
    /************************************************************//**
     * \fn void setdist(double d);
     * \brief Setter de la distancia a la que se encuentra el punto
     *        respecto al extremo izquierdo de la barra.
     * \param d Nuevo valor de la distancia.
     ****************************************************************/
    void setdist(double d) {dist = d;}
    /************************************************************//**
     * \fn double getdist() const;
     * \brief Getter de la distancia del punto.
     * \param - No necesita argumentos.
     * \return Devuelve la distancia.
     ****************************************************************/
    double getdist() const {return dist;}
    /************************************************************//**
     * \fn void clear();
     * \brief Función que reestablece los valores por defecto del punto
     * \param - No necesita argumentos
     ****************************************************************/
    void clear();
    /************************************************************//**
     * \fn void imprimir() const;
     * \brief Muestra en la consola la posicion del punto
     * \param - No necesita argumentos
     ****************************************************************/
    void imprimir() const{
      cout << "Punto["<<id<<"]=("<<x<<","<<y<<")"<<endl;
    }
    /************************************************************//**
     * \fn bool operator < (const Element &element) const;
     * \brief Sobrecarga del operador "menor que" entre puntos.
     *        Elige el de mayor prioridad, y el que se encuentre más
     *        a la izquierda en caso de prioridades iguales
     * \param element Punto con el que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator < (const Element &element) const;
    /************************************************************//**
     * \fn bool operator == (const Element &element) const;
     * \brief Sobrecarga del operador "igual que" entre dos puntos.
     *        Se consideran iguales si tienen el mismo identificador.
     * \param element Punto con el que se compara.
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator == (const Element &element) const;

    void setorder (const int &i) {orden = i;}
};

/************************************************************//**
 * \class CSU
 * \brief Clase que representa a un apuntado de CSU
 ****************************************************************/

class CSU {
  static int orden, identificador;
  int id, prior;
  double x, y, alfa;
  set<Element> puntos;
  double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, ma, mb;
  bool barras_ocupadas [NUM_BARRAS];
  double distancia_punto [NUM_BARRAS];
  double dist_min, dist_max;
  double minx, maxx, miny, maxy;
  /************************************************************//**
   * \fn void extremos();
   * \brief Método para calcular los vértices del apuntado
   * \param - No necesita argumentos
   ****************************************************************/
  void extremos();

  public:
    static Config conf;
    /************************************************************//**
     * \fn CSU (int ident, double posx, double posy, double angulo); 
     * \brief Constructor para valores determinados.
     * \param ident Identificador del apuntado.
     * \param posx Posición horizontal del centro del apuntado.
     * \param posy Posición vertical del centro del apuntado.
     * \param angulo Orientación en radianes del apuntado.
     ****************************************************************/
    CSU (double posx, double posy, double angulo);
    /************************************************************//**
     * \fn CSU (const CSU &c);
     * \brief Constructor de copia.
     * Este constructor crea una copia de otro apuntado.
     * \param c Apuntado a copiar.
     ****************************************************************/
    CSU (const CSU &c); 
    /************************************************************//**
     * \fn CSU ()
     * \brief Constructor por defecto.
     * Este constructor crea un elemento vacío
     * \param - No se le pasan parametros.
     ****************************************************************/
    CSU () {}
    /************************************************************//**
     * \fn void setid(const int &i)
     * \brief Setter del identificador del apuntado.
     * \param i Nuevo valor del infentificador
     ****************************************************************/
    void setid(const int &i) {id = i;}
    /************************************************************//**
     * \fn int getid() const 
     * \brief Getter del identificador del apuntado.
     * \param - No necesita argumentos
     * \return Devuelve el valor del identificador
     ****************************************************************/
    int getid() const {return id;}
    /************************************************************//**
     * \fn void setx(const double &i) 
     * \brief Setter de la posición horizontal
     * \param i Nueva posición en el eje X
     ****************************************************************/
    void setx(const double &i) {x = i;}
    /************************************************************//**
     * \fn double getx() const
     * \brief Getter de la posición horizontal
     * \param - No necesita argumentos
     * \return Devuelve el valor de la posición en el eje X
     ****************************************************************/
    double getx() const {return x;}
    /************************************************************//**
     * \fn void sety(const double &i)
     * \brief Setter de la posición vertical
     * \param i Nueva posición en el eje Y
     ****************************************************************/
    void sety(const double &i) {y = i;}
    /************************************************************//**
     * \fn double gety() const
     * \brief Getter de la posición vertical
     * \param - No necesita argumentos
     * \return Devuelve el valor de la posición en el eje Y
     ****************************************************************/
    double gety() const {return y;}
    /************************************************************//**
     * \fn void setalfa(const double &i)
     * \brief Setter del ángulo de orientación.
     * \param i Nueva valor del ángulo.
     ****************************************************************/
    void setalfa(const double &i) {alfa = i; extremos();}
    /************************************************************//**
     * \fn double getalfa() const
     * \brief Getter del ángulo de orientación.
     * \param - No necesita argumentos
     * \return Devuelve el valor del ángulo.
     ****************************************************************/
    double getalfa() const {return alfa;}
    /************************************************************//**
     * \fn void setprio(const int &i)
     * \brief Setter de la prioridad
     * \param i Nueva prioridad del punto
     ****************************************************************/
    void setprio(const int &i) {prior = i;}
    /************************************************************//**
     * \fn int getprior() const
     * \brief Getter de la prioridad
     * \param - No necesita argumentos
     * \return Devuelve el valor de la prioridad
     ****************************************************************/
    int getprior() const {return prior;}
    /************************************************************//**
     * \fn bool empty() const
     * \brief Método para saber si el apuntado tiene elementos o no
     * \param - No necesita argumentos
     * \return True si está vacío, false en caso contrario
     ****************************************************************/
    bool empty() const {return puntos.empty();}
    /************************************************************//**
     * \fn int size() const
     * \brief Devuelve el número de puntos que contiene
     * \param - No necesita argumentos
     * \return Número de puntos.
     ****************************************************************/
    int size() const {return puntos.size();}
    /************************************************************//**
     * \fn double getMinD() const;
     * \brief Devuelve la menor distancia entre los puntos y el extremo
              izquierdo del apuntado
     * \param - No necesita argumentos
     * \return Distancia mínima.
     ****************************************************************/
    double getMinD() const {return dist_min;}
    /************************************************************//**
     * \fn double getMaxD() const;
     * \brief Devuelve la mayor distancia entre los puntos y el extremo
              izquierdo del apuntado
     * \param - No necesita argumentos
     * \return Distancia máxima.
     ****************************************************************/
    double getMaxD() const {return dist_max;}
    /************************************************************//**
     * \fn void clear();
     * \brief Función que reestablece los valores por defecto del 
     *        apuntado, eliminando los puntos que contiene.
     * \param - No necesita argumentos
     ****************************************************************/
    void clear();
    /************************************************************//**
     * \fn void pointAdd(Element p);
     * \brief Método para añadir un elemento al apuntado.
     * \param p Punto a añadir.
     ****************************************************************/
    void pointAdd(Element p);
    /************************************************************//**
     * \fn void pointAdd(vector<Element> lista);
     * \brief Método para añadir una lista de puntos al apuntado.
     * \param lista Lista de puntos a añadir.
     ****************************************************************/
    void pointAdd(vector<Element> lista);
    /************************************************************//**
     * \fn set<Element> getPoints() const
     * \brief Método para obtener todos los puntos del apuntado.
     * \param - No necesita argumentos
     * \return Devuelve un conjunto de puntos
     ****************************************************************/
    set<Element> getPoints() const {return puntos;}
    /************************************************************//**
     * \fn bool getBarra(const int &i) const;
     * \brief Método para saber si una barra está ocupada o no.
     * \param i Número de la barra que queremos mirar.
     * \return Devuelve si la barra está ocupada o no.
     ****************************************************************/
    bool getBarra(const int &i) const {return barras_ocupadas[i];}
    /************************************************************//**
     * \fn bool getDist(const int &i) const;
     * \brief Método para obtener la distancia a la que se encutra un punto
     *        respecto al extremo izquierdo de la barra.
     * \param i Número de la barra que queremos mirar.
     * \return Devuelve la distancia del punto.
     ****************************************************************/
    double getDist(const int &i) const {return distancia_punto[i];}
    /************************************************************//**
     * \fn bool operator < (const CSU &apuntado) const;
     * \brief Sobrecarga del operador "menor que" entre apuntados.
     *        Elige el de mayor prioridad, y el que se encuentre más
     *        a la izquierda en caso de prioridades iguales.
     * \param apuntado CSU con la que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator < (const CSU &apuntado) const;
    /************************************************************//**
     * \fn bool operator == (const CSU &apuntado) const;
     * \brief Sobrecarga del operador "igual que" entre dos apuntados.
     *        Se consideran iguales si tienen el mismo centro y ángulo.
     * \param apuntado CSU con la que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator == (const CSU &apuntado) const;
    /************************************************************//**
     * \fn void operator = (const CSU &apuntado) const;
     * \brief Sobrecarga del operador "igual" entre dos apuntados.
     *        Establece una copia entre ambos apuntados.
     * \param apuntado CSU a copiar.
     ****************************************************************/
    void operator = (const CSU &apuntado);
    /************************************************************//**
     * \fn void imprimir(BITMAP* bmp) const;
     * \brief Método para dibujar por pantalla un rectángulo que 
     *        representa a la CSU.
     * \param bmp Imagen donde se va a dibujar el apuntado.
     ****************************************************************/
    void imprimir(BITMAP* bmp) const;
    /************************************************************//**
     * \fn void imprimir() const
     * \brief Muestra en la consola la posicion del apuntado.
     * \param - No necesita argumentos
     ****************************************************************/
    void imprimir() const {
      cout << "Apuntado["<<id<<"]=("<<x<<","<<y<<","<<alfa<<")"<<endl;
    }
    /************************************************************//**
     * \fn bool estaDentro(const Element &p) const;
     * \brief Funcion a eliminar, tarda más que el resto
     * \param p Punto
     * \return True si está dentro, false si no.
     ****************************************************************/
    bool estaDentro(const Element &p) const;
    /************************************************************//**
     * \fn bool estaDentro2(const Element &p) const;
     * \brief Determina si un punto está dentro de la CSU mirando
     *        sus aristas y la posición del punto respecto a éstas.
     * \param p Punto a comprobar.
     * \return True si está dentro, false si no.
     * \sa estaDentro3()
     ****************************************************************/
    bool estaDentro2(const Element &p) const;
    /************************************************************//**
     * \fn bool estaDentro3(const Element &p, int &distancia) const;
     * \brief Método que mira si un punto está dentro de la CSU mirando
     *        que la barra que ocupa no esté ya ocupada.
     * \param p Punto a comprobar.
     * \param barra Barra sobre la que sería ubicado el punto.
     * \param distancia Distancia del punto respecto al borde de la CSU.
     * \return True si está dentro, false si no.
     * \sa estaDentro2()
     ****************************************************************/
    bool estaDentro3(const Element &p, int &barra, double &distancia) const;
    /************************************************************//**
     * \fn void mejoraArriba();
     * \brief Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en la barra
     *        superior, desplazándolos todos hacia "arriba".
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraArriba();
    /************************************************************//**
     * \fn void mejoraAbajo();
     * \brief Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en la barra
     *        inferior, desplazándolos todos hacia "abajo".
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraAbajo();
    /************************************************************//**
     * \fn void mejoraIzquierda();
     * \brief Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en el extremo
     *        izquiero de una barra, desplazándolos todos hacia la izquierda
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraIzquierda();
    /************************************************************//**
     * \fn void mejoraDerecha();
     * \brief Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en el extremo
     *        derecho de una barra, desplazándolos todos hacia la derecha
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraDerecha();
    /************************************************************//**
     *
     ****************************************************************/
    bool colision (const CSU &csu) const;
    /************************************************************//**
     * \fn void imp_estado() const 
     * \brief Función que muestra el estado actual de la CSU, dónde
     *        se encuentra y todos los puntos que tiene.
     * \param - No necesita argumentos
     ****************************************************************/
    void imp_estado() const {
      cout << "*******************************************" << endl;
      cout << "CSU: " << id << ": ("<<x<<","<<y<<"), "<<alfa<<endl;
      cout << "Puntos: ";
      if (puntos.empty())
        cout << "Vacío" << endl;
      for (set<Element>::iterator i = puntos.begin(); i != puntos.end(); i++)
        cout << i->getid() << " -> ";
      cout << endl;
      cout << "*******************************************" << endl;
    }
    /************************************************************//**
     * \fn void inline friend operator << (ofstream &fich, const CSU apunt)
     * \brief  Sobrecarga del operador << para escribir en un fichero la
     *         configuración final del apuntado.
     * \param fich Fichero en el que escribir
     * \param apunt Apuntado a escribir
     ****************************************************************/
    void inline friend operator << (ofstream &fich, const CSU apunt) {
      /*fich << "<Apuntado>" << endl;
      fich << "\t<X>" << apunt.getx() << "</X>" << endl;
      fich << "\t<Y>" << apunt.gety() << "</Y>" << endl;
      fich << "\t<PA>" << apunt.getalfa() << "</PA>" << endl;
      fich << "\t<Configuracion>" << endl;
      for () {
      }
      fich << "\t</Configuracion>\n</Apuntado>" << endl;*/
      fich << apunt.getx() << "\t" << apunt.gety() << "\t" << apunt.getalfa() << endl;
      for (int i = 0; i < NUM_BARRAS; i++) {
        fich << "\t"; 
        if (!apunt.getBarra(i))
          fich << "0.0000"<< endl;
        else 
          fich << apunt.getDist(i)-ANCHO << endl;
      }
    }
    void setorder (const int &i) {orden = i;}
    pair<double, double> getEjeX() const {pair<double, double> x(minx, maxx); return x;}
    pair<double, double> getEjeY() const {pair<double, double> y(miny, maxy); return y;}
    void getABCD(double ar[]) const {
      ar[0] = Ax;
      ar[1] = Ay;
      ar[2] = Bx;
      ar[3] = By;
      ar[4] = Cx;
      ar[5] = Cy;
      ar[6] = Dx;
      ar[7] = Dy;
    }
};

#endif

