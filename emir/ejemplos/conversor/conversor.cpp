#include <fstream>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <cfloat>

using namespace std;

const int MIL = 10000;
const string RUTA_RES = "../xml/";

int main(int argc, char** argv) {
  int moreX = 0, moreY = 0, grados = 1;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-g2a") == 0) { //hay que pasarlo a arcseg
      grados = 3600;
      cout << "Convirtiendo a grados" << endl;
    }
    if (strcmp(argv[i],"--help") == 0) {
      cout << "Uso: ./conversor-dat-xml [-g2a] archivo\n\t-g2a: pasa de grados a arcoseg" << endl;
      exit(0);
    } 
  }
  ifstream fichin;
  double x[MIL], y[MIL];
  int total = 0, p[MIL];
  //Abrimos el fichero de los objetos a visualizar
  fichin.open(argv[argc-1]);
  if (fichin.fail() || fichin.bad()) {
    cout << "El fichero "<< argv[argc-1] << " no existe o no se puede abrir" << endl;
    return 0;
  }
  string entrada = argv[argc-1], nombre = RUTA_RES, entrada2 = "../";
  unsigned pos = entrada.find_last_of('/');
  nombre += entrada.substr(++pos, entrada.length()-pos-5);
  entrada2 += entrada.substr(pos, entrada.length()-pos-4);
  nombre += ".xml";
  entrada2 += "-converted.dat";
  double maxX, maxY, minX, minY;
  while (!fichin.eof()) {
    total++;
    fichin >> x[total];
    fichin >> y[total];
    fichin >> p[total];
    fichin.ignore(10, '\n');
    x[total] *= grados;
    y[total] *= grados;
  }
  fichin.close();
  maxX = minX = x[1];
  maxY = minY = y[1];
  for (int i = 1; i < total; i++) {
    if (x[i] > maxX)
      maxX = x[i];
    if (y[i] > maxY)
      maxY = y[i];
    if (x[i] < minX) 
      minX = x[i];
    if (y[i] < minY)
      minY = y[i];
  }
  moreX = 10 - minX;
  moreY = 10 - minY;
  ofstream ent2(entrada2.c_str());
  ofstream fichout(nombre.c_str());
  fichout << "<Observables widht=\"" << maxX+moreX << "\" height=\"" << maxY+moreY << "\">" << endl;
  for (int i = 1; i < total; i++) {
    fichout << "\t<Element id=\"" << i << "\">" << endl;
    fichout << fixed << "\t\t<X>" << x[i]+moreX << "</X>" << endl;
    fichout << fixed << "\t\t<Y>" << y[i]+moreY << "</Y>" << endl;
    fichout << "\t\t<Prioridad>" << p[i] << "</Prioridad>" << endl;
    fichout << "\t</Element>" << endl;
    ent2 << fixed << x[i]+moreX << "\t" << y[i]+moreY << "\t" << p[i] << endl;
  }  
  fichout << "</Observables>" << endl;
  fichout.close();
  cout << "Convertidos " << total - 1 << " puntos en " << nombre <<endl;
  cout << "Entrada convertida en " << entrada2 << endl;
  cout << "Se ha movido el origen en (" << moreX << "," << moreY << ")" << endl;
}

