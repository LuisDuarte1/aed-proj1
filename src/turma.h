#ifndef TURMA_H
#define TURMA_H

#include <iostream>
#include <list>

#include "slot.h"

/**
 * @brief Class que guarda a informação sobre a turma. Quando é adicionado esta turma aos estudantes, é necessario atualizar o counter 
 * 
 * 
 */
struct Turma{
    std::string class_code;
    std::string uc_code;

    int estudantes; //Atenção! esta variavel deve ser atualizada quando um aluno é adicionado a ou removido a esta

    std::list<Slot> aulas;


public:
    /**
     * @brief Compara se o uc_code e o class_code são iguais, a quantidade de estudantes não é relevante.
     *
     * @param outra_turma Outra turma para comparação.
     * @return true se for igual
     * @return false se for diferente
     */
    bool operator==(const Turma& outra_turma);
    /**
     * @brief Retorna o número de estudantes
     * @return número de estudantes em int
     */
    int getestudantes();
    /**
     * @brief Adiciona 1 estudante a Turma
     */
    void addestudantes();
    /**
     * @brief Remove 1 estudante a Turma
     */
    void removeestudantes();
    /**
     * @brief Retorna a lista de parâmetro Slot com as aulas da Turma
     * @return std::list<Slot> aulas
     */
    std::list<Slot> getaulas();
    /**
     * @brief Retorna o código da UC.
     * @return std::string uc_code.
     */
    std::string getuc_code();
};

#endif