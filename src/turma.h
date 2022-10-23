#ifndef TURMA_H
#define TURMA_H

#include <iostream>

/**
 * @brief Class que guarda a informação sobre a turma. Quando é adicionado esta turma aos estudantes, é necessario atualizar o counter 
 * 
 * 
 */
struct Turma{
    std::string class_code;
    std::string uc_code;

    int estudantes; //Atenção! esta variavel deve ser atualizada quando um aluno é adicionado a ou removido a esta

    /**
     * @brief Compara se o uc_code e o class_code são iguais, a quantidade de estudantes não é relevante.
     * 
     * @param outra_turma Outra turma para comparação.
     * @return true se for igual
     * @return false se for diferente
     */
    bool operator==(const Turma& outra_turma);
};

#endif