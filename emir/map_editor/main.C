#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <allegro.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <ctime>
#include "element.h"

/************************************************************//**
 * \file main.C
 * \brief Archivo principal del proyecto - método main
 *
 * Conjunto de métodos que resuelven el problema a tratar (Proyecto
 * EMIR).
 ****************************************************************/

using namespace std;

const double ALT_B = 7.2727;

int CSU::identificador = 0;
int CSU::orden = 0;
int Element::identificador = 0;
int Element::orden = 0;

string tiempo() {
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  string salida = "";
  salida += (now->tm_year + 1900) + '-' + (now->tm_mon + 1) + '-' + now->tm_mday + ".dat";
}

void pintarTODO (BITMAP* bmp, const CSU &c, const int &alto) {
  double a[8];
  c.getABCD(a);
  int blue = rand() % 256;
  int red = rand() % 256;
  int green = rand() % 256;
  line(bmp, a[0], alto-a[1], a[2], alto-a[3], makecol(red,green,blue));
  line(bmp, a[2], alto-a[3], a[4], alto-a[5], makecol(red,green,blue));
  line(bmp, a[4], alto-a[5], a[6], alto-a[7], makecol(red,green,blue));
  line(bmp, a[6], alto-a[7], a[0], alto-a[1], makecol(red,green,blue));
  set<Element> p = c.getPoints();
  for (set<Element>::iterator v = p.begin(); v != p.end(); v++)
    circlefill(bmp, v->getx(), alto - v->gety(), 4, makecol(red,green,blue));
}

void pintarCSU (BITMAP* bmp, const CSU &c, const int &alto) {
  double a[8];
  c.getABCD(a);
  line(bmp, a[0], alto-a[1], a[2], alto-a[3], makecol(255,55,0));
  line(bmp, a[2], alto-a[3], a[4], alto-a[5], makecol(255,55,0));
  line(bmp, a[4], alto-a[5], a[6], alto-a[7], makecol(255,55,0));
  line(bmp, a[6], alto-a[7], a[0], alto-a[1], makecol(255,55,0));
  /*set<Element> p = c.getPoints();
  int green = rand() % 256;
  for (set<Element>::iterator v = p.begin(); v != p.end(); v++)
    circlefill(bmp, v->getx(), alto - v->gety(), 4, makecol(255,green,255));*/
}

inline set<pair<double,double> > crear_exacto(double x, double y) {
  set<pair<double, double> > puntos;
  pair<double, double> p;
  p.second = y - ALTO;
  x-= ANCHO;
  for (int i = 0; i < NUM_BARRAS; i++) {
    p.first = rand() % (2*ANCHO) + x;
    p.second += ALT_B;
    puntos.insert(p);
  }
  return puntos;
}

void crear(set<CSU> &csus, set<Element> &points) {
  static double x, y, alfa;
  cout << "Introduzca coordenadas (centro) de la CSU\nX: ";
  cin >> x;
  cout << "Y: ";
  cin >> y;
  cout << "Introduzca rotación de la misma (en grados): ";
  static int grados;
  cin >> grados;
  alfa = (grados%360)*PI/180;
  CSU nueva(x,y,alfa);
  //cout << "Quiere generación automática o manual (a/m): ";
  static char mode = 'a';
  //cin >> mode;
  if (mode == 'a') {
    set<pair<double, double> > puntos = crear_exacto(x,y);
    static double px, py;
    static set<pair<double, double> >::iterator it;
    for(it = puntos.begin(); it != puntos.end(); it++) {
      px = (it->first-x)*cos(alfa) - (it->second-y)*sin(alfa) + x;
      py = (it->first-x)*sin(alfa) + (it->second-y)*cos(alfa) + y;
      Element new_p(px,py,CERO);
      points.insert(new_p);
      static int barra;
      static double dist;
      nueva.estaDentro3(new_p, barra, dist);
      new_p.setbarra(barra);
      new_p.setdist(dist);
      nueva.pointAdd(new_p);
    }
  }
  else {
    //Código de insertación manual aquí
  }
  csus.insert(nueva);
}

volatile int close_button_pressed = FALSE;
void close_button_handler(void) {
  close_button_pressed = TRUE;
}

int verTodo(const set<CSU> &csus, const set<Element> &points) {
  //Inicializamos allegro para el pintado
  set_window_title("Mostrando el espacio");
  int w = 900, h = 900;
  //get_desktop_resolution(&w,&h);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0) != 0) { //modo gráfico
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("imposible iniciar el modo video\n%s\n", allegro_error);
    return 1;
  }
  set_close_button_callback(close_button_handler);
  BITMAP *bmp = create_bitmap(900, 900);
  for(set<CSU>::iterator it = csus.begin(); it != csus.end(); it++)
    pintarTODO(bmp, *it, 900);
  clear_bitmap(screen);
  stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
  while (!key[KEY_ESC]&&!close_button_pressed) {}
  return 0;
}

int verPuntos(const set<Element> &points) {
  //Inicializamos allegro para el pintado
  set_window_title("Mostrando los puntos");
  int w = 900, h = 900;
  //get_desktop_resolution(&w,&h);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0) != 0) { //modo gráfico
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("imposible iniciar el modo video\n%s\n", allegro_error);
    return 1;
  }
  set_close_button_callback(close_button_handler);
  BITMAP *bmp = create_bitmap(900, 900);
  for(set<Element>::iterator it = points.begin(); it != points.end(); it++)
    circlefill(bmp, it->getx(), 900 - it->gety(), 2, makecol(255,128,0));
  clear_bitmap(screen);
  stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
  while (!key[KEY_ESC]&&!close_button_pressed) {}
  return 0;
}

int verCSUs(const set<CSU> &csus) {
  //Inicializamos allegro para el pintado
  set_window_title("Mostrando las CSUs");
  int w = 900, h = 900;
  //get_desktop_resolution(&w,&h);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0) != 0) { //modo gráfico
    set_gfx_mode(GFX_TEXT,0,0,0,0);
    allegro_message("imposible iniciar el modo video\n%s\n", allegro_error);
    return 1;
  }
  set_close_button_callback(close_button_handler);
  BITMAP *bmp = create_bitmap(900, 900);
  for(set<CSU>::iterator it = csus.begin(); it != csus.end(); it++)
    pintarCSU(bmp, *it, 900);
  clear_bitmap(screen);
  stretch_blit(bmp, screen, 0,0,bmp->w, bmp->h, 0,0, SCREEN_W, SCREEN_H);
  while (!key[KEY_ESC]&&!close_button_pressed) {}
  return 0;
}

void guardar(const set<Element> &points) {
  ofstream fich("output.xml");
  fich << "<Observables widht=\"900\" height=\"900\">" << endl;
  for (set<Element>::iterator it = points.begin(); it != points.end(); it++) {
      fich << "\t<Element id=\"" << it->getid() << "\">" << endl;
      fich << "\t\t<x>"<< it->getx() <<"</x>" << endl;
      fich << "\t\t<y>"<< it->gety() <<"</y>" << endl;
      fich << "\t\t<Prioridad>1</Prioridad>" << endl;
      fich << "\t</Element>" << endl;
  }
  fich << "</Observables>" << endl; 
  fich.close();
  cout << "output.xml generado" << endl;
}

void salvar(set<CSU> c, set<Element> p) {
  //ofstream fich ((char*)(tiempo()).c_str());
  ofstream fich ("save.dat");
  fich << c.size() << endl;
  for (set<CSU>::iterator i = c.begin(); i != c.end(); i++) {
    fich << i->getx() << "\t" << i->gety() << "\t" << i->getalfa() << endl;
    static set<Element> puntos;
    puntos.clear();
    puntos = i->getPoints();
    fich << puntos.size() << endl;
    for (set<Element>::iterator it = puntos.begin(); it != puntos.end(); it++) 
      fich << it->getx() << "\t" << it->gety() << "\t" << it->getprior() << endl;
  }
  fich.close();
  cout << "datos salvados" << endl;
}

void cargar(set<CSU> &c, set<Element> &p) {
  string name;
  cout << "Nombre del fichero a cargar: ";
  cin >> name;
    cout << "OLA" << endl;
  ifstream fich(name.c_str());
  if (fich.is_open()) {
    int tamC, tamP;
    fich >> tamC;
    for (int i = 0; i < tamC; i++) {
      static double Cx, Cy, Ca;
      fich >> Cx;
      fich >> Cy;
      fich >> Ca;
      fich.ignore(10, '\n');
      CSU nueva(Cx, Cy, Ca);
      fich >> tamP;
      for (int j = 0; j < tamP; j++) {
        static double Px, Py, Pp;
        fich >> Px;
        fich >> Py;
        fich >> Pp;
        fich.ignore(10, '\n');
        Element new_p(Px, Py, Pp);
        p.insert(new_p);
        static int barra;
        static double dist;
        nueva.estaDentro3(new_p, barra, dist);
        new_p.setbarra(barra);
        new_p.setdist(dist);
        nueva.pointAdd(new_p);
      }
      c.insert(nueva);
    }
    fich.close();
    cout << "datos cargados" << endl;
  }
  else
    cout << "Problemas al cargar el fichero" << endl;
}

int menu () {
  cout << "Menú del creador de ejemplos" << endl;
  cout << "1 Crear CSU" << endl;
  cout << "2 Visualizar CSUs" << endl;
  cout << "3 Visualizar Puntos" << endl;
  cout << "4 Visualizar Espacio" << endl;
  cout << "5 Guardar puntos" << endl;
  cout << "6 Salvar datos" << endl;
  cout << "7 Cargar datos" << endl;
  cout << "8 Salir" << endl;
  cout << endl << "opcion: ";
  int op;
  cin >> op;
  return op;
}

int main (int argc, char **argv) {
  set<Element> points;
  set<CSU> csus;
  int op = 0;
  while (op != 8) {
    op = menu();
    allegro_init();
    set_color_depth(16);
    install_keyboard();
    switch (op) {
      case 1: crear(csus, points); break;
      case 2: verCSUs(csus); break;
      case 3: verPuntos(points); break;
      case 4: verTodo(csus, points); break;
      case 5: guardar(points); break;
      case 6: salvar(csus, points); break;
      case 7: cargar(csus, points); break;
      case 8: cout << "Saliendo del editor" << endl;break;
      default: cout << "Opción no válida" << endl;
    }
    allegro_exit();
  }
}
