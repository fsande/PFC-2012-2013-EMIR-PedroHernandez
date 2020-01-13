#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <allegro.h>
#define USE_MATH_DEFINES
#include <math.h>

/************************************************************//**
 * \file element.h
 * \brief Archivo de cabeceras
 * Definición de las clases Element y CSU
 ****************************************************************/

using namespace std;

const double CERO    = 0;      /**< Constante de 0*/
const double PI      = M_PI;   /**< Constante de PI*/
const double PIMEDIO = PI/2;   /**< Constante de PI/2*/
const int ANCHO = 120;   /**< Mitad del ancho de la CSU*/
const int ALTO = 200;   /**< Mitad del alto de la CSU*/
const int CIEN = 100;   /**< Constante de 100*/
const double INF = 1000.0;   /**< Constante para calcular máximos*/
const double ALCANCE = 233.238;   /**< Radio de alcance de una CSU desde su centro a su vértice*/
const int ARRIBA = 1;   /**< Indica si se usa la parte superior de la barra*/
const int ABAJO = 0;   /**< Indica si se usa la parte inferior de la barra*/
const int PRECISION = 1000000;   /**< Precisión que queremos en los cálculos*/
// Constantes de las barras
const int NUM_BARRAS = 55;   /**< Numero de barras total de la CSU*/
const double ALTO_CSU = 400,   /**< ALto total de la CSU*/
             DIST_BARRAS = ALTO_CSU/NUM_BARRAS,   /**< Altura de una única barra*/
             BARRA1_3 = 2.42,   /**< Tercio de barra - para el beam switching*/
             BARRA2_3 = 4.84,   /**< 2/3 de barra - para el beam switching*/
             BORDE_INF_DEF = 0.1,   /**< Borde inferior mínimo*/
             BORDE_SUP_DEF = 7.17,   /**< Borde superior máximo*/
             BORDE_INF = 1.27,   /**< Borde inferior cuando queremos margen*/
             BORDE_SUP = 6.27;   /**< Borde superior cuando queremos margen*/
// Constantes de ordenación
const int MENORX = 0,   /**< Criterio de ordenación por menor X*/
          MAYORX = 1,   /**< Criterio de ordenación por mayor X*/
          MENORY = 2,   /**< Criterio de ordenación por menor Y*/
          MAYORY = 3,   /**< Criterio de ordenación por mayor Y*/
          PRIORI = 4,   /**< Criterio de ordenación por prioridades*/
          TAMPUN = 5;   /**< Criterio de ordenación por mayor número de elementos recogidos*/
// Constantes de colores para el dibujo
const int BLANCO = makecol(255,255,255);   /**< Constante para el color blanco*/
const int ROJO = makecol(255,0,0);   /**< Constante para el color rojo*/
const int AZUL = makecol(0,0,255);   /**< Constante para el color azul*/
const int VERDE = makecol(0,255,0);   /**< Constante para el color verde*/
const int AMARI = makecol(255,255,0);   /**< Constante para el color amarillo*/
const int AQUA = makecol(0,255,255);   /**< Constante para el color aguamarina*/
/****************************************************************/

#ifndef CLASSCONFIG
#define CLASSCONFIG

/**************************************************************************//**
 * \class Config
 * \brief Clase de configuracion que guarda las opciones elegidas por el usuario
 ******************************************************************************/
class Config {
  public:
    bool dbscan, /**< indica si se quiere utilizar el algoritmo DBSCAN previamente*/
         grasp, /**< indica si se quiere intentar mejorar el resultado con la heurística GRASP*/
         verbose, /**< activa la salida de detalles de funcionamiento en un fichero de texto
                   * llamado "verbose.txt". Tiene fines de depuración*/
         grafico, /**< activa el paso a paso gráfico. Una muestra de lo que está haciendo
                   * la aplicación durante su análisis. Ralentiza mucho la ejecución*/
         beamswitching, /**< indica que se quiere utilizar la técnica del beam switching a
                         * la hora de realizar mediciones.*/
         noborder, /**< indica que los puntos han de estar a un arcseg de distancia
                    * respecto a los bordes. Estos son los bordes a lo ancho de la CSU*/
         tipodat; /**< indica si se quiere la salida en texto plano de 3 columnas o en XML*/
    int ancho, /**< ancho de la ventana gráfica*/
        alto, /**< alto de la ventana gráfica*/
        rotaciones; /**< indica el número de rotaciones iniciales que puede hacer una CSU
                     * en su búsqueda de elementos*/

    /************************************************************//**
     * \fn Config();
     * \brief Construye una configuración con valores predeterminados
     ****************************************************************/
    Config () {
      dbscan = verbose = grafico = grasp = beamswitching = noborder = tipodat = false;
      ancho = alto = 900;
      rotaciones = 20;
    }

    /************************************************************//**
     * \fn void operator = (const Config &c);
     * \brief Sobrecarga del operador "igual" entre dos archivos de
     * configuracion.
     * 
     * Establece una copia entre ambos.
     * \param c Configuración a copiar.
     ****************************************************************/
    void operator = (const Config &c) {
      dbscan = c.dbscan;
      grasp = c.grasp;
      verbose = c.verbose;
      grafico = c.grafico;
      ancho = c.ancho;
      alto = c.alto;
      rotaciones = c.rotaciones;
      beamswitching = c.beamswitching;
      noborder = c.noborder;
      tipodat = c.tipodat;
    }
};
#endif

/************************************************************//**
 * \class Element
 * \brief Un elemento es un punto que se desea observar en el espacio
 ****************************************************************/

class Element {
  static int orden, identificador;
  static Config conf;
  int id, /**< Identificador único de cada elemento */
      prioridad, /**< Prioridad para ser visualizado, 1 más importante, 99 menos importante */
      barra; /**< Barra del apuntado en la que se encuentra el punto */
  double x, /**< Posición en el eje X donde se encuentra el punto */
         y, /**< Posición en el eje Y donde se encuentra el punto */ 
         dist, /**< Distancia respecto al extremo de la barra */
         zona; /**< Zona en la que se situa dentro de la barra */
  public:
    /************************************************************//**
     * \fn Element(double posx, double posy, int pri);
     * \brief Constructor de un elemento con valores determinados
     * \param posx Posición en el eje X
     * \param posy Posición en el eje Y
     * \param pri Prioridad del elemento (1 muy importante - 99 no importante)
     ****************************************************************/
    Element(double posx, double posy, int pri);

    /************************************************************//**
     * \fn Element();
     * \brief Constructor por defecto.
     *
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
     * \brief Setter de la distancia del Elemento
     *
     * Distancia a la que se encuentra el punto respecto al extremo izquierdo
     * de la barra.
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
     *
     *        Elige el de mayor prioridad, y el que se encuentre más
     *        a la izquierda en caso de prioridades iguales
     * \param element Punto con el que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator < (const Element &element) const;

    /************************************************************//**
     * \fn bool operator == (const Element &element) const;
     * \brief Sobrecarga del operador "igual que" entre dos puntos.i
     *
     *        Se consideran iguales si tienen el mismo identificador.
     * \param element Punto con el que se compara.
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator == (const Element &element) const;

    /************************************************************//**
     * \fn void setorder (const int &i);
     * \brief Define la manera en la que se ordenan los elementos
     *
     * A elegir entre: MENORX, MAYORX, MENORY, MAYORY y PRIORI
     * \param i Opción elegida 
     ****************************************************************/
    void setorder (const int &i) {orden = i;}

    /************************************************************//**
     * \fn void configurar (const Config &c);
     * \brief Establece las opciones de configuración
     *
     * Este atributo es común a todas las instancias de la clase.
     * \param c Objeto de configuración
     ****************************************************************/
    void configurar (const Config &c) {conf = c;}

    /************************************************************//**
     * \fn void setzona(const double &z);
     * \brief Setter de la zona en la que se ubica un elemento dentro de la barra.
     * \param z Distancia entre 0 y DIST_BARRAS en la que se sitúa.
     ****************************************************************/
    void setzona(const double &z) {zona = z;}

    /************************************************************//**
     * \fn double getzona() const;
     * \brief Getter de la zona en la que se ubica un elemento dentro de la barra.
     * \param - No necesita argumentos
     * \return Devuelve la zona del elemento.
     ****************************************************************/
    double getzona() const {return zona;}
};

/************************************************************//**
 * \class CSU
 * \brief Clase que representa a un apuntado de CSU
 ****************************************************************/

class CSU {
  static int orden, identificador;
  static Config conf;
  int id, prior, orientacion;
  double x, y, alfa;
  set<Element> puntos;
  double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, ma, mb;
  bool barras_ocupadas [NUM_BARRAS];
  double distancia_punto [NUM_BARRAS]; 
  //para las mejoras horizontale
  double dist_min, dist_max;
  //Para el manejo de las barras
  double margenUp, margenDown, limiteS, limiteI;

  /************************************************************//**
   * \fn void extremos();
   * \brief Método para calcular los vértices del apuntado
   * \param - No necesita argumentos
   ****************************************************************/
  void extremos();

  /************************************************************//**
   * \fn void comprobacion();
   * \brief Método para comprobar que los Element de la CSU siguen estando en su
   * sitio tras haber hecho movimientos. 
   * 
   * Crea una nueva CSU en las mismas condiciones que su gemela e intenta meter
   * meter los puntos de la una en la otra. En teoría todos caben perfectametne,
   * aunque a veces por cuestiones de redondeo y en el orden de 10^-12 puede decir 
   * que un punto no puede ir dentro, pero son situaciones controladas que se sabe
   * que no es así.
   * \param - No necesita argumentos
   ****************************************************************/
  void comprobacion() const;

  /************************************************************//**
   * \fn  testeo(const Element &p, double &new_x, double &new_y) const;
   * \brief Función que calcula el punto de intersección entre la recta formada
   * por los vértices A y D de la CSU (lado izquierdo) y el elemento p
   * \param p Elemento de referencia
   * \param new_x Devuelve el valor en el eje X del punto de intersección
   * \param new_y Devuelve el valor en el eje Y del punto de intersección
   ****************************************************************/
  void testeo(const Element &p, double &new_x, double &new_y) const;

  /************************************************************//**
   * \fn void actualizar(const int &b);
   * \brief Actualiza la CSU tras un movimiento
   * 
   * Esta funcion es llamada tras un cambio en el centro de la CSU debido
   * a un movimiento de mejora; se encarga de comprobar que todos los elementos
   * contenidos en ella se encuentren donde deben y recalcula las distancias de
   * los mismos para su posterior utilización
   * \param b Número de barras que ha sido movido, 0 en movimientos laterales
   ****************************************************************/
  void actualizar(const int &b);

  /************************************************************//**
   * \fn void actualizar2(int move);
   * \brief Actualiza la CSU tras un movimiento
   *
   * Esta funcion es llamada tras un cambio en el centro de la CSU debido
   * a un movimiento de reajuste; se encarga de comprobar que todos los
   * elementos contenidos en ella se encuentren donde deben y recalcula tanto
   * las distancias de los elementos como los márgenes de la CSU para su
   * posterior utilización.
   * \param - no requiere argumentos 
   ****************************************************************/
  void actualizar2(/*int move, double a_mover, const int &pid*/);

  /************************************************************//**
   * \fn int p_potencial(const double &rango, int &barra) const;
   * \brief Comprueba si un punto que en teoría es descartado como "dentro" de
   * la CSU es una opción potencial para estarlo.
   *
   * Devuelve 0 si el punto no entra en la CSU, 2 si está demasiado
   * arriba y cabe en esa barra, 3 si está muy arriba y hay que cambiarlo a la
   * siguiente barra, 4 si está muy abajo y lo queremos pasar a la barra
   * inferior y 5 en el caso de que esté demasiado abajo y quepa en esa barra
   * \param rango Zona de la barra en la que se encuentra
   * \param barra Barra en la que se encuentra, puede variar a donde irá el
   * punto en caso de moverse la CSU (+/-1 barra)
   * \return Valor entre 0 y 5
   ****************************************************************/
  int p_potencial(const double &rango, int &barra) const;

    /************************************************************//**
     * \fn bool estaDentro2(const Element &p) const;
     * \brief Determina si un punto está dentro de la CSU mirando
     *        sus aristas y la posición del punto respecto a éstas.
     * \param p Punto a comprobar.
     * \return True si está dentro, false si no.
     ****************************************************************/
    bool estaDentro2(const Element &p) const;

  public:
    /************************************************************//**
     * \fn CSU (double posx, double posy, double angulo, int ori = ARRIBA);
     * \brief Constructor para valores determinados.
     * \param posx Posición horizontal del centro del apuntado.
     * \param posy Posición vertical del centro del apuntado.
     * \param angulo Orientación en radianes del apuntado.
     * \param ori Orientación de las barras para el beam switching
     ****************************************************************/
    CSU (double posx, double posy, double angulo, int ori = ARRIBA);

    /************************************************************//**
     * \fn CSU (const CSU &c);
     * \brief Constructor de copia.
     *
     * Este constructor crea una copia de otro apuntado.
     * \param c Apuntado a copiar.
     ****************************************************************/
    CSU (const CSU &c); 

    /************************************************************//**
     * \fn CSU ()
     * \brief Constructor por defecto.
     *
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
     *
     *        Elige el de mayor prioridad, y el que se encuentre más
     *        a la izquierda en caso de prioridades iguales.
     * \param apuntado CSU con la que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator < (const CSU &apuntado) const;

    /************************************************************//**
     * \fn bool operator == (const CSU &apuntado) const;
     * \brief Sobrecarga del operador "igual que" entre dos apuntados.
     *
     *        Se consideran iguales si tienen el mismo centro y ángulo.
     * \param apuntado CSU con la que hace la comparación
     * \return Devuelve el resultado de la comparación
     ****************************************************************/
    bool operator == (const CSU &apuntado) const;

    /************************************************************//**
     * \fn void operator = (const CSU &apuntado) const;
     * \brief Sobrecarga del operador "igual" entre dos apuntados.
     *
     *        Establece una copia entre ambos apuntados.
     * \param apuntado CSU a copiar.
     ****************************************************************/
    void operator = (const CSU &apuntado);

    /************************************************************//**
     * \fn void imprimir() const
     * \brief Muestra en la consola la posicion del apuntado.
     * \param - No necesita argumentos
     ****************************************************************/
    void imprimir() const {
      cout << "Apuntado["<<id<<"]=("<<x<<","<<y<<","<<alfa<<")"<<endl;
    }

    /************************************************************//**
     * \fn bool estaDentro(const Element &p, int &distancia) const;
     * \brief Método que mira si un punto está dentro de la CSU mirando
     *        que la barra que ocupa no esté ya ocupada.
     * \param p Punto a comprobar.
     * \param barra Barra sobre la que sería ubicado el punto.
     * \param distancia Distancia del punto respecto al borde de la CSU.
     * \param rango Zona en la que se encuentra dentro de la barra
     * \return 1 si está dentro, 0 si no. 2 si podría estarlo
     * \sa estaDentro2() p_potencial()
     ****************************************************************/
    int estaDentro(const Element &p, int &barra, double &distancia, double &rango) const;

    /************************************************************//**
     * \fn void mejoraArriba();
     * \brief Realiza una mejora ascendente
     * 
     * Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en la barra
     *        superior, desplazándolos todos hacia "arriba".
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraArriba();

    /************************************************************//**
     * \fn void mejoraAbajo();
     * \brief Realiza una mejora descendente
     * 
     * Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en la barra
     *        inferior, desplazándolos todos hacia "abajo".
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraAbajo();

    /************************************************************//**
     * \fn void mejoraIzquierda();
     * \brief Realiza una mejora lateral
     * 
     * Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en el extremo
     *        izquiero de una barra, desplazándolos todos hacia la izquierda
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraIzquierda();

    /************************************************************//**
     * \fn void mejoraDerecha();
     * \brief Realiza una mejora lateral
     * 
     * Función para modificar la posición de la CSU con el objetivo
     *        de que quepan más puntos en su interior.
     *        Procura situar un punto de los que ya contiene en el extremo
     *        derecho de una barra, desplazándolos todos hacia la derecha
     * \param - No necesita argumentos
     ****************************************************************/
    void mejoraDerecha();

    /************************************************************//**
     * \fn bool colision (const CSU &csu) const;
     * \brief Método para determinar si una CSU colisiona con otra dada.
     *
     * Si sus centros están demasiado cerca, se considera que hay colisión, 
     * proyectamos cada vértice de la segunda CSU con el lado vertical (izq) de
     * la primera y si sus máximos y mínimos no colisionan, no hay colision, si
     * no, proyectamos respecto al lado horizontal en busca de lo mismo. Si
     * existe alguna colisión, comprobamos si los puntos de uno podrían estar
     * dentro de la otra, en ese caso existe colisión.
     * \param csu La CSU con la que vamos a comparar
     * \return True si hay colisión, False si no
     ****************************************************************/
    bool colision (const CSU &csu) const;

    /************************************************************//**
     * \fn void inline friend operator << (ofstream &fich, const CSU apunt)
     * \brief  Sobrecarga del operador << para escribir en un fichero
     *
     * Escribe la configuración final del apuntado. Si la opcion tipodat está
     *         activada, se guarda en tres columnas x y alfa y a continuación la
     *         configuración de cada una de las barras. En caso contrario, se
     *         guarda en formato XML.
     * \param fich Fichero en el que escribir
     * \param apunt Apuntado a escribir
     ****************************************************************/
    void inline friend operator << (ofstream &fich, const CSU apunt) {
      if (!conf.tipodat) {
        fich << "<Apuntado>" << endl;
        fich << "\t<X>" << apunt.getx() << "</X>" << endl;
        fich << "\t<Y>" << apunt.gety() << "</Y>" << endl;
        fich << "\t<PA>" << apunt.getalfa() << "</PA>" << endl;
        fich << "\t<Configuracion>" << endl;
        for (int i = 0; i < NUM_BARRAS; i++) {
          fich << "\t\t<Barra>";
          if (!apunt.getBarra(i))
            fich << "0.0000";
          else 
            fich << apunt.getDist(i)-ANCHO;
          fich << "</Barra>" << endl;
        }
        fich << "\t</Configuracion>\n</Apuntado>" << endl;
      }
      else {
        fich << apunt.getx() << "\t" << apunt.gety() << "\t" << apunt.getalfa() << endl;
        for (int i = 0; i < NUM_BARRAS; i++) {
          fich << "\t"; 
          if (!apunt.getBarra(i))
            fich << "0.0000"<< endl;
          else 
            fich << apunt.getDist(i)-ANCHO << endl;
        }
      }
    }

    /************************************************************//**
     * \fn void setorder (const int &i);
     * \brief Setter del criterio de ordenación entre CSUs. 
     *
     * A elegir entre:
     * MENORX, MAYORX, MENORY, MAYORY, PRIORI y TAMPUN (con más puntos primero)
     * \param i Opción elegida
     ****************************************************************/
    void setorder (const int &i) {orden = i;}

    /************************************************************//**
     * \fn void setorient (const int &i); 
     * \brief Setter de la orientación de la CSU. 
     *
     * Esta orientación indica qué lado de la barra es válido cuando se
     * hace el beam switching. De forma general se ha
     * visto que funciona mejor utilizar el lado superior de las barras.
     * \param i Elección, a ser ARRIBA o ABAJO
     ****************************************************************/
    void setorient (const int &i);

    /************************************************************//**
     * \fn void getABCD(double ar[]) const;
     * \brief Este método devuelve los vértices de la CSU
     * \param ar Contenedor de los vértices
     ****************************************************************/
    void getABCD(double ar[]) const;

    /************************************************************//**
     * \fn void configurar (const Config &c);
     * \brief Establece las opciones de configuración
     *
     * Este atributo es común a todas las instancias de la clase.
     * \param c Objeto de configuración
     ****************************************************************/
    void configurar (const Config &c) {conf = c;}

    /************************************************************//**
     * \fn double getpendiente() const;
     * \brief Getter de la pendiente de la recta formada por los vértices AD
     * \param - No requiere parámetros
     * \return Pendiente de la recta
     ****************************************************************/
    double getpendiente() const {return ma;}

    /************************************************************//**
     * \fn void mostrar(BITMAP* bmp, int color) const;
     * \brief Dibuja la CSU
     *
     * Método para dibujar por pantalla un rectángulo que representa a la
     * CSU. Está formado por la unión de sus vértices, 55 barras situadas a lo
     * ancho del rectángulo y los puntos que contiene.
     * \param bmp Imagen donde se va a dibujar el apuntado.
     * \param color Color con el que se va a dibujar. Si se omite se pune uno al
     * azar.
     ****************************************************************/
    void mostrar(BITMAP* bmp, int color = makecol(rand() % 256, rand() % 256, rand() % 256)) const;

    /************************************************************//**
     * \fn void pointAddMove(Element &p, const int &move);
     * \brief Introduce en punto moviendo la CSU
     * 
     * Esta función mueve la CSU lo justo y necesario para meter un punto
     * que por poca distancia vertical no entra en alguna de las barras. Tiene
     * unos márgenes para decidir cuánto puede moverse sin perder un punto. Una
     * vez movida e insertado el punto, actualiza los demás.
     * \param p Elemento a insertar
     * \param move Situación en la que se encuentra, siendo 2 si está demasiado
     * arriba y cabe en esa barra, 3 si está muy arriba y hay que cambiarlo a la
     * siguiente barra, 4 si está muy abajo y lo queremos pasar a la barra
     * inferior y 5 en el caso de que esté demasiado abajo y quepa en esa barra
     ****************************************************************/
    void pointAddMove(Element &p, const int &move);
};

#endif

