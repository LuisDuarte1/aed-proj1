#ifndef GESTAO_HORARIOS_H
#define GESTAO_HORARIOS_H

#include <iostream>
#include <list>
#include <set>
#include <queue>

#include "estudante.h"
#include "pedidos.h"


class GestaoHorarios{
    public:
        std::set<Estudante> estudantes;
        std::queue<Pedidos> pedidos_pendentes;
        std::list<std::shared_ptr<Turma>> turmas; 

        /**
         * @brief Lê os ficheiros .csv para carregar os estudantes. 
         * Atenção que os .csv devem ser postos na pasta recursos FORA da pasta de build do CMake.
         * 
         */
        void lerFicheiros();
};

#endif