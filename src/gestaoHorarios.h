#ifndef GESTAO_HORARIOS_H
#define GESTAO_HORARIOS_H

#include <iostream>
#include <list>
#include <set>
#include <queue>

#include "estudante.h"
#include "horario.h"
#include "pedidos.h"


class GestaoHorarios{
    std::set<Estudante> estudantes;
    std::list<Horario> horarios;
    std::queue<Pedidos> pedidos_pendentes;
};

#endif