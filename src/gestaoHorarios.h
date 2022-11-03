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
         * Complexidade O(n^2)
         */
        static void lerFicheiros();


        /**
         * @brief Guarda os dados em memória para ficheiros .csv que já existem.
         * Atenção que os .csv devem ser postos na pasta recursos FORA da pasta de build do CMake.
         * Complexidade O(n^2)
         * 
         */
        static void guardarFicheiros();
        
        static void processarPedidos();
        static void aceitarpedidos(ConjuntoPedidos conjuntopedidos);
};

/**
 * @brief Converte o tipo de aula para uma string equivalente usada principalmente nos .csv
 * 
 * @param t Tipo de aula
 * @return std::string Tipo de aula em string
 */
std::string convertTipoAula(Tipo t);


#endif