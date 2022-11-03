//
// Created by wwwjo on 24/10/2022.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <bits/stdc++.h>


#include "gestaoHorarios.h"
#include "turma.h"
#include "slot.h"
#include "turma.h"
#include "estudante.h"
using namespace std;

        /**
         * @brief Class que inicia o menu para visualizador e opera os "outputs".
         */
class menu {
    public:
        /*!
         * @brief Esta funcão inicia o menu e recebe por input o numero da opção pretendida pelo utilizador
         * Caso o input seja inválido, ele chama a própria função.
         * Complexidade:O(n^2)
         */
        void iniciar();
        /**
         * @brief Esta função recebe por input o número mecanográfico do estudante, verifica se é valido e caso seja, chama a função menu::printhorario.
         * Caso o input seja inválido, ele chama a própria função.
         * Complexidade:O(n^2)
         */
        void estudante();
        /**
         * @brief Esta função recebe por input o numero da opção de uma UC ou de uma Turma
         * No caso de receber o numero da opção da UC este recebe por input o codigo da UC e o numero da opcao correspondida (Numero de Estudantes em Cada Turma/Estudantes em Cada Turma/Horário em Cada Turma)
         * e da output da informacao pedida.
         * No caso de receber o numero da opção da Turma este recebe por input o codigo da turma, (em determinados casos, o codigo da UC caso assim seja pretendido) e também o numero da opção (Caso se pretenda a ocupação ou o horário)
         * e dá output da informação pretendida
         * Caso o input seja inválido, ele chama a própria função.
         * Complexidade:O(n^2)
         */
        void UCandTurmaandAno();
        /**
         * @brief Esta função recebe por input o número de UCs e o numero da opção da ordenação (alfabética ou nºde UCs) e dá output da informação pretendida.
         * Caso o input seja invalido ele chama a própria função.
         * Complexidade:O(n^2)
         */
        void estudantesmaisnucs();
        /**
         * @brief Esta função recebe por output o número da opção pretendida (Remoção/Adição/Alteração/Alterações de estudante(s) de determinada(s) UC(s)/Turma(s))
         * Em todos os casos, a função recebe o número mecanografico do estudante e o código de uma determinada UC/Turma (ou de várias, conforme o pedido) e chama as respetivas funções da class pedidos.
         * Caso o input seja inválido, ele chama a própria função.
         * Complexidade:O(n^2)
         */
        void pedidosalteracao();
        /**
         * @brief Função dá output para a consola do horário de uma determinada/o Estudante/UC/Turma.
         * Complexidade:O(n^2)
         *
         * @param horarios Lista com shared pointers da class Turma
         */
        void printhorario(list<std::shared_ptr<Turma>> horarios);
};



#endif //PROJ1_AED_MENU_H
