#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <allegro.h>
#include <math.h>
#include <algorithm>
#include "parser.h"
#include "dbscan.h"
#include "mytime.h"

/************************************************************//**
 * \file main.C
 * \brief Archivo principal del proyecto - método main
 *
 * Conjunto de métodos que resuelven el problema a tratar (Proyecto
 * EMIR).
 ****************************************************************/

//#define TESTS

using namespace std;

const double MAX = 100000;
const double MIN = -1.0;
const double DIST = 0;
const string RUTA_RES = "../Resultados/";
const string linea = "------------------------------------------------------------\n";
const double DESP = 0; //distancia desde centro a región buena
const int ORI = ARRIBA;
const int ROT_MEJORA = 180;

ofstream fich("verbose.txt");
Config configuracion;

volatile int close_button_pressed = FALSE;
/***************************************************************************//**
 * \fn void close_button_handler(void)
 * \brief Permite el cierre de la ventana gráfica pulsando el botón X de cerrar
 ******************************************************************************/
void close_button_handler(void) {
  close_button_pressed = TRUE;
}

/***************************************************************************//**
 * \fn inline void progreso() 
 * \brief Muestra una barra mientras se ejecuta el programa
 *******************************************************************************/
inline void progreso() {
  static char barra = '|';
  switch (barra) {
    case '|': barra = '/';
      break;
    case '/': barra = '-';
      break;
    case '-': barra = '\\';
      break;
    case '\\': barra = '|';
      break;
  }
  cout << "\r[2K Working "<<barra;
}

/***************************************************************************//**
 * \fn int ayuda()
 * \brief Muestra cómo usar el programa y sus opciones por pantalla
 *******************************************************************************/
int ayuda() {
  cout << "Pointing optimizer program for Emir" << endl << endl;
  cout << "Usage: ./csuoptimizer [options] <input file>" << endl << endl;
  cout << "Available options:" << endl;
  cout << "--beams: activates beam switching (default is off)." << endl;
  cout << "--dat: Changes output format to .dat (default is XML)." << endl;
  cout << "--dbscan: Activates the use of DBScan cluster detection algorithm (default is off)." << endl;
  cout << "--grasp: Uses the GRASP heuristic to enhance the results (default is off)." << endl;
  cout << "--graphic: Activates graphic step by step execution for debugging purposes. It slows execution (default is off)." << endl;
  cout << "--noborder: Avoids objects in the border of the bars." << endl;
  cout << "-NR X: X stands for the number of CSU rotations to perform when searching. Default is 20." << endl;
  cout << "--verbose: Generates the 'verbose.txt' text file containing information related to the program execution." << endl << endl;
  cout << "The <input file> must be a XML file with this format:" << endl << endl;
  cout << "<Observables [widht=Ancho_cielo height=Alto_cielo]>" << endl;
  cout << "\t<Element id=\"Identificador\">" << endl;
  cout << "\t\t<x>PosX</x>" << endl;
  cout << "\t\t<y>PosY</y>" << endl;
  cout << "\t\t<Prioridad>[1..99]</Prioridad>" << endl;
  cout << "\t</Element>" << endl;
  cout << "\t  ···" << endl;
  cout << "</Observables>" << endl;
  cout << linea << endl << endl;
  return 0;
}

/***************************************************************************//**
 * \fn void pintarCores (BITMAP* bmp, vector<list<vector<Element> > > resultado)
 * \brief Dibuja la nube de puntos a tratar
 * \param bmp Imagen en la que se pinta
 * \param resultado Puntos a pintar
 *******************************************************************************/
// Función que dibuja los resultados por grupos de colores, cada color es un cluster diferente
void pintarCores (BITMAP* bmp, vector<list<vector<Element> > > resultado) {
  vector<list<vector<Element> > >::iterator it = resultado.begin();
  for (it; it != resultado.end(); it++) {
    list<vector<Element> >::iterator l = it->begin();
    int red = rand() % 256, green = rand() % 256, blue = rand() % 256;
    for (l; l != it->end(); l++) {
      vector<Element>::iterator v = l->begin();
      for (v; v != l->end(); v++) {
        Element p = *v;
        circlefill(bmp, p.getx(), bmp->h - p.gety(), 4, makecol(red,green,blue));
      }
    }
  }
}

/***************************************************************************//**
 * \fn void pintarCSU (BITMAP* bmp, const CSU &c, const int &centroX, const int &centroY, int color)
 * \brief Dibuja una CSU
 *
 * Esta función no llama a la función propia de la CSU para dibujar, puesto que
 * centra la imagen en un punto concreto.
 * \param bmp Imagen donde se dibuja
 * \param c CSU a dibujar
 * \param centroX Coordenada X del centro de la imagen
 * \param centroY Coordenada Y del centro de la imagen
 * \param color Color con el que se va a pintar, si no se especifica se pone uno
 * aleatorio.
 *******************************************************************************/
void pintarCSU (BITMAP* bmp, const CSU &c, const int &centroX, const int &centroY, int color = makecol(rand() % 256, rand() % 256, rand() % 256)) {
  double a[8];
  c.getABCD(a);
  line(bmp, a[0] - centroX, bmp->h-(a[1]-centroY), a[2] - centroX, bmp->h-(a[3]-centroY), color);
  line(bmp, a[2] - centroX, bmp->h-(a[3]-centroY), a[4] - centroX, bmp->h-(a[5]-centroY), color);
  line(bmp, a[4] - centroX, bmp->h-(a[5]-centroY), a[6] - centroX, bmp->h-(a[7]-centroY), color);
  line(bmp, a[6] - centroX, bmp->h-(a[7]-centroY), a[0] - centroX, bmp->h-(a[1]-centroY), color);
  set<Element> p = c.getPoints();
  for (set<Element>::iterator v = p.begin(); v != p.end(); v++)
    circlefill(bmp, v->getx() - centroX, bmp->h - (v->gety()-centroY), 4, color);
}

/***************************************************************************//**
 * \fn inline void rellenar_con_puntos (CSU &apunt, set<Element> puntos)
 * \brief Llena de puntos una CSU
 *
 * Se recorren todos los puntos y se comprueba uno por uno si están dentro de la
 * CSU. Puede pasar que el punto entre de forma directa o que haya que ajustar
 * la CSU para que entre. Ambos casos están contemplados y son realizados desde
 * aquí.
 * \param apunt CSU que queremos rellenar
 * \param puntos Lista de puntos a mirar
 *******************************************************************************/
// Funcion que recorre la lista de puntos y comprueba si están dentro de un determiando apuntado
inline void rellenar_con_puntos (CSU &apunt, set<Element> puntos) {
  static set<Element>::iterator s2;
  s2 = puntos.begin();
  while (s2 != puntos.end()) {
    static int barra, op;
    static double dist, zona;
    op = apunt.estaDentro(*s2, barra, dist, zona);
    if (op) {
      Element p = *s2;
      p.setbarra(barra);
      p.setdist(dist);
      p.setzona(zona);
      if (op == 1)
        apunt.pointAdd(p);
      else
        apunt.pointAddMove(p, op);
    }
    s2++;
  }
}

/***************************************************************************//**
 * \fn inline void eliminar_puntos (set<Element> lista, set<Element> &puntos, set<Element> &eliminados)
 * \brief Elimina una serie de puntos
 *
 * La función se encarga de eliminar de una lista total los puntos agrupados en 
 * una segunda lista. Se recorren los puntos de esa CSU, se buscan de la lista
 * total y se eliminan de la misma a la vez que se insertan en otra lista que
 * marca aquellos puntos que han sido eliminados.
 * \param lista Lista de puntos que se quieren borrar
 * \param puntos Conjunto de puntos total del que se quiere quitar elementos
 * \param eliminados Conjunto de puntos donde se insertan los eliminados
 *******************************************************************************/
// Funcion que elimina de la lista de puntos aquellos que se dan en una lista
inline void eliminar_puntos (set<Element> lista, set<Element> &puntos, set<Element> &eliminados) {
  static set<Element>::iterator s2, borrar;
  for (borrar = lista.begin(); borrar != lista.end(); borrar++) {
    s2 = puntos.begin();
    while (s2 != puntos.end())
      if (s2->getid() == borrar->getid())
        break;
      else
        s2++;
    eliminados.insert(*s2);
    puntos.erase(s2);
  }
}

/***************************************************************************//**
 * \fn inline void sort(set<Element> &cto,const int &opcion)
 * \brief Ordena Elementos según un criterio
 * \param cto Conjunto de puntos a ordenar
 * \param opcion Criterio de ordenación
 * \sa Element::setorder()
 *******************************************************************************/
inline void sort(set<Element> &cto,const int &opcion) {
  static Element p;
  p.setorder(opcion);
  static set<Element> aux;
  static set<Element>::iterator it;
  aux.clear();
  for (it = cto.begin(); it != cto.end(); it++) 
    aux.insert(*it);
  cto = aux;
}

/***************************************************************************//**
 * \fn inline void sort(set<CSU> &cto,const int &opcion)
 * \brief Ordena CSUs según un criterio
 * \param cto Conjunto de CSUs a ordenar
 * \param opcion Criterio de ordenación
 * \sa CSU::setorder()
 *******************************************************************************/
inline void sort(set<CSU> &cto,const int &opcion) {
  static CSU p;
  p.setorder(opcion);
  static set<CSU> aux;
  static set<CSU>::iterator it;
  aux.clear();
  for (it = cto.begin(); it != cto.end(); it++) 
    aux.insert(*it);
  cto = aux;
}

/***************************************************************************//**
 * \fn sacar_apuntados(set<Element> puntos)
 * \brief Encuentra apuntados de CSU que cubran todos los puntos
 *
 * El objetivo de esta función es cubrir todos los puntos que se le pasan
 * mediante apuntados. Para ello ordena los puntos de diferentes maneras, a fin
 * de conseguir el mejor resultado posible. Por cada ordenación, creamos tantas
 * CSUs como número de rotaciones indicado con centro en el primer punto de la
 * lista, y para cada una de ellas se maximiza el número de puntos que puede
 * tener mediante movimientos de mejora, esto es, mientras vayan cambiando el
 * número de elementos, mover arriba, abajo, a la izquierda y a la derecha. De
 * todas estas rotaciones, nos quedamos con la que más puntos abarca, y
 * continuamos con el siguiente punto. Al finalizar tenemos tantas listas como
 * criterios de ordenación, y elegimos aquella con menos apuntados.
 * \param puntos Conjunto de puntos a cubrir
 * \return Conjunto de CSUs que cubren todos los puntos
 *******************************************************************************/
set<CSU> sacar_apuntados(set<Element> puntos) {
  set<CSU> centros, vector[4];
  static set<Element> eliminados, actuales;
  static int min, ancho, alto;
  static BITMAP *bmp = create_bitmap(900, 900);
  static set<Element>::iterator it;
  sort(centros, TAMPUN);
  if (configuracion.grafico) {
    sort(puntos, MENORX);
    it = puntos.end();
    it--;
    ancho = (puntos.begin()->getx() + it->getx())/2 - 450;
    sort(puntos, MENORY);
    it = puntos.end();
    it--;
    alto = (puntos.begin()->gety() + it->gety())/2 - 450;
  }
  if (configuracion.verbose) {
    fich << linea << "Entramos en sacar_apuntados" << endl;
    fich << "mirando " << puntos.size() << " puntos" << endl;
  }
  for (int i = MENORX; i <= MAYORY; i++) {
    centros.clear();
    eliminados.clear();
    actuales = puntos;
    sort(actuales, i);
    while (!actuales.empty()) {
      static set<CSU> posibles;
      posibles.clear();
      Element p = *(actuales.begin());
      if (configuracion.grafico) {
        clear_bitmap(bmp);
        for(it = puntos.begin(); it != puntos.end(); it++)
          circlefill(bmp, it->getx() - ancho, bmp->h - (it->gety() - alto), 3, ROJO);
        for(it = actuales.begin(); it != actuales.end(); it++)
          circlefill(bmp, it->getx() - ancho, bmp->h - (it->gety() - alto), 4, AQUA);
        circlefill(bmp, p.getx() - ancho, bmp->h - (p.gety() - alto), 4, BLANCO);
        stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
        //static int a;
        //cin >> a;
        sleep(0.2);
      }
      for (int j = 0; j < ROT_MEJORA; j++) {
        static double despl;
        despl = 0;
        if (configuracion.beamswitching)
          despl = DESP;
        CSU csu_posible(p.getx()+DIST, p.gety()+despl, j*PI/ROT_MEJORA);
        if (configuracion.beamswitching)
          csu_posible.setorient(ORI);
        rellenar_con_puntos(csu_posible, actuales);
        if (!csu_posible.empty()) {
          static int tam_viejo;
          tam_viejo = 0;
          while (tam_viejo != csu_posible.size() && csu_posible.size() < NUM_BARRAS) {
            progreso();
            tam_viejo = csu_posible.size();
            csu_posible.mejoraArriba();
            rellenar_con_puntos(csu_posible, actuales);
            csu_posible.mejoraAbajo();
            rellenar_con_puntos(csu_posible, actuales);
            csu_posible.mejoraIzquierda();
            rellenar_con_puntos(csu_posible, actuales);
            csu_posible.mejoraDerecha();
            rellenar_con_puntos(csu_posible, actuales);
          }
          posibles.insert(csu_posible);
        }
      }
      min = 0;
      static CSU mejor_opcion;
      static set<CSU>::iterator i;
      for (i = posibles.begin(); i != posibles.end(); i++) 
        if (i->size() > min) {
          min = i->size();
          mejor_opcion = *i;
        }
      if (configuracion.grafico) {
        pintarCSU(bmp, mejor_opcion, ancho, alto);
        stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
        sleep(0.2);
      }
      posibles.clear();
      centros.insert(mejor_opcion);
      eliminar_puntos(mejor_opcion.getPoints(), actuales, eliminados);
    }
    vector[i] = centros;
  }
  min = MAX;
  int select;
  for (int i = 0; i < 4; i++)
    if (vector[i].size() < min) {
      min = vector[i].size();
      select = i;
    }
    else if (vector[i].size() == min && *(vector[i].begin()) < *(vector[select].begin()))
      select = i;
  if (configuracion.verbose) 
    fich << "Salimos de sacar_apuntados" << endl << linea;
  return vector[select];
}

/***************************************************************************//**
 * \fn set<CSU> colisiones (set<CSU> lista_ini, const int &total_puntos);
 * \brief Elimina colisiones entre apuntados
 *
 * El cometido de esta función es reducir el número total de apuntados mediante
 * el uso de búsquedas locales. En primer lugar se descartan aquellas CSUs que
 * no colisionan con ninguna, pues éstas pertenecen al resultado final. De las
 * restantes, se elige una de ella y se seleccionan sus puntos, luego se mira
 * una a una el resto de CSUs para ver si colisionan, y si es así, cogemos sus
 * puntos. De esta forma hacemos una pequeña nube de puntos que da apuntados de
 * más, y con ella realizamos una búsqueda de CSUs más exhaustiva, con un mayor
 * número de rotaciones. Si el resultado es mejor que el que teníamos, volvemos
 * a empezar.
 * \param lista_ini Conjunto de CSUs que queremos reducir
 * \param total_puntos Número de elementos del problema
 * \return Conjunto de CSUs que forman la nueva solución
 *******************************************************************************/
set<CSU> colisiones (set<CSU> lista_ini, const int &total_puntos) {
// Inicializamos
  static int finalizar;
  finalizar = 0;
  static BITMAP *bmp = create_bitmap(800,800), *points = create_bitmap(configuracion.ancho, configuracion.alto);
  static set<Element> pptt, rafiki, puntos, p_parcial;
  static set<Element>::iterator ppttit, p;
  static double a[8], b[8];
  if(configuracion.verbose) {
    fich << linea << endl << "Entramos en colisiones " << endl;
    fich << "Numero de puntos al entrar: " << total_puntos << endl;
    fich << "Ordenamos la lista inicial de " << lista_ini.size() << " CSUs por menor X" << endl;
  }
  sort(lista_ini, TAMPUN);
  static set<CSU>::iterator jt, it;
  static set<CSU> porcion, no_coli;
  set<CSU> lista_fin;
  no_coli.clear();
//******************************************************************************* 
// Vamos a realizar todo el proceso mientras se siga mejorando
  while (finalizar != (lista_ini.size()+no_coli.size())) {
    lista_fin.clear();
    finalizar = lista_ini.size();
    set<Element> eliminados;
    eliminados.clear();
//En esta sección quitamos los que no colisionan para aligerar carga posterior
    if(configuracion.verbose)
      fich << linea << "Metemos en list_fin aquellas CSUs que no colisionan" << endl;
    it = lista_ini.begin();
    while (it != lista_ini.end()){
      if (configuracion.grafico)
        clear_bitmap(points);
      static bool quitable;
      quitable = true;
      jt = lista_ini.begin();
      while (jt != lista_ini.end() && quitable){
        if (configuracion.grafico)
          jt->mostrar(points, ROJO);
        if (it != jt && (it->colision(*jt) || jt->colision(*it))) //Si colisiona, no lo podemos quitar
          quitable = false;
        jt++;
      }
      if (configuracion.grafico) {
        it->mostrar(points, BLANCO);
        stretch_blit(points, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
        sleep(0.3);
      }
      if (quitable) {
        lista_fin.insert(*it);
        p_parcial = it->getPoints();
        for (p = p_parcial.begin(); p != p_parcial.end(); p++) 
          eliminados.insert(*p);
        static set<CSU>::iterator borrar;
        borrar = it; //Guardamos la posicion que se va a elimimar
        it++; //pasamos a mirar la siguiente
        lista_ini.erase(borrar); //    
      }                                
      else                             
        it++;                          
    }                                  
    if(configuracion.verbose)
      fich << lista_fin.size() << " apuntados que no colisionan" << endl;
//******************************************************************************* 
// Mientras no se hayan agrupado todos los numeros
    while (eliminados.size() != total_puntos) { //mientras queden puntos por mirar
      if(configuracion.verbose) {
        fich << "Entramos en el bucle, por lo que quedan puntos" << endl;
        fich << "Quedan " << total_puntos-eliminados.size() << " puntos por cubrir" << endl;
        fich << "Quedan " << lista_ini.size() << " CSUs disponibles. Mostramos los 10 primeros" << endl;
        static int asdasd;
        asdasd = 0; it = lista_ini.begin();
        while (asdasd < 10 && it != lista_ini.end()) {
          fich << it->getid() << ", ";
          asdasd++;
          it++;
        }
        fich << endl;
      }
      progreso();
      puntos.clear();
      p_parcial.clear();
      porcion.clear();
      it = lista_ini.begin(); //it es el principio de la lista de CSUs
      if(configuracion.verbose) {
        fich << "Seleccionado el " << it->getid() << endl;
      }
      //Esto no debería salir nunca
      if (lista_ini.empty()) {
        cout << "Abortando, error extraño" << endl;
        break;
      }
//******************************************************************************* 
// Cogemos los puntos del primero y los colocamos en la lista de mejora 
      p_parcial = it->getPoints(); //p_parcial son todos los puntos de la primera CSU
      if(configuracion.verbose) {
        fich << "Obtenemos los puntos del apuntado" << endl;
        fich << "Son " << p_parcial.size() << " puntos" << endl;
      }
      for (p = p_parcial.begin(); p != p_parcial.end(); p++)
        puntos.insert(*p); //insertamos todos los puntos de la primera CSU en los totales
      porcion.insert(*it); //Ponemos esa CSU en el grupo que se va a mirar
      CSU ini = *it; //Almacenamos la primera CSU
      lista_ini.erase(it); //Borramos la CSU de la lista total
      jt = lista_ini.begin(); //jt es el principio de la lista de CSUs
      if(configuracion.grafico) {
        rafiki.clear();
        for (it = lista_ini.begin(); it != lista_ini.end(); it++) {
          pptt = it->getPoints();
          for (ppttit = pptt.begin(); ppttit != pptt.end(); ppttit++)
            rafiki.insert(*ppttit);
        }
      }
      if(configuracion.verbose) {
        fich << linea <<  "Comprobamos las colisiones" << endl;
      }
//*******************************************************************************
// Seleccionamos todos aquellos que colisionan con el anteriormente seleccionado
      while(!lista_ini.empty() && jt != lista_ini.end()) { //comprobamos cada uno con el primero de la lista
        progreso();
          if(configuracion.grafico) {
            clear_bitmap(bmp);
            ini.getABCD(a);
            jt->getABCD(b);
            line(bmp, a[0] - ini.getx() + 400, 800-(a[1] - ini.gety() + 400), a[2] - ini.getx() + 400, 800-(a[3] - ini.gety() + 400), AMARI);
            line(bmp, a[2] - ini.getx() + 400, 800-(a[3] - ini.gety() + 400), a[4] - ini.getx() + 400, 800-(a[5] - ini.gety() + 400), AMARI);
            line(bmp, a[4] - ini.getx() + 400, 800-(a[5] - ini.gety() + 400), a[6] - ini.getx() + 400, 800-(a[7] - ini.gety() + 400), AMARI);
            line(bmp, a[6] - ini.getx() + 400, 800-(a[7] - ini.gety() + 400), a[0] - ini.getx() + 400, 800-(a[1] - ini.gety() + 400), AMARI);
            line(bmp, b[0] - ini.getx() + 400, 800-(b[1] - ini.gety() + 400), b[2] - ini.getx() + 400, 800-(b[3] - ini.gety() + 400), AQUA);
            line(bmp, b[2] - ini.getx() + 400, 800-(b[3] - ini.gety() + 400), b[4] - ini.getx() + 400, 800-(b[5] - ini.gety() + 400), AQUA);
            line(bmp, b[4] - ini.getx() + 400, 800-(b[5] - ini.gety() + 400), b[6] - ini.getx() + 400, 800-(b[7] - ini.gety() + 400), AQUA);
            line(bmp, b[6] - ini.getx() + 400, 800-(b[7] - ini.gety() + 400), b[0] - ini.getx() + 400, 800-(b[1] - ini.gety() + 400), AQUA);
            for (ppttit = rafiki.begin(); ppttit != rafiki.end(); ppttit++)
              circlefill(bmp, ppttit->getx() - ini.getx() + 400, 800 - (ppttit->gety() - ini.gety() + 400), 2, BLANCO);
            pptt = ini.getPoints();
            for (ppttit = pptt.begin(); ppttit != pptt.end(); ppttit++)
              circlefill(bmp, ppttit->getx() - ini.getx() + 400, 800 - (ppttit->gety() - ini.gety() + 400), 2, AMARI);
            pptt = jt->getPoints();
            for (ppttit = pptt.begin(); ppttit != pptt.end(); ppttit++)
              circlefill(bmp, ppttit->getx() - ini.getx() + 400, 800 - (ppttit->gety() - ini.gety() + 400), 2, AQUA);
          }
        if (ini.colision(*jt) || jt->colision(ini)) {
          if(configuracion.grafico) 
            cout << "COLISIONA" << endl;
          porcion.insert(*jt); //Ponemos esa CSU en el grupo que se va a mirar
          p_parcial = jt->getPoints(); //p_parcial son los puntos de esa CSU
          for (p = p_parcial.begin(); p != p_parcial.end(); p++) 
            puntos.insert(*p); //Añadimos los puntos al total
          static set<CSU>::iterator borrar;
          borrar = jt; //Guardamos la posicion que se va a elimimar
          jt++; //pasamos a mirar la siguiente
          lista_ini.erase(borrar); //
        }
        else {
          if(configuracion.grafico) 
            cout << "NO COLISIONA" << endl;
          jt++;
        }
        if(configuracion.grafico) {
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
      }
      if(configuracion.grafico) 
        cout << "sale con " << porcion.size() << " apuntados que colisionan" << endl;
      static bool continuar;
      continuar = true;
      if(configuracion.verbose) {
        fich << "Sale con " << porcion.size() << " apuntados y " << puntos.size() << " puntos" << endl;
        fich << "Necesario teórico: " << puntos.size()/NUM_BARRAS << endl;
      }
      //******************************************************************************* 
      // Si la colisión no es necesaria teoricamente, se intenta reducir
      if (puntos.size()/NUM_BARRAS < porcion.size()) {
        static bool izq_menor;
        static CSU final;
        static set<CSU>::iterator fin;
        fin = porcion.end();
        fin--;
        final = *fin;
        izq_menor = (ini.gety() < final.gety())? true : false;
        set<CSU> nuevos = sacar_apuntados(puntos);
        sort(nuevos, TAMPUN);
        if(configuracion.verbose) 
          fich << "Conseguimos " << nuevos.size() << endl;
        //Si se ha conseguido mejorar, volvemos a insertarlos para remirarlos
        if ((nuevos.size() < porcion.size()) || (nuevos.size() == porcion.size() && nuevos.begin()->size() > porcion.begin()->size())) {
          if(configuracion.verbose) {
            fich << "Es mejor que la anterior, los reinsertamos" << endl;
            fich << "Lista inicial tenía " << lista_ini.size() << endl;
          }
          continuar = false;
          porcion = nuevos;
          for (it = porcion.begin(); it != porcion.end(); it++)
            lista_ini.insert(*it);
          if(configuracion.verbose) 
            fich << "Lista inicial tiene " << lista_ini.size() << endl;
        }
      }
      //*******************************************************************************
      // Si no se ha conseguido mejorar o la colision en necesaria, quitamos la primera CSU
      if (continuar) {
        if(configuracion.verbose) {
          fich << "Quitamos el primero y eliminamos puntos" << endl;
          fich << "Antes: " << lista_ini.size() << " csus y " << eliminados.size() << " puntos eliminados" << endl;
        }
        it = porcion.begin();
        lista_fin.insert(*it);
        p_parcial = it->getPoints();
        for (p = p_parcial.begin(); p != p_parcial.end(); p++) {
          eliminados.insert(*p);
        }
        porcion.erase(it);
        for (it = porcion.begin(); it != porcion.end(); it++)
          lista_ini.insert(*it);
        if(configuracion.verbose) 
          fich << "Después: " << lista_ini.size() << " csus y " << eliminados.size() << " puntos eliminados" << endl;
      }
    }
    lista_ini = lista_fin;
  }
  return lista_fin;
}

/***************************************************************************//**
 * \fn void guardar (const char* nombre, const set<CSU> &result)
 * \brief Guarda los resultados en un fichero de texto
 * \param nombre Nombre del fichero de salida
 * \param result Conjunto de apuntados que constituyen un resultado
 *******************************************************************************/
void guardar (const char* nombre, const set<CSU> &result) {
  ofstream fich(nombre);
  if (fich.is_open()) {
    for (set<CSU>::iterator it = result.begin(); it != result.end(); it++) { 
      if (configuracion.tipodat)
        fich << "**************************************************************" << endl;
      fich << *it;
    }
  }
  fich.close();
}

/***************************************************************************//**
 * \fn vector<list<vector<Element> > > sinDBS(const set<Element> &puntos)
 * \brief Prepara los datos en caso de que no haya DBScan
 * \param puntos Conjunto de elementos de entrada
 * \return Mismos puntos de entrada en estructura distinta
 *******************************************************************************/
vector<list<vector<Element> > > sinDBS(const set<Element> &puntos) {
  vector<list<vector<Element> > > universo;
  list<vector<Element> > lista;
  vector<Element> copia;
  for (set<Element>::iterator it = puntos.begin(); it != puntos.end(); it++)
    copia.push_back(*it);
  lista.push_back(copia);
  universo.push_back(lista);
  return universo;
}

/***************************************************************************//**
 * \fn void comprobar(const set<CSU> &apuntados, const set<Element> &puntos)
 * \brief Comprueba que todos los puntos estén cubiertos
 * \param apuntados Conjunto solución
 * \param puntos Datos de entrada
 *******************************************************************************/
void comprobar(const set<CSU> &apuntados, const set<Element> &puntos) {
  int total = 0;
  for (set<CSU>::iterator it = apuntados.begin(); it != apuntados.end(); it++)
    total += it->size();
  if (total != puntos.size())
    cout << "Faltan " << puntos.size()-total << " puntos por cubrir" << endl;
}

/***************************************************************************//**
 * \fn inline set<CSU> selectAP (const Element &p, const set<Element> &puntos)
 * \brief Crea una lista de CSUs a partir de un punto
 *
 * Esta función genera todos apuntados posibles a partir de un punto dado, con
 * el fin de que sean utilizados en un posterior proceso de selcción.
 * \param p Elemento que da centro al apuntado
 * \param puntos Conjunto de elementos que constituyen el problema
 * \return Conjunto de apuntados posibles.
 *******************************************************************************/
inline set<CSU> selectAP (const Element &p, const set<Element> &puntos) {
  static set<CSU> posibles;
  static BITMAP* bmp = create_bitmap(configuracion.ancho, configuracion.alto);
  posibles.clear();
  static int j;
  for (j = 0; j < configuracion.rotaciones; j++) {
    static double despl;
    despl = 0;
    if (configuracion.beamswitching)
      despl = DESP;
    CSU csu_posible(p.getx()+DIST, p.gety()+despl, j*PI/configuracion.rotaciones);
    if (configuracion.beamswitching)
      csu_posible.setorient(ORI);
    rellenar_con_puntos(csu_posible, puntos);
    if (!csu_posible.empty()) {
      static int tam_viejo;
      tam_viejo = 0;
      while (tam_viejo != csu_posible.size() && csu_posible.size() < NUM_BARRAS) {
        progreso();
        tam_viejo = csu_posible.size();
        if (configuracion.grafico) {
          clear_bitmap(bmp);
          csu_posible.mostrar(bmp);
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
        csu_posible.mejoraArriba();
        rellenar_con_puntos(csu_posible, puntos);
        if (configuracion.grafico) {
          clear_bitmap(bmp);
          csu_posible.mostrar(bmp);
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
        csu_posible.mejoraAbajo();
        rellenar_con_puntos(csu_posible, puntos);
        if (configuracion.grafico) {
          clear_bitmap(bmp);
          csu_posible.mostrar(bmp);
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
        csu_posible.mejoraIzquierda();
        rellenar_con_puntos(csu_posible, puntos);
        if (configuracion.grafico) {
          clear_bitmap(bmp);
          csu_posible.mostrar(bmp);
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
        csu_posible.mejoraDerecha();
        rellenar_con_puntos(csu_posible, puntos);
        if (configuracion.grafico) {
          clear_bitmap(bmp);
          csu_posible.mostrar(bmp);
          stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
          sleep(0.2);
        }
      }
      posibles.insert(csu_posible);
    }
  }
  return posibles;
}

/***************************************************************************//**
 * \fn set<CSU> apuntadosRandom(set<Element> puntos, const int &opcion)
 * \brief Genera apuntados aleatoriamente
 *
 * Esta función genera un conjunto solución, bien siguiendo un criterio de
 * ordenación de los elementos, o bien cogiendo puntos al azar hasta
 * completarlos.
 * \param puntos Elementos a cubrir
 * \param opcion Criterio de ordenación/aleatorio
 * \return Conjunto de CSUs solución 
 *******************************************************************************/
set<CSU> apuntadosRandom(set<Element> puntos, const int &opcion) {
  static CLOCK_TYPE chrono;
  static double time;
  static set<Element>::iterator v;
  static set<CSU> posibles;//, resultado;
  set<CSU> resultado;
  posibles.clear();
  //resultado.clear();
  static set<CSU>::iterator i;
  static CSU mejor_opcion;
  static int contador;
  if (opcion <= 4) {
    sort(puntos, opcion);
    set<Element> eliminados;
    set<Element> cluster = puntos;
    static set<Element>::iterator e1;
    while (!puntos.empty()) 
      for (v = cluster.begin(); v != cluster.end(); v++) { 
        progreso();
        e1 = eliminados.find(*v);
        if (e1 == eliminados.end()) {
          posibles = selectAP(*v, puntos);
          i = posibles.begin(); 
          mejor_opcion = *i; //Al estar ordenados por tamaño, el primero será el mejor
          resultado.insert(mejor_opcion);
          eliminar_puntos(mejor_opcion.getPoints(), puntos, eliminados); 
        }
      }
    if(configuracion.verbose) {
      fich << "Sol"<<opcion<<" genera " << resultado.size() << " apuntados" << endl;
    }
  }
  else {
    set<Element> eliminados;
    eliminados.clear();
    static set<Element>::iterator e2;
    while (!puntos.empty()) {
      progreso();
      static int pivot, j;
      pivot = rand() % puntos.size();
      v = puntos.begin();
      for (j = 0; j < pivot; j++) 
        v++;
      e2 = eliminados.find(*v);
      if (e2 == eliminados.end()) {
        posibles = selectAP(*v, puntos);
        CSU mejor_opcion;
        i = posibles.begin(); 
        mejor_opcion = *i; //Al estar ordenados por tamaño, el primero será el mejor
        resultado.insert(mejor_opcion);
        eliminar_puntos(mejor_opcion.getPoints(), puntos, eliminados);
      }
    }
    if(configuracion.verbose) {
      fich << "S-Al"<<opcion-4<<" genera " << resultado.size() << " apuntados" << endl;
    }
  }
  return resultado;
}

/***************************************************************************//**
 * \fn set<CSU> grasp (set<CSU> resultado, set<Element> puntos)
 * \brief Heurística GRASP para mejorar resultados
 *
 * Esta función crea N posibles resultados aleatorios, que une hasta formar un
 * único conjunto enorme de apuntados, ordenados por mayor número de elementos.
 * Va escogiendo aleatoriamente los mayores hasta que consiga cubrir todos los
 * puntos, y luego reduce las colisiones. Si no consigue un resultado mejor, se
 * deja el que estaba.
 * \param resultado Cto de apuntados mínimo que resuelve el problema.
 * \param puntos Cto de elementos que forman el problema
 * \result Mejor resultado obtenido, que puede ser el de entrada
 *******************************************************************************/
set<CSU> grasp (set<CSU> resultado, set<Element> puntos) {
  if(configuracion.verbose) {
    fich << "Comienzo del GRASP" << endl;
    fich << "Numero de puntos: " << puntos.size() << endl;
    fich << "Resultado óptimo teórico: " << puntos.size()/NUM_BARRAS << " apuntados" << endl;
  }
  int num_sol = 5;
  int tam_entrada = resultado.size();
  sort(resultado, TAMPUN);
  if(configuracion.verbose) {
    fich << "Se establece la ordenación de CSUs según el mayor número de puntos cubiertos" << endl;
  }
  set<CSU> posibles, lista[num_sol], final;
  static set<CSU>::iterator it, jt, borrar;
  set<Element> p_finales;
  if(configuracion.verbose) {
    fich << "Generamos " << num_sol << " soluciones" << endl;
    fich << linea << endl;
  }
  //PASO 1: generar N soluciones
  for (int i = 0; i < num_sol; i++)
    lista[i] = apuntadosRandom(puntos, i);
  if(configuracion.verbose) {
    fich << linea << endl;
    fich << "Buscamos la mejor solución" << endl;
  }
  //PASO 2: buscar mejor solucion
  for (int i = 0; i < num_sol; i++)
    if (lista[i].size() < resultado.size())
      resultado = lista[i];
  set<CSU> resultado_previo = resultado;
  if(configuracion.verbose) {
    fich << "mejor resultado " << resultado.size() << endl;
    fich << "Inicializamos la solución final con aquellas csus que no solapan con ninguna" << endl;
  }
  //PASO 1: inicializar la solucion final
  it = resultado.begin();
  while (it != resultado.end()) {
      progreso();
    jt = it;
    jt ++;
    static bool col;
    col = false;
    while (jt != resultado.end() && !col) {
      progreso();
      if (it->colision(*jt) || jt->colision(*it))
        col = true;
      jt++;
    }
    if (!col) {
      final.insert(*it);
      static set<Element> contar;
      contar = it->getPoints();
      for (set<Element>::iterator cc = contar.begin(); cc != contar.end(); cc++)
        p_finales.insert(*cc);
      borrar = it;
      it++;
      resultado.erase(borrar);
    }
    else
      it++;
  }
  if(configuracion.verbose) {
    fich << "El resultado final tiene inicialmente " << final.size() << " apuntados" << endl;
    fich << linea << endl << "Creamos la RCL" << endl;
  }
  //PASO 3: Añadir los restantes de S1 a la RCL
  for (it = resultado.begin(); it != resultado.end(); it++)
    posibles.insert(*it);
  for (int i = 0; i < num_sol; i++)
    for(it = lista[i].begin(); it != lista[i].end(); it++)
      posibles.insert(*it);
  if(configuracion.verbose) {
    fich << "La RCL está compuesta por " << posibles.size() << " apuntados. Se lista el número de puntos de cada uno [id, tamaño]:" << endl;
  for (it = posibles.begin(); it != posibles.end(); it++)
    fich  << "[" << it->getid() << "," << it->size() << "] - ";
    fich << endl << linea << endl;
    fich << "Sacamos elementos de la RCL aleatoriamente según el número de puntos que tiene hasta cubrir todos los puntos" << endl;
  }
  //PASO 4: Seleccionar elementos de la RCL hasta que se cubran todos los puntos
  while (p_finales.size() != puntos.size()) {
    progreso();
    static int tam_point_max, limite;
    it = jt = posibles.begin();
    tam_point_max = it->size();
    limite = 0;
    it++;
    while (it->size() == tam_point_max) {
      it++;
      limite++;
    }
    //Seleccionamos uno aleatorio de los mejores
    if (limite != 0)
      limite = rand() % limite;
    for (int i = 0;  i < limite; i++)
      jt++;
    final.insert(*jt);
    static set<Element> contar;
    contar = it->getPoints();
    for (set<Element>::iterator cc = contar.begin(); cc != contar.end(); cc++)
      p_finales.insert(*cc);
    if(configuracion.verbose) {
      fich << "Seleccionado el apuntado " << jt->getid() << endl;
      fich << "Final tiene " << final.size() << " apuntados y " << p_finales.size() << "/" << puntos.size() << " puntos cubiertos" << endl;
    }
    posibles.erase(jt);
  }
  if(configuracion.verbose) {
    fich << linea << endl;
    fich << "Para conseguir todos los puntos se han usado " << final.size() << " apuntados" << endl;
    fich << "Restantes en la RCL " << posibles.size() << endl << linea << endl;
    fich << "Intentamos mejorar este resultado usando la estrategia de reducción de colisiones" << endl;
  }
  //PASO 5: Intentar mejorar el resultado obtenido.
  posibles.clear();
  posibles = final;
  posibles = colisiones(posibles, puntos.size());

  if(configuracion.verbose) {
    fich << "Tras el proceso han quedado " << posibles.size() << " apuntados" << endl;
  }
  if (posibles.size() < resultado_previo.size()) {
    cout << "Mejorado con " << posibles.size() << endl;
    return posibles;
  }
  else {
    cout << "GRASP inútil" << endl;
    return resultado_previo;
  }
}

int Element::orden = 0;
int CSU::orden = 0;
int Element::identificador = 0;
int CSU::identificador = 0;
Config CSU::conf = configuracion;
Config Element::conf = configuracion;

int main (int argc, char **argv) {
  if (argc == 1) {
    cout << "Programa de apuntados para el proyecto Emir." << endl;
    cout << "Modo de uso: ./csuoptimizer [opciones] <fichero de entrada>" << endl;
    cout << "Use ./csuoptimizer --help para más información sobre la entrada." << endl;
    return 0;
  }
  for (int i = 1; i <= argc - 1; i++) {
    if (strcmp(argv[i],"--help") == 0)
      return ayuda();
    if (strcmp(argv[i],"--dbscan") == 0)
      configuracion.dbscan = true;
    if (strcmp(argv[i],"--grasp") == 0)
      configuracion.grasp = true;
    if (strcmp(argv[i],"--graphic") == 0)
      configuracion.grafico = true;
    if (strcmp(argv[i],"-NR") == 0) {
      i++;
      if (atoi(argv[i]) > 0)
        configuracion.rotaciones = atoi(argv[i]);
      else
        cout << "Rotaciones incorrectas, seleccionado valor por defecto" << endl;
    }
    if (strcmp(argv[i], "--verbose") == 0)
      configuracion.verbose = true;
    if (strcmp(argv[i], "--beams") == 0)
      configuracion.beamswitching = true;
    if (strcmp(argv[i], "--noborder") == 0)
      configuracion.noborder = true;
    if (strcmp(argv[i], "--dat") == 0)
      configuracion.tipodat = true;
  }
  CLOCK_TYPE chrono, chrono_t;
  double time;
  CLOCK_Start(chrono_t);
  char* filepath = argv[argc-1];//"../ejemplos/xml/exacto3.xml";
    
// Parser parser(filepath);
  Parser parser;
  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  try {
  #endif //LIBXMLCPP_EXCEPTIONS_ENABLED 
    parser.set_substitute_entities(true); //
    parser.parse_file(filepath);
    #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  }
  catch(const xmlpp::exception& ex) {
    cout << "libxml++ exception: " << ex.what() << endl;
    return 0;
  }
  #endif //LIBXMLCPP_EXCEPTIONS_ENABLED
  
  configuracion.ancho = parser.getWidht();
  configuracion.alto = parser.getHeight();
  Element tmpE;
  tmpE.configurar(configuracion);
  CSU tmpC;
  tmpC.configurar(configuracion);

  vector<list<vector<Element> > > resultado;
  if (configuracion.dbscan) {
    Dbscan db;
    db.setList(parser.getList());
    CLOCK_Start(chrono);
    db.start();
    CLOCK_End(chrono, time);
    cout << "Se tardó " << time << " en hallar los núcleos" << endl;
    resultado = db.getResult();
  }
  else 
    resultado = sinDBS(parser.getList());
  allegro_init();
  //Inicializamos allegro para el pintado
  install_keyboard();
  set_color_depth(16);
  set_window_title(filepath);
  int w = 800, h = 800;
  //get_desktop_resolution(&w,&h);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0) != 0) { //modo gráfico
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("imposible iniciar el modo video\n%s\n", allegro_error);
    return 1;
  }
  set_close_button_callback(close_button_handler);
  BITMAP *bmp = create_bitmap(parser.getHeight(), parser.getWidht());
  clear_bitmap(bmp);
  pintarCores(bmp,resultado);
  clear_bitmap(screen);
  stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
  set<CSU> diferentes[5];
  sort(diferentes[0],TAMPUN);
  int mej, min = MAX;
  CLOCK_Start(chrono);
  for (int i = MENORX; i < 5; i++) {
    diferentes[i] = apuntadosRandom(parser.getList(), i);
    if (diferentes[i].size() < min) {
      min = diferentes[i].size();
      mej = i;
    }
  }
  set<CSU> centros = diferentes[mej];
  CLOCK_End(chrono, time);
  cout << "\rSe tardó " << time << " en hallar los "<< centros.size() << " apuntados" << endl;
  sort(centros, TAMPUN);
  CLOCK_Start(chrono);
  centros = colisiones(centros, parser.getList().size());
  CLOCK_End(chrono, time);
  cout << "\rSe tardó " << time << " en reducir a "<< centros.size() << " apuntados" << endl;
  if (configuracion.grasp) {
    CLOCK_Start(chrono);
    centros = grasp(centros, parser.getList());
    CLOCK_End(chrono, time);
    cout << "\rSe tardó " << time << " en hacer grasp" << endl;
    if(configuracion.verbose) {
      fich << "Se tardó " << time << " en hacer grasp" << endl;
    }
  }
  string entrada = filepath, nombre = RUTA_RES;
  unsigned pos = entrada.find_last_of('/');
  nombre += entrada.substr(++pos, entrada.length()-pos-5);
  if (configuracion.tipodat)
    nombre += "-result.dat";
  else
    nombre += "-result.xml";
  sort(centros, PRIORI);
  guardar(nombre.c_str(), centros);
  for (set<CSU>::iterator it = centros.begin(); it != centros.end(); it++) {
    it->mostrar(bmp);
  }
  CLOCK_End(chrono_t, time);
  cout << "\rNúmero de apuntados total: " << centros.size() << endl;
  int minutos = time/60;
  cout << "\rSe ha tardado en total " << minutos << " min " << time-(minutos*60) << " seg" << endl;
  if(configuracion.verbose) {
    fich << "Se ha tardado en total " << time << " seg" << endl;
  }
  comprobar(centros, parser.getList());

  clear_bitmap(screen);
  stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
  while (!key[KEY_ESC]&&!close_button_pressed) {}
}


/********************************************************//**
 * \mainpage Proyecyo Final de Carrera: EMIR
 * <hr>
 * \author Pedro Orlando Hernández Martín
 * \date 29.Ene.2013
 ************************************************************/
