#ifndef PEDIDOS_H
#define PEDIDOS_H

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

};


#endif