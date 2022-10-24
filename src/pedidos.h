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
    Turma turma_inicio;
    Turma turma_final;
public:
    Pedidos(int numero_up, TipoPedido tipo, Turma turma);
    Pedidos(int numero_up, TipoPedido tipo, Turma turma_inicio, Turma turma_final);
    bool conflito();
    bool desiquilibrio();
    void adicionar_turma();
    void remover_turma();
    void alterar_turma();
};



#endif