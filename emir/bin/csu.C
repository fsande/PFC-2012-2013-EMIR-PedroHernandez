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

const string linea = "*****************************************************************\n";

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
}

CSU::CSU (double posx, double posy, double angulo, int ori) {
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
  orientacion = ori;
  margenUp = margenDown = INF;
  limiteS = BORDE_SUP_DEF;
  limiteI = BORDE_INF_DEF;
  if (conf.noborder) {
    limiteS = BORDE_SUP;
    limiteI = BORDE_INF;
  }
  if (conf.beamswitching) {
    if (orientacion == ARRIBA)
      limiteI = BARRA2_3;
    if (orientacion == ABAJO)
      limiteS = BARRA1_3;
  }
}

void CSU::setorient(const int &i) {
  orientacion = i;
  if (conf.beamswitching) {
    if (orientacion == ARRIBA)
      limiteI = BARRA2_3;
    if (orientacion == ABAJO)
      limiteS = BARRA1_3;
  }
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
  if (p.getdist() < dist_min) {
    dist_min = p.getdist();
  }
  if (2*ANCHO-p.getdist() < dist_max) {
    dist_max = 2*ANCHO-p.getdist();
  }
  if (limiteS - p.getzona() < margenUp)
    margenUp = limiteS - p.getzona();
  if (p.getzona() - limiteI < margenDown)
    margenDown = p.getzona() - limiteI;
}

void CSU::actualizar2(/*int move , double a_mover, const int &pid*/) {
  static set<Element> newsp;
  newsp.clear();
  static set<Element>::iterator it;
  static Element p;
  static double mUp, mDown;
  mUp = mDown = INF;
  //recalculamos las posiciones
  for (it = puntos.begin(); it != puntos.end(); it++) {
    p = *it;
    //Configuramos el nuevo punto
    static double new_x, new_y, zone, rango, dist;
    static int barra;
    testeo(p, new_x, new_y);
    zone = sqrt((Ax - new_x) * (Ax - new_x) + (Ay - new_y) * (Ay - new_y));
	  barra = (int)(zone / DIST_BARRAS);
    rango = zone - (barra * DIST_BARRAS);
    dist = (double)sqrt((p.getx() - new_x) * (p.getx() - new_x) + (p.gety() - new_y) * (p.gety() - new_y));
    p.setdist(dist);
    p.setbarra(barra);
    p.setzona(rango);
    //Comenzamos las comprobaciones para confirmar que todo está como debería
    //Calculamos nuevos márgenes
    if (limiteS - rango < mUp)
      mUp = limiteS - rango;
    if (rango - limiteI < mDown)
      mDown = rango - limiteI;
    distancia_punto[barra] = dist;
/*    //testeamos que no se ha movido de la barra en la que estaba
    if (it->getbarra() != barra) {
      cout << "WARNING - Punto de la exbarra " << it->getbarra() << " en barra " 
           << barra << " en lugar de en la " << it->getbarra() << endl;
     // sleep(3);
    }
    //testeamos que se ha movido de zona como se esperaba
    if (move == 2) //subimos CSU, baja la zona
      if (abs((it->getzona()-a_mover) - rango) > 0.000001 && it->getid() != pid) {
        cout << "WARNING 2 - El punto " <<it->getid() << " de la barra " << barra << " ha cambiado su zona en "
             << (it->getzona()-a_mover) - rango << " arcseg de distancia" << endl;
        cout << "Antes: " << it->getzona() << " Ahora está en la zona " << rango << endl;
       // sleep(3);
      }
    if (move == 3) //bajamos CSU, sube la zona
      if (abs((it->getzona()+ a_mover) - rango) > 0.000001 && it->getid() != pid) {
        cout << "WARNING 3 - El punto " <<it->getid() << " de la barra " << barra << " ha cambiado su zona en "
             <<  (it->getzona()+ a_mover) - rango << " arcseg de distancia" << endl;
        cout << "Antes: " << it->getzona() << " Ahora está en la zona " << rango << endl;
        //sleep(3);
      }
    if (move == 4) //subimos CSU, baja la zona
      if (abs((it->getzona() - a_mover) - rango) > 0.000001 && it->getid() != pid) {
        cout << "WARNING 4 - El punto " <<it->getid() << " de la barra " << barra << " ha cambiado su zona en "
             << (it->getzona() - a_mover) - rango << " arcseg de distancia" << endl;
        cout << "Antes: " << it->getzona() << " Ahora está en la zona " << rango << endl;
     //   sleep(3);
      }
    if (move == 5) //bajamos CSU, sube la zona
      if (abs(rango - (it->getzona()+a_mover)) > 0.000001 && it->getid() != pid) {
        cout << "WARNING 5 - El punto " <<it->getid() << " de la barra " << barra << " ha cambiado su zona en "
             << rango - (it->getzona()+a_mover) << " arcseg de distancia" << endl;
        cout << "Antes: " << it->getzona() << " Ahora está en la zona " << rango << endl;
      //  sleep(3);
      }
    //Comprobamos que no se haya producido un desplazamiento lateral
    if (dist != it->getdist()) {
      if (abs(dist - it->getdist()) > 0.000001){
        cout << "WARNING!!!!!!!!!!! - El punto de la barra " << barra << " ha cambiado en "
             << dist-it->getdist() << " arcseg de distancia" << endl;
        sleep(3);
      }
    }
*/
    if (dist < dist_min) {
      dist_min = dist;
    }
    if (2*ANCHO-dist < dist_max) {
      dist_max = 2*ANCHO-dist;
    }
    newsp.insert(p);
  }
  margenUp = mUp;
  margenDown = mDown;
/*  if (puntos.size() != newsp.size()) {
    cout << "Error" << endl;
    exit(0);
  }
*/
  puntos.clear();
  puntos = newsp;
}

void CSU::pointAddMove(Element &p, const int &move) {
  static double dist;
  //Hay que subir la CSU
  if (move == 2 || move == 4) {
    if (move == 2) //está muy arriba
      dist = p.getzona() - limiteS + 0.01;
    if (move == 4)  //pasar a barra inferior
      dist = p.getzona() + (DIST_BARRAS - limiteS) + 0.01;
    if (alfa == CERO) { //es vertical, subimos la Y
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
    margenDown -= dist;
    margenUp += dist;
  }
  //Hay que bajar la CSU
  else {
    if (move == 3)  //Pasar a barra superior 
      dist = DIST_BARRAS - p.getzona() + limiteI + 0.01;
    if (move == 5) { //Está demasiado abajo
      dist = limiteI - p.getzona() + 0.01;
    }
    if (alfa == CERO) { //es vertical, bajamos la Y
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
    margenDown += dist;
    margenUp -= dist;
  }
  extremos();
  /*static int barra;
  static double distancia, zona;
  if (estaDentro(p, barra, distancia, zona) != 1) {
    cout << "ALGO TA MAL " << linea;
    sleep(1);
  }
  if (barra != p.getbarra())
    cout << "CAMBIO DE BARRA, esperado " << p.getbarra() << " recibido " << barra << endl;
  p.setbarra(barra);
  p.setdist(distancia);
  p.setzona(zona);*/
  puntos.insert(p);
  barras_ocupadas[p.getbarra()] = true;
  if (p.getprior() < prior)
    prior = p.getprior();
/*  if (limiteS - p.getzona() < margenUp)
    margenUp = limiteS - p.getzona();
  if (p.getzona() - limiteI < margenDown)
    margenDown = p.getzona() - limiteI;*/
  actualizar2(/*move, dist, p.getid()*/);
//  comprobacion();
}

void CSU::mostrar(BITMAP* bmp, int color) const {
  static pair<double,double> bA[NUM_BARRAS], bB[NUM_BARRAS];
  static int i;
  static double dist;
  for (i = 0; i < NUM_BARRAS; i++) {
    dist = i * DIST_BARRAS;
    if (alfa == CERO) { //es vertical, bajamos la Y
      bA[i].first  = Ax;
      bA[i].second = Ay + dist;
      bB[i].first  = Bx;
      bB[i].second = By + dist;
    }
    else if (alfa == PIMEDIO) { //es horizontal, movemos la X
      bA[i].first  = Ax - dist;
      bA[i].second = Ay;
      bB[i].first  = Bx - dist;
      bB[i].second = By;
    }
    else {
      static double raiz;
      raiz = sqrt((dist*dist)/(1 + ma * ma));
      bA[i].second = Ay - ma * raiz;
      bA[i].first  = Ax - raiz;
      bB[i].second = By - ma * raiz;
      bB[i].first  = Bx - raiz;
    }
    line(bmp, bA[i].first, bmp->h-bA[i].second, bB[i].first, bmp->h-bB[i].second, color);
  }
  line(bmp, Ax, bmp->h-Ay, Bx, bmp->h-By, color);
  line(bmp, Bx, bmp->h-By, Cx, bmp->h-Cy, color);
  line(bmp, Cx, bmp->h-Cy, Dx, bmp->h-Dy, color);
  line(bmp, Dx, bmp->h-Dy, Ax, bmp->h-Ay, color);
  for (set<Element>::iterator v = puntos.begin(); v != puntos.end(); v++)
    circlefill(bmp, v->getx(), bmp->h - v->gety(), 2, color);
}

void CSU::clear() {
  id = -1;
  prior = CIEN;
  x = y = alfa = 0.0;
  for (int i = CERO; i < NUM_BARRAS; i++) {
    barras_ocupadas[i] = false;
    distancia_punto[i] = INF;
  }
  dist_min = dist_max = margenDown = margenUp = INF;
}

/*A = -(y2 - y1)
  B = x2 - x1
  C = -(A * x1 + B * y1)
  D = A * xp + B * yp + C*/
#define edge(x1, y1, x2, y2) (-(y2-y1) * p.getx() + (x2 - x1) * p.gety() - (-(y2-y1)*x1 + (x2-x1)*y1))

/*Determina si un punto está dentro de la CSU mirando sus aristas D < 0 
  si el punto está a la izq, D = 0 si coinciden, D > 0 si está a la derecha*/
bool CSU::estaDentro2(const Element &p) const {
  set<Element>::iterator it = puntos.find(p);
  if (it != puntos.end())
    return false;
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

void CSU::testeo(const Element &p, double &new_x, double &new_y) const {
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
}

//pares: hay que subir la CSU, impares: hay que bajar la CSU
int CSU::p_potencial(const double &rango, int &barra) const {
  if (rango > limiteS) { //Parte superior de la barra
    if (!barras_ocupadas[barra] && rango - limiteS + 0.01 <= margenDown /*&& margenDown >= 0.01*/) //cabe en esta barra
      return 2;
    if (barra < NUM_BARRAS-1 && !barras_ocupadas[barra+1])
      if (DIST_BARRAS - rango + limiteI + 0.01 <= margenUp /*&& margenUp >= 0.01*/) {
        barra++;
        return 3;
      }
  }
  if (rango < limiteI) { //Parte inferior de la barra
    if (limiteI - rango + 0.01 <= margenUp/* && margenUp >= 0.01*/) {
      if (barras_ocupadas[barra])
        return 0;
      else
        return 5;
    }
    if (barra > 0 && !barras_ocupadas[barra-1])
      if (rango + (DIST_BARRAS-limiteS) + 0.01 <= margenDown/* && margenDown >= 0.01*/) {
        barra--;
        return 4;
      }
  }
  return 0;
}

//http://pier.guillen.com.mx/algorithms/07-geometricos/07.3-interseccion_recta-recta.htm
int CSU::estaDentro(const Element &p, int &barra, double &distancia, double &rango) const {
  static double new_x, new_y, zone;
  if (estaDentro2(p)) {
    testeo(p, new_x, new_y);
    zone = sqrt((Ax - new_x) * (Ax - new_x) + (Ay - new_y) * (Ay - new_y));
	  barra = (int)(zone / DIST_BARRAS);
    if (barra == NUM_BARRAS)
      return 0;
    rango = zone - (barra * DIST_BARRAS);
    distancia = (double)sqrt((p.getx() - new_x) * (p.getx() - new_x) + (p.gety() - new_y) * (p.gety() - new_y));
    if (distancia > 2*ANCHO)
      return 0;
    if (barras_ocupadas[barra]) 
      return p_potencial(rango, barra);
    //Evitamos que estén justo donde van las barras
    static double redondeo; //demasiada precisión en doubles
    redondeo = ceil(rango * PRECISION) / PRECISION;
    if (redondeo < BORDE_INF_DEF || redondeo > BORDE_SUP_DEF){
      return p_potencial(rango, barra);
    }
    //Miramos los bordes (1 arcseg por cada lado)
    if (conf.noborder) 
      if (redondeo <= BORDE_INF || redondeo >= BORDE_SUP)
        return p_potencial(rango, barra);
    if (conf.beamswitching) {
      if (orientacion == ARRIBA) 
        if (redondeo < BARRA2_3)
          return p_potencial(rango, barra);
      if (orientacion == ABAJO)
        if (redondeo > BARRA1_3)
          return p_potencial(rango, barra);
    }
    return !barras_ocupadas[barra];
  }
  return 0;
}

void CSU::actualizar(const int &b) {
  static set<Element> newsp;
  newsp.clear();
  static set<Element>::iterator it;
  static Element p;
  if (b == 0) 
    dist_max = dist_min = INF;
  for (it = puntos.begin(); it != puntos.end(); it++) {
    p = *it;
    static double new_x, new_y, zone, rango;
    static int barra;
    testeo(p, new_x, new_y);
    zone = sqrt((Ax - new_x) * (Ax - new_x) + (Ay - new_y) * (Ay - new_y));
	  barra = (int)(zone / DIST_BARRAS);
    //testeamos que se movió correctamente
/*    if (it->getbarra()+b != barra) {
      cout << "WARNING - Punto de la exbarra " << it->getbarra() << " en barra " 
           << barra << " en lugar de en la " << it->getbarra()+b << endl;
      sleep(3);
    }
*/
    p.setbarra(barra);
    //testeamos que sigue en su sitio
    rango = zone - (barra * DIST_BARRAS);
/*    if (rango != it->getzona()) {
      if (abs(rango - it->getzona()) > 0.000001){
        cout << "WARNING - El punto de la barra " << barra << " ha cambiado su zona en "
             << rango-it->getzona() << " arcseg de distancia" << endl;
        sleep(3);
      }
    }
*/
    p.setzona(rango);
    static double dist;
    dist = (double)sqrt((p.getx() - new_x) * (p.getx() - new_x) + (p.gety() - new_y) * (p.gety() - new_y));
    p.setdist(dist);
    //Si los movimientos son laterales (b = 0) actualizamos las distancias
    if (b == 0) {
      if (dist < dist_min) {
        dist_min = dist;
      }
      if (2*ANCHO-dist < dist_max) {
        dist_max = 2*ANCHO-dist;
      }
      distancia_punto[barra] = dist;
    }
/*    else { //Comprobamos que no han cambiado
      if (dist != it->getdist()) {
        if (abs(dist - it->getdist()) > 0.000001){
          cout << "WARNING - El punto de la barra " << barra << " ha cambiado en "
               << dist-it->getdist() << " arcseg de distancia" << endl;
          sleep(3);
        }
      }
    }
*/
    newsp.insert(p);
  }
/*  if (puntos.size() != newsp.size()) {
    cout << "Error" << endl;
    exit(0);
  }
*/  
  puntos.clear();
  puntos = newsp;
}

void CSU::comprobacion() const {
  CSU test(x,y,alfa,orientacion);
  static set<Element>::iterator s2;
  s2 = puntos.begin();
  while (s2 != puntos.end()) {
    static int barra;
    static double dist, zona;
    if(test.estaDentro(*s2, barra, dist, zona) == 1) {
      Element p = *s2;
      p.setbarra(barra);
      p.setdist(dist);
      p.setzona(zona);
      test.pointAdd(p);
    }
		else {
			cout << "El punto " << s2->getid() << " de la barra " << s2->getbarra() << " no está dentro" << endl;
			cout << "El resultado que muestra es el : " << test.estaDentro(*s2, barra, dist, zona) << endl;
			cout << "La barra que debería estar es " << barra << " y su zona es " << zona << endl;
      cout << std::fixed << "diferencia inferior= " << zona - limiteI << endl;
      cout << std::fixed << "diferencia superior= " << zona - limiteS << endl;
		}
    s2++;
  }
  if (puntos.size() != test.size()) {
    cout << puntos.size() << " - " << test.size() << endl;
  }
}

/* Esta mejora traslada el punto central del apuntado dejando la barra '0' con un elemento */
void CSU::mejoraArriba() {
  static int i, j, z;
  static double dist;
  i = CERO;
  while (!barras_ocupadas[i])
    i++;
  if (i != CERO) {
    for (j = CERO; j+i < NUM_BARRAS; j++){
      barras_ocupadas[j] = barras_ocupadas[j+i];
    }
    for (j = NUM_BARRAS - i; j < NUM_BARRAS; j++){
      barras_ocupadas[j] = false;
    }
    dist = i * DIST_BARRAS;
    if (alfa == CERO) { //es vertical, subimos la Y
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
    actualizar(-i);
  }
  //comprobacion();
}

void CSU::mejoraAbajo() {
  static int i, j, z;
  static double dist;
  i = NUM_BARRAS - 1;
  while (!barras_ocupadas[i])
    i--;
  if (i != NUM_BARRAS - 1) {
    for (j = CERO; i-j >= CERO; j++) {
      barras_ocupadas[NUM_BARRAS - j - 1] = barras_ocupadas[i - j];
    }
    for (j = NUM_BARRAS - i - 2; j >= CERO; j--){
      barras_ocupadas[j] = false;
    }
    dist = (NUM_BARRAS - 1 - i) * DIST_BARRAS;
    if (alfa == CERO) { //es vertical, bajamos la Y
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
    actualizar(NUM_BARRAS-i-1);
  }
  //comprobacion();
}

void CSU::mejoraIzquierda() {
  static int j;
  static double dist;
  if (dist_min > 0.2) {
  dist = dist_min - 0.1;
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
  actualizar(0);
  }
  //comprobacion();
}

void CSU::mejoraDerecha() {
  static int j;
  static double dist;
  if (dist_max > 0.2) {
  dist = dist_max - 0.1;
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
  actualizar(0);
  }
  //comprobacion();
}

bool CSU::colision (const CSU &csu) const {
  if((double)sqrt((csu.getx() - x) * (csu.getx() - x) + (csu.gety() - y) * (csu.gety() - y)) < 30)
    return true;
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
  static double d, z;
  CSU vacia (csu.getx(), csu.gety(), csu.getalfa());
  for (p = puntos.begin(); p != puntos.end(); p++)
    if (vacia.estaDentro(*p,b,d,z))
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

void CSU::getABCD(double ar[]) const {
  ar[0] = Ax; ar[1] = Ay;
  ar[2] = Bx; ar[3] = By;
  ar[4] = Cx; ar[5] = Cy;
  ar[6] = Dx; ar[7] = Dy;
}
