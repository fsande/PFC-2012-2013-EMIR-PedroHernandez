#include "element.h"

/************************************************************//**
 * \file element.C
 * \brief Archivo de definiciones de la clase Element
 *
 * Implementación de los métodos de la clase Element
 ****************************************************************/

using namespace std;

/* Constructor de la clase Element */
Element :: Element (double posx, double posy, int pri) {
  id = identificador++;
  x = posx;
  y = posy;
  prioridad = pri;
  barra = -1;
  //apuntado = NULL;
}

void Element :: clear() {
  id = 0;
  x = 0;
  y = 0;
  prioridad = 0;
  barra = -1;
  //apuntado = NULL;
}

bool Element :: operator < (const Element &element) const {
  switch (orden) {
    case 4: // Prioridad
      if (prioridad < element.getprior())
        return true;
      if (prioridad > element.getprior())
        break;
    case 0: // Menor X
      if (x < element.getx())
        return true;
      else
        if ((y < element.gety()) && (x == element.getx()))
          return true;
      break;
    case 1: //Mayor X
      if (x > element.getx())
        return true;
      else
        if ((y < element.gety()) && (x == element.getx()))
          return true;
      break;
    case 2: //Menor Y
      if (y < element.gety())
        return true;
      else
        if ((x < element.getx()) && (y == element.gety()))
          return true;
      break;
    case 3: //Mayor Y
      if (y > element.gety())
        return true;
      else
        if ((x < element.getx()) && (y == element.gety()))
          return true;
      break;
  }
  return false;
}

bool Element :: operator == (const Element &element) const {
  if (id == element.getid())
    return true;
  return false;
}

