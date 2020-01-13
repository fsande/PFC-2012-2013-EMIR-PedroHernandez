#include <sstream>
#include <cctype>
#include <functional>
#include <algorithm>
#include "parser.h"
#include "dbscan.h"

/************************************************************//**
 * \file parser.C
 * \brief Archivo de definiciones de la clase Parser
 *
 * Implementación de los métodos de la clase Parser
 ****************************************************************/

using namespace std;

double equis, ye;
int pri, iden;

string stoupper(const string& s) {
  string result(s);
  transform(s.begin(),s.end(),result.begin(),ptr_fun <int, int> (toupper));
  return result;
}


Parser :: Parser() : xmlpp::SaxParser() {
  Q.clear();
  nodo = "";
  nuevo = 0;
  height = 3600;
  widht = 3600;
}

Parser :: Parser(char* nombre) : xmlpp::SaxParser() {
  Q.clear();
  height = 3600;
  widht = 3600;
  fich.open(nombre);
  if (fich.is_open()){
    //cout << "Fichero abierto con exito" << endl;
    //ofstream out("out.xml");
    //out << "<Observables>" << endl;
    int i = 0;
    while (!fich.eof()) {
      //out << "\t<Element id=\"" << i << "\">" << endl;
      double x, y;
      int p;
      fich >> x;
      //out << "\t\t<X>" << x << "</X>" << endl;
      fich >> y;
      //out << "\t\t<Y>" << y << "</Y>" << endl;
      fich >> p;
      //out << "\t\t<Prioridad>" << p << "</Prioridad>" << endl;
      //out << "\t</Element>" << endl;
      fich.ignore(10, '\n');
      Element punto(x, y, p);
      i++;
      Q.insert(punto);
      //cout << "Añadido punto (" << punto.getx() << "," << punto.gety() << ")" << endl;
    }
    //out << "</Observables>" << endl;
    //out.close();
    fich.close();
  }
  else
    cerr << "Problemas con el fichero" << endl;
}

Parser::~Parser() {
}

#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
void Parser::on_start_document() {
 // cout << "on_start_document()" << endl;
}

void Parser::on_end_document() {
//  cout << "on_end_document()" << endl;
}

void Parser::on_start_element(const Glib::ustring& name,
                              const AttributeList& attributes) {
  //cout << "node name = " << name << endl;
  nodo = name;

  // Print attributes:
  for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
    try{
      if (iter->name != "")
        ;//cout << "  Attribute name = " << iter->name << "en nodo " << nodo << endl;
    }
    catch(const Glib::ConvertError& ex) {
      cerr << "Parser::on_start_element(): Exception caught while converting name for cout: " << ex.what() << endl;
    }

    try {
      if (iter->value != "") {
        //cout << "    , value= " << iter->value << endl;
        stringstream value(iter->value);
        int val;
        value >> val;
        if (stoupper(nodo) == "OBSERVABLES") {
          if (stoupper(iter->name) == "HEIGHT")
            height = val;
          else if (stoupper(iter->name) == "WIDHT")
            widht = val;
        }
        else if (stoupper(iter->name) == "ID")
          iden = val;
      }
    }
    catch(const Glib::ConvertError& ex) {
      cerr << "Parser::on_start_element(): Exception caught while converting value for cout: " << ex.what() << endl;
    }
  }
}

void Parser::on_end_element(const Glib::ustring& /* name */){
  //cout << "on_end_element() " << nodo << " con datos = " << nuevo << endl;
  nodo = "";
  if (nuevo == 3) {
    nuevo = 0;
    Element point(equis, ye, pri);
    Q.insert(point);
    punto.clear();
  }
}

void Parser::on_characters(const Glib::ustring& text) {
  try {
    stringstream value(text);
    double dval;
    value >> dval;
    //cout << "on_characters(): " << text << endl;
    if (stoupper(nodo) == "X") {
      equis = dval;
      nuevo++;
    }
    else if (stoupper(nodo) == "Y") {
      ye = dval;
      nuevo++;
    }
    else if (stoupper(nodo) == "PRIORIDAD") {
      pri = (int)dval;
      nuevo++;
    }
  }
  catch(const Glib::ConvertError& ex) {
    cerr << "Parser::on_characters(): Exception caught while converting text for cout: " << ex.what() << endl;
  }
}

void Parser::on_comment(const Glib::ustring& text) {
  try {
    if (text != "")
      ;//cout << "on_comment(): " << text << endl;
  }
  catch(const Glib::ConvertError& ex) {
    cerr << "Parser::on_comment(): Exception caught while converting text for cout: " << ex.what() << endl;
  }
}

void Parser::on_warning(const Glib::ustring& text) {
  try {
    if (text != "")
      cout << "on_warning(): " << text << endl;
  }
  catch(const Glib::ConvertError& ex) {
    cerr << "Parser::on_warning(): Exception caught while converting text for cout: " << ex.what() << endl;
  }
}

void Parser::on_error(const Glib::ustring& text) {
  try {
    cout << "on_error(): " << text << endl;
  }
  catch(const Glib::ConvertError& ex) {
    cerr << "Parser::on_error(): Exception caught while converting text for cout: " << ex.what() << endl;
  }
}

void Parser::on_fatal_error(const Glib::ustring& text) {
  try {
    cout << "on_fatal_error(): " << text << endl;
  }
  catch(const Glib::ConvertError& ex) {
    cerr << "Parser::on_characters(): Exception caught while converting value for cout: " << ex.what() << endl;
  }
}
#endif

