# PFC-2012-2013-EMIR-PedroHernandez

************************************************************************
     _____  _____ _    _  ____        _   _           _              
    / ____|/ ____| |  | |/ __ \      | | (_)         (_)             
   | |    | (___ | |  | | |  | |_ __ | |_ _ _ __ ___  _ _______ _ __ 
   | |     \___ \| |  | | |  | | '_ \| __| | '_ ` _ \| |_  / _ \ '__|
   | |____ ____) | |__| | |__| | |_) | |_| | | | | | | |/ /  __/ |   
    \_____|_____/ \____/ \____/| .__/ \__|_|_| |_| |_|_/___\___|_|   
                               | |                                   
                               |_|                                   

************************************************************************
Introduction
************************************************************************
CSUoptimizer is an application that solves a specific problem of the EMIR
project developed by the Instituto de Astrofísica de CANARIAS (IAC).
************************************************************************
                              Contents
************************************************************************

bin               : CSUoptimizer application.
documentacion     : Code documentation with Doxygen.
ejemplos          : Example files.
ejemplos/conversor: Helper application to convert file types.
ejemplos/xml      : XML files of the examples used.
map_editor        : Accurate example's generate application
memoriaEmir       : LaTeX of this document.
Resultados        : Results files.

************************************************************************
Prerequisites 
************************************************************************
· make tool
· g++ compiler
· libxml++ library : http://libxmlplusplus.sourceforge.net/
· Allegro4 library : http://alleg.sourceforge.net/
Optional prerequisites
· Doxygen          : http://www.stack.nl/~dimitri/doxygen/
· LaTeX            : http://www.latex-project.org/  
------------------------------------------------------------------------
Installing prerequisites:
------------------------------------------------------------------------
- make tool
  $ sudo apt-get install make

- g++ compiler:
  $ sudo apt-get install g++

- libxml++ library:
  $ sudo apt-get install libxml++2.6-dev libxml++2.6-doc
  $ sudo apt-get install libgtkmm-2.4-dev

- Allegro4 library:
  $ sudo apt-get install liballegro4.2-dev

------------------------------------------------------------------------
Installing optional prerequisites:
------------------------------------------------------------------------
- Doxygen:
  $ wget http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.4.src.tar.gz
  $ tar -xzvf doxygen-1.8.4.src.tar.gz
  $ cd doxygen-1.8.4/
  $ ./configure
  - In case of fail:
    · graphviz:
      $ sudo apt-get install graphviz
    · flex:
      $ sudo apt-get install flex
    · bison:
      $ sudo apt-get install bison
    - Reconfigure again:
      $ ./configure
  $ make
  $ sudo make install

- LaTeX:
  $ sudo apt-get install texlive-extra-utils
  $ sudo apt-get install texlive-latex-extra
  $ sudo apt-get install texlive-latex-recommended
  $ sudo apt-get install texlive-full
  $ sudo apt-get install texlive-science
************************************************************************
How to install
************************************************************************
1. Decompress the csuoptimizer.tar.gz file
  $ cd ~
  $ tar -xzvf csuoptimizer.tar.gz

2. Configure and compile CSUoptimizer
  $ cd csuoptimizer/bin/
  $ make

3. Check your installation.
  $ ./csuoptimizer ../ejemplos/xml/exacto.xml

************************************************************************
                   Documentation and links
************************************************************************
  Documentation is located at
    · ~/csuoptimizer/memoriaEmir/
    · ~/csuoptimizer/documentacion/html/

  Repositories:
    . Private csuoptimizer repository: https://bitbucket.org/PHdez/emir

************************************************************************
                              Authors
************************************************************************
Pedro Orlando Hernández Martín: alu0100402193@ull.edu.es
Francisco de Sande            : fsande@ull.es
