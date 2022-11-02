#ifndef ESTUDANTE_H
#define ESTUDANTE_H

#include <iostream>
#include <list>
#include <memory>
#include <set>

#include "turma.h"

class Estudante{
    int numero_up;
    std::string nome;
    std::list<std::shared_ptr<Turma>> turmas_inscrito;

    public:
        /**
         * @brief Construtor para um novo objeto estudante
         * 
         * @param _numero_up Novo número_up que não deve ser duplicado
         * @param _nome Novo nome do estudante
         */
        Estudante(int _numero_up, std::string _nome);

        /**
         * @brief Função para comparar dois estudantes. Usa só o número_up para o fazer, já que este deve ser único.
         * Complexidade: O(1)
         * 
         * @param a Estudante para comparar
         * @return true Se número up for igual.
         * @return false Se número up for diferente
         */
        bool operator==(const Estudante& a);

        /**
         * @brief Função para ver se o número de estudante é menor em relação a outro estudante.
         * Principalmente usada para o std::set
         * Complexidade: O(1)
         * 
         * @param a Estudante
         * @param b Outro estudante
         * @return true se número_up do a for menor do que número_up do b
         * @return false se número_up do a for maior do que número_up do b
         */
        friend bool operator<(const Estudante& a, const Estudante& b);

        /**
         * @brief Vai buscar a este Objeto Estudante o respetivo número_up
         * Complexidade: O(1)
         * 
         * @return int 
         */
        inline int getStudentNumber() const {return numero_up;};



        /**
         * @brief Vai buscar uma cópia da lista de turmas em que o estudante está inscrito.
         * Complexidade: O(1)
         * 
         * @return std::list<Turma> 
         */
        inline std::list<std::shared_ptr<Turma>> getTurmas() const{ return turmas_inscrito;};

        /**
         * @brief Adiciona uma turma em que o estudante vai passar a estar inscrito.
         * Esta função não faz checks se há sobreposições ou se a turma é válida ou até se está duplicada.
         * Complexidade: O(n)
         * 
         * @param nova_turma Turma para adicionar
         */
        void adicionarTurma(const std::shared_ptr<Turma>& nova_turma);

        /**
         * @brief Tenta remover uma turma em que o estudante está inscrito. 
         * Se não for sucedido, dá print para a consola (por agora). 
         * 
         * @param turma_remover Turma para remover
         */
        void removerTurma(std::shared_ptr<Turma>& turma_remover);

        /**
         * @brief Retorna uma cópia do nome do estudante 
         * 
         * @return std::string nome do estudante
         */
        inline std::string getStudentName(){return nome;};
        

};

/**
 * @brief Função global para adicionar um estudante a uma turma porque é impossível mutar um estudante 
 * diretamente de um set. Para isso mutamos o estudante, removemos esse do set e voltamos a adicionar.
 * Complexidade: log(n) já que o std::set garante o balanceamento da tree
 * 
 * 
 * @param e_set que contem todos os estudantes
 * @param estudante para a quem adiciona a turma
 * @param turma a adicionar
 */
void adicionarEstudanteTurma(std::set<Estudante>& e_set, Estudante estudante, std::shared_ptr<Turma> turma);



/**
 * @brief Função global para remover um estudante a uma turma porque é impossível mutar um estudante 
 * diretamente de um set. Para isso mutamos o estudante, removemos esse do set e voltamos a adicionar.
 * Complexidade: log(n) já que o std::set garante o balanceamento da tree
 * 
 * 
 * @param e_set que contem todos os estudantes
 * @param estudante para a quem remove a turma
 * @param turma a remover
 */
void removerEstudanteTurma(std::set<Estudante>& e_set,Estudante estudante ,std::shared_ptr<Turma> turma);

#endif