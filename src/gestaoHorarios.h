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
        static std::set<Estudante> estudantes;
        static std::list<ConjuntoPedidos> pedidos_pendentes;
        static std::list<std::shared_ptr<Turma>> turmas;
        static std::list<ConjuntoPedidos> pedidos_recusados;

        /**
         * @brief Lê os ficheiros .csv para carregar os estudantes. 
         * Atenção que os .csv devem ser postos na pasta recursos FORA da pasta de build do CMake.
         * 
         */
        void lerFicheiros();
        static void processarPedidos();
        static void aceitarpedidos(ConjuntoPedidos conjuntopedidos);
};

#endif