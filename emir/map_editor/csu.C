#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "element.h"

/************************************************************//**
 * \file csu.C
 * \brief Archivo de definiciones de la clase CSU
 *
 * Implementación de los métodos de la clase CSU
 ****************************************************************/

using namespace std;

int gz = 900;

#define min(a, b) (a <= b ? a : b)
#define max(a, b) (a >= b ? a : b)

inline void CSU::extremos() {
  Ax = ((-ANCHO*cos(alfa))-(-ALTO*sin(alfa))+x);
  Ay = ((-ANCHO*sin(alfa))+(-ALTO*cos(alfa))+y);
  Bx = ((ANCHO*cos(alfa))-(-ALTO*sin(alfa))+x);
  By = ((ANCHO*sin(alfa))+(-ALTO*cos(alfa))+y);
  Cx = ((ANCHO*cos(alfa))-(ALTO*sin(alfa))+x);
  Cy = ((ANCHO*sin(alfa))+(ALTO*cos(alfa))+y);
  Dx = ((-ANCHO*cos(alfa))-(ALTO*sin(alfa))+x);
  Dy = ((-ANCHO*sin(alfa))+(ALTO*cos(alfa))+y);
  if (alfa != CERO && alfa != PIMEDIO) { //No es vertical y no habrá division por 0
    ma = (Dy - Ay)/(Dx - Ax); // pendiente de la recta vertical (perpendicular a las barras)
    mb = -1/ma; // pendiente recta perpendicular (paralela a las barras)
  }
  /*minx = min(Ax, Bx);
  minx = min(minx, Cx);
  minx = min(minx, Dx);
  maxx = max(Ax, Bx);
  maxx = max(maxx, Cx);
  maxx = max(maxx, Dx);
  miny = min(Ay, By);
  miny = min(miny, Cy);
  miny = min(miny, Dy);
  maxy = max(Ay, By);
  maxy = max(maxy, Cy);
  maxy = max(maxy, Dy);*/
}

CSU::CSU (double posx, double posy, double angulo) {
  id = identificador++;
  prior = CIEN;
  x = posx;
  y = posy;
  alfa = angulo;
  puntos.clear();
  extremos();
  for (int i = CERO; i < NUM_BARRAS; i++) {
    barras_ocupadas[i] = false;
    distancia_punto[i] = INF;
  }
  dist_min = INF;
  dist_max = INF;
}

CSU::CSU (const CSU &c) {
  id = c.getid();
  prior = c.getprior();
  x = c.getx();
  y = c.gety();
  alfa = c.getalfa();
  puntos = c.getPoints();
  dist_min = c.getMinD();
  dist_max = c.getMaxD();
  for (int i = 0; i < NUM_BARRAS; i++) {
    barras_ocupadas[i] = c.getBarra(i);
    distancia_punto[i] = c.getDist(i);
  }
  extremos();
}
    
void CSU::pointAdd(vector<Element> lista) {
  vector<Element>::iterator it = lista.begin();
  for(it; it != lista.end(); it++)
    puntos.insert(*it);
}

void CSU::pointAdd(Element p) {
  puntos.insert(p); 
  barras_ocupadas[p.getbarra()] = true;
  distancia_punto[p.getbarra()] = p.getdist();
  if (p.getprior() < prior)
    prior = p.getprior();
  if (p.getdist() < dist_min)
    dist_min = p.getdist();
  if (2*ANCHO-p.getdist() < dist_max)
    dist_max = 2*ANCHO-p.getdist();
}

void CSU::imprimir(BITMAP* bmp) const{
/*
  line(bmp, Ax, Ay, Bx, By, makecol(255,255,0));
  line(bmp, Bx, By, Cx, Cy, makecol(255,255,0));
  line(bmp, Cx, Cy, Dx, Dy, makecol(255,255,0));
  line(bmp, Dx, Dy, Ax, Ay, makecol(255,255,0));
*/
  //imprimir();
  static int j,i;
  static double distAR, distAB, distDE, distIZ, nxAR, nyAR, nxAB, nyAB, nxIZ, nyIZ, nxDE, nyDE;
  i = CERO;
  while (!barras_ocupadas[i])
    i++;
  distAR = i * DIST_BARRAS - 0.5;
  i = NUM_BARRAS;
  while (!barras_ocupadas[i])
    i--;
  distAB = (NUM_BARRAS - 1 - i) * DIST_BARRAS - 0.5;
  distIZ = dist_min - 0.5;
  distDE = dist_max - 0.5;
  nxAR = nxAB = nxIZ = nxDE = x; nyAR = nyAB = nyIZ = nyDE = y;
  if (alfa == CERO) { //es vertical, movemos la X
    nyAR += distAR;
    nyAB -= distAB;
    nxIZ += distIZ;
    nxDE -= distDE;
  }
  else if (alfa == PIMEDIO) { //es horizontal, movemos la Y
    nxAR -= distAR;
    nxAB += distAB;
    nyIZ -= distIZ;
    nyDE += distDE;
  }
  else {
    static double raizAR, raizAB, raizIZ, raizDE;
    raizAR = sqrt((distAR*distAR)/(1 + ma * ma));
    raizAB = sqrt((distAB*distAB)/(1 + ma * ma));
    raizIZ = sqrt((distIZ*distIZ)/(1 + mb * mb));
    raizDE = sqrt((distDE*distDE)/(1 + mb * mb));
    nyAR -= ma * raizAR;
    nyAB += ma * raizAB;
    nxIZ += raizIZ;
    nxDE -= raizDE;
    nxAR -= raizAR;
    nxAB += raizAB;
    nyIZ += mb * raizIZ;
    nyDE -= mb * raizDE;
  }
  int blue = rand() % 256, gy = 900;
  line(bmp, Ax, gz - Ay, Bx, gz - By, makecol(255,255,blue));
  line(bmp, Bx, gz - By, Cx, gz - Cy, makecol(255,255,blue));
  line(bmp, Cx, gz - Cy, Dx, gz - Dy, makecol(255,255,blue));
  line(bmp, Dx, gz - Dy, Ax, gz - Ay, makecol(255,255,blue));
  line(bmp, nxAR, gz - nyAR, x, gz - y, makecol(255,255,255));
  line(bmp, nxAB, gz - nyAB, x, gz - y, makecol(255,255,255));
  line(bmp, nxIZ, gz - nyIZ, x, gz - y, makecol(255,255,255));
  line(bmp, nxDE, gz - nyDE, x, gz - y, makecol(255,255,255));
    circlefill(bmp, Ax, gz - Ay, 4, makecol(255,255,255));
    circlefill(bmp, Dx, gz - Dy, 4, makecol(255,255,255));
  int green = rand() % 256;
  static double new_x, new_y;
  for (set<Element>::iterator v = puntos.begin(); v != puntos.end(); v++) {
    circlefill(bmp, v->getx(), gz - v->gety(), 4, makecol(255,green,255));
    if (alfa != CERO && alfa != PIMEDIO) {
      new_x = (ma * Ax - mb * v->getx() + v->gety() - Ay) / (ma - mb);
      new_y = ma * (new_x - Ax) + Ay;
    }
    else if (alfa == CERO) {   // Es vertical
      new_x = Ax;
      new_y = v->gety();
    }
    else{  // Es horizontal
      new_y = Ay;
      new_x = v->getx();
    }
    line(bmp, new_x, gz - new_y, v->getx(), gz - v->gety(), makecol(255,255,255));
  }
}

void CSU::clear() {
  id = -1;
  prior = CIEN;
  x = y = alfa = 0.0;
  for (int i = CERO; i < NUM_BARRAS; i++) {
    barras_ocupadas[i] = false;
    distancia_punto[i] = INF;
  }
  dist_min = INF;
  dist_max = INF;
}

#define area(Ax, Ay, Bx, By, Cx, Cy) ((Cx*By-Bx*Cy)-(Cx*Ay-Ax*Cy)+(Bx*Ay-Ax*By))/2
#define negativo(valor) (valor <= CERO ? CERO : 1)

/*Determina si un punto está dentro del área de un triángulo formado por
  dicho punto y las aristas de rectángulo.*/
bool CSU::estaDentro(const Element &p) const {
  static double ABP, BCP, CDP, DAP;
  ABP = area(Ax,Ay,Bx,By,p.getx(),p.gety());
  BCP = area(Bx,By,Cx,Cy,p.getx(),p.gety());
  CDP = area(Cx,Cy,Dx,Dy,p.getx(),p.gety());
  DAP = area(Dx,Dy,Ax,Ay,p.getx(),p.gety());
  static int dentro;
  dentro = negativo(ABP) + negativo(BCP) + negativo(CDP) + negativo(DAP);
  if (dentro == CERO || dentro == 4)
    return true;
  else
    return false;
}

/*A = -(y2 - y1)
  B = x2 - x1
  C = -(A * x1 + B * y1)
  D = A * xp + B * yp + C*/
#define edge(x1, y1, x2, y2) (-(y2-y1) * p.getx() + (x2 - x1) * p.gety() - (-(y2-y1)*x1 + (x2-x1)*y1))

/*Determina si un punto está dentro de la CSU mirando sus aristas D < 0 
  si el punto está a la izq, D = 0 si coinciden, D > 0 si está a la derecha*/
  //NOTA: es más rápido que el otro
bool CSU::estaDentro2(const Element &p) const {
  register double distancia = (double)sqrt((p.getx() - x) * (p.getx() - x) + (p.gety() -y) * (p.gety() -y));
  if (distancia <= ALCANCE) {
    static int D1, D2, D3, D4;
    D1 = edge(Ax, Ay, Dx, Dy);
    D2 = edge(Dx, Dy, Cx, Cy);
    D3 = edge(Cx, Cy, Bx, By);
    D4 = edge(Bx, By, Ax, Ay);
    return (D1 <= CERO && D2 <= CERO && D3 <= CERO && D4 <= CERO);
  }
  return false;
}

//http://pier.guillen.com.mx/algorithms/07-geometricos/07.3-interseccion_recta-recta.htm
bool CSU::estaDentro3(const Element &p, int &barra, double &distancia) const {
  static double new_x, new_y;
  if (estaDentro2(p)) {
    if (alfa != CERO && alfa != PIMEDIO) { // No es ni vertical ni horizontal
      new_x = (ma * Ax - mb * p.getx() + p.gety() - Ay) / (ma - mb);
      new_y = ma * (new_x - Ax) + Ay;
    }
    else if (alfa == CERO){   // Es vertical
      new_x = Ax;
      new_y = p.gety();
    }
    else{  // Es horizontal
      new_y = Ay;
      new_x = p.getx();
    }  
	  barra = (int)(sqrt((Ax - new_x) * (Ax - new_x) + (Ay - new_y) * (Ay - new_y)) / DIST_BARRAS);
    if (!barras_ocupadas[barra]) 
      distancia = (double)sqrt((p.getx() - new_x) * (p.getx() - new_x) + (p.gety() - new_y) * (p.gety() - new_y));
    return !barras_ocupadas[barra];
  }
  return false;
}

/* Esta mejora traslada el punto central del apuntado dejando la barra '0' con un elemento */
void CSU::mejoraArriba() {
  static int i, j;
  static double dist;
  i = CERO;
  while (!barras_ocupadas[i])
    i++;
  if (i != CERO) {
    dist = i * DIST_BARRAS - 0.1;
    for (j = CERO; j < NUM_BARRAS; j++){
      barras_ocupadas[j] = false;
      distancia_punto[j] = INF;
    }
    if (alfa == CERO) { //es vertical, bajamos la Y
      y += dist;
    }
    else if (alfa == PIMEDIO) { //es horizontal, movemos la X
      x -= dist;
    }
    else {
      static double raiz;
      raiz = sqrt((dist*dist)/(1 + ma * ma));
      y -= ma * raiz;
      x -= raiz;
    }
    extremos();
    dist_min = INF;
    dist_max = INF;
    puntos.clear();
  }
}

void CSU::mejoraAbajo() {
  static int i, j;
  static double dist;
  i = NUM_BARRAS - 1;
  while (!barras_ocupadas[i])
    i--;
  if (i != NUM_BARRAS - 1) {
    dist = (NUM_BARRAS - 1 - i) * DIST_BARRAS - 0.1;
    for (j = CERO; j < NUM_BARRAS; j++){
      barras_ocupadas[j] = false;
      distancia_punto[j] = INF;
    }
    if (alfa == CERO) { //es vertical, subimos la Y
      y -= dist;
    }
    else if (alfa == PIMEDIO) { //es horizontal, movemos la X
      x += dist;
    }
    else {
      static double raiz;
      raiz = sqrt((dist*dist)/(1 + ma * ma));
      y += ma * raiz;
      x += raiz;
    }
    extremos();
    dist_min = INF;
    dist_max = INF;
    puntos.clear();
  }
}

void CSU::mejoraIzquierda() {
  static int j;
  static double dist;
  dist = dist_min - 0.1;
  for (j = CERO; j < NUM_BARRAS; j++){
    barras_ocupadas[j] = false;
    distancia_punto[j] = INF;
  }
  if (alfa == CERO) { //es vertical, movemos la X
    x += dist;
  }
  else if (alfa == PIMEDIO) { //es horizontal, movemos la Y
    y += dist;
  }
  else {
    static double raiz;
    raiz = sqrt((dist*dist)/(1 + mb * mb));
    if (alfa < PIMEDIO) {
      x += raiz;
      y += mb * raiz;
    } else {
      x -= raiz;
      y -= mb * raiz;
    }
  }
  extremos();
  dist_min = INF;
  dist_max = INF;
  puntos.clear();
}

void CSU::mejoraDerecha() {
  static int j;
  static double dist;
  dist = dist_max - 0.1;
  for (j = CERO; j < NUM_BARRAS; j++){
    barras_ocupadas[j] = false;
    distancia_punto[j] = INF;
  }
  if (alfa == CERO) { //es vertical, movemos la X
    x -= dist;
  }
  else if (alfa == PIMEDIO) { //es horizontal, movemos la Y
    y -= dist;
  }
  else {
    static double raiz;
    raiz = sqrt((dist*dist)/(1 + mb * mb));
    if (alfa < PIMEDIO) {
      x -= raiz;
      y -= mb * raiz;
    } else {
      x += raiz;
      y += mb * raiz;
    }
  }
  extremos();
  dist_min = INF;
  dist_max = INF;
  puntos.clear();
}

bool CSU::colision (const CSU &csu) const {
  static double minimoX, maximoX, minimoY, maximoY, s2[8];
  static pair<double,double> punto;
  minimoX = minimoY = INF;
  maximoX = maximoY = 0;
  csu.getABCD(s2);  //Ax,Ay,Bx,By,Cx,Cy,Dx,Dy
  static int i, j;
  //RECTA AD
  for (i = 0; i < 8; i+=2) { //cada uno de los puntos de CSU2
    if (alfa != CERO && alfa != PIMEDIO) { // No es ni vertical ni horizontal
      punto.first = (ma * Ax - mb * s2[i] + s2[i+1] - Ay) / (ma - mb);
      punto.second = ma * (punto.first - Ax) + Ay;
    }
    else if (alfa == CERO){   // Es vertical
      punto.first = Ax;
      punto.second = s2[i+1];
    }
    else{  // Es horizontal
      punto.first = s2[i];
      punto.second = Ay;
    }
    minimoX = min(minimoX, punto.first);
    maximoX = max(maximoX, punto.first);
    minimoY = min(minimoY, punto.second);
    maximoY = max(maximoY, punto.second);
  }
  //Comprobamos que no haya solape
  static double miX, maX;
  miX = min(Ax,Dx);
  maX = max(Ax,Dx);
  if (maximoX < miX)
    return false;
  if (minimoX > maX)
    return false;
  miX = min(Ay,Dy);
  maX = max(Ay,Dy);
  if (maximoY < miX)
    return false;
  if (minimoY > maX)
    return false;
  //Si llegamos aquí es que hay solape en la proyeccion del lado AD (izq)
  //Repetimos para el lado DC
  //RECTA DC
  minimoX = minimoY = INF;
  maximoX = maximoY = 0;
  for (i = 0; i < 8; i+=2) { //cada uno de los puntos de CSU2
    if (alfa != CERO && alfa != PIMEDIO) { // No es ni vertical ni horizontal
      punto.first = (mb * Dx - ma * s2[i] + s2[i+1] - Dy) / (mb - ma);
      punto.second = mb * (punto.first - Dx) + Dy;
    }
    else if (alfa == CERO){   // Es vertical
      punto.first = s2[i];
      punto.second = Dy;
    }
    else{  // Es horizontal
      punto.first = Dx;
      punto.second = s2[i+1];
    }
    minimoX = min(minimoX, punto.first);
    maximoX = max(maximoX, punto.first);
    minimoY = min(minimoY, punto.second);
    maximoY = max(maximoY, punto.second);
  }
  //Comprobamos que no haya solape
  miX = min(Cx,Dx);
  maX = max(Cx,Dx);
  if (maximoX < miX)
    return false;
  if (minimoX > maX)
    return false;
  miX = min(Cy,Dy);
  maX = max(Cy,Dy);
  if (maximoY < miX)
    return false;
  if (minimoY > maX)
    return false;
  //Si llegamos hasta aquí es que los bordes colisionan. Comprobamos si los puntos también
  static set<Element>::iterator p;
  static int b;
  static double d;
  CSU vacia (csu.getx(), csu.gety(), csu.getalfa());
  for (p = puntos.begin(); p != puntos.end(); p++)
    if (vacia.estaDentro3(*p,b,d))
      return true;
  return false;
}

bool CSU :: operator < (const CSU &c) const {
  switch (orden) {
    case 4: //Prioridad
      if (prior < c.getprior())
        return true;
      if (prior > c.getprior())
        break;
    case 5: //Numero de puntos
      if (size() > c.size())
        return true;
      if (size() < c.size())
        break;
    case 0: //menor X
      if (x < c.getx())
        return true;
      else {
        if ((y < c.gety()) && (x == c.getx()))
          return true;
        else {
          if ((y == c.gety()) && (x == c.getx()) && alfa < c.getalfa())
            return true;
          else {
            if (y == c.gety() && x == c.getx() && alfa == c.getalfa() && size() > c.size())
              return true;
            else
              if (y == c.gety() && x == c.getx() && alfa == c.getalfa() && size() == c.size()) {
                static set<Element>::iterator it, jt;
                static set<Element> comparar;
                comparar = c.getPoints();
                for (it = puntos.begin(); it != puntos.end(); it++) {
                  jt = comparar.find(*it);
                  if (jt == comparar.end())
                    return true;
                  else
                    return false;
                }
              }
          }
        }
      }
      break;
    case 1: //Mayor X
      if (x > c.getx())
        return true;
      else
        if ((y < c.gety()) && (x == c.getx()))
          return true;
        else
          if ((y == c.gety()) && (x == c.getx()) && alfa < c.getalfa())
            return true;
      break;
    case 2: //menor Y
      if (y < c.gety())
        return true;
      else
        if ((x < c.getx()) && (y == c.gety()))
          return true;
        else
          if ((y == c.gety()) && (x == c.getx()) && alfa < c.getalfa())
            return true;
      break;
    case 3: //Mayor Y
      if (y > c.gety())
        return true;
      else
        if ((x < c.getx()) && (y == c.gety()))
          return true;
        else
          if ((y == c.gety()) && (x == c.getx()) && alfa < c.getalfa())
            return true;
      break;
  }
  return false;
}

bool CSU :: operator == (const CSU &c) const {
  if ((id == c.getid()) || ((x == c.getx()) && (y == c.gety()) && (alfa == getalfa())));
    return true;
  return false;
}

void CSU :: operator = (const CSU &c) {
  id = c.getid();
  prior = c.getprior();
  x = c.getx();
  y = c.gety();
  alfa = c.getalfa();
  puntos = c.getPoints();
  dist_min = c.getMinD();
  dist_max = c.getMaxD();
  for (int i = 0; i < NUM_BARRAS; i++) {
    barras_ocupadas[i] = c.getBarra(i);
    distancia_punto[i] = c.getDist(i);
  }
  extremos();
}

