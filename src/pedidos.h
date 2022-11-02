#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <memory>

#include "turma.h"


enum TipoPedido{
    Adicionar,
    Remover,
    Mudar
};

class Pedidos{
    int numero_up;
    TipoPedido tipo;
    std::shared_ptr<Turma> turma_inicio;
    std::shared_ptr<Turma> turma_final;
public:
    Pedidos(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma);
    Pedidos(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma_inicio, std::shared_ptr<Turma> turma_final);
    bool conflito();
    bool desiquilibrio();
    void adicionar_turma();
    void remover_turma();
    void alterar_turma();
};



#endif