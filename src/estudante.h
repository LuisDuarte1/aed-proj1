#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <iostream>
#include <list>

#include "turma.h"

class Estudante{
    int numero_up;
    std::string nome;
    std::list<Turma> turmas_inscrito;

};

#endif