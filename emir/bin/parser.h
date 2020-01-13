#ifndef PARSER_H
#define PARSER_H

#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <libxml++/libxml++.h>
#include <glibmm/convert.h>
#include "element.h"

/************************************************************//**
 * \file parser.h
 * \brief Archivo de cabeceras
 * Definición de la clase parser
 ****************************************************************/

using namespace std;

/************************************************************//**
 * \class Parser
 * \brief Clase que hereda de la clase SaxParser, definida en la
 *        librería libxml++, cuya función es actuar como un parser
 *        de XML.
 ****************************************************************/

class Parser: public xmlpp::SaxParser {
  set<Element> Q;
  ifstream fich;
  Element punto;
  string nodo;
  int nuevo, widht, height;

  #ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
  virtual void on_start_document();
  virtual void on_end_document();
  virtual void on_start_element(const Glib::ustring& name,
                                const AttributeList& properties);
  virtual void on_end_element(const Glib::ustring& name);
  virtual void on_characters(const Glib::ustring& characters);
  virtual void on_comment(const Glib::ustring& text);
  virtual void on_warning(const Glib::ustring& text);
  virtual void on_error(const Glib::ustring& text);
  virtual void on_fatal_error(const Glib::ustring& text);
  #endif

  public:
    /************************************************************//**
     * \fn Parser();
     * \brief Constructor por defecto
     * \param - No necesita argumentos
     ****************************************************************/
    Parser();
    /************************************************************//**
     * \fn Parser(char* nombre);
     * \brief Constructor para unos valores concretos. Realiza el 
     *        procesado del archivo.
     * \param nombre Nombre del fichero XML de entrada.
     ****************************************************************/
    Parser(char* nombre);
    /************************************************************//**
     * \fn vector<Element> getList();
     * \brief Obtiene el vector de puntos totales
     * \param - No necesita argumentos
     * \return Lista de Element que componen el problema
     ****************************************************************/
    set<Element> getList() {return Q;}
    /************************************************************//**
     * \fn virtual ~Parser();
     * \brief Destructor por defecto
     * \param - No necesita argumentos
     ****************************************************************/
    virtual ~Parser();
    /************************************************************//**
     * \fn int getHeight() const
     * \brief Obtiene el tamaño del eje vertical del problema
     * \param - No necesita argumentos.
     * \return Valor total del eje Y
     ****************************************************************/
    int getHeight() const {return height;}
    /************************************************************//**
     * \fn int getWidht() const
     * \brief Obtiene el tamaño del eje horizontal del problema
     * \param - No necesita argumentos.
     * \return Valor total del eje X
     ****************************************************************/
    int getWidht() const {return widht;}

};

#endif
