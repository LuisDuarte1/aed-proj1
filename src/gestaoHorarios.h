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
        static std::queue<ConjuntoPedidos> pedidos_recusados; // <3 

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
        
        /**
         * @brief Processa todos os pedidos num estilo relativamente FIFO.
         * Faz o seguinte:
         *  - Remove todos os pedidos com conflito
         *  - Tenta encontrar pedidos com desequilibrio e tenta encontrar matches noutros conjuntos de pedidos
         * que a resolvam.
         *  - Se as dependencias dos pedidos a seguir não conseguirem ser cumpridas, 
         * elimina o mesmo e as dependencias.
         *  - A lista final são todos os pedidos que possam ser cumpridos.
         *
         * 
         * Complexidade: n^4
         * 
         */
        static void processarPedidos();

        /**
         * @brief Aceita o conjunto pedido fazendo as alterações necessárias nas estruturas
         * de dados do GestaoHorarios.
         * Complexidade(n)
         * @param conjuntopedidos a aceita.
         */
        static void aceitarpedidos(ConjuntoPedidos conjuntopedidos);
};

/**
 * @brief Converte o tipo de aula para uma string equivalente usada principalmente nos .csv
 * Complexidade(n)
 * @param t Tipo de aula
 * @return std::string Tipo de aula em string
 */
std::string convertTipoAula(Tipo t);


#endif