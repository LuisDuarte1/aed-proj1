#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <memory>

#include "turma.h"


enum TipoPedido{
    Adicionar,
    Remover,
    Mudar
};


class Pedido{
    int nup;
    TipoPedido tipo;
    std::shared_ptr<Turma> turma_inicio;
    std::shared_ptr<Turma> turma_final;
public:
    Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma);
    Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma_inicio, std::shared_ptr<Turma> turma_final);
    void adicionar_turma();
    void remover_turma();
    void alterar_turma();
};


class ConjuntoPedidos{
public:
    std::list<Pedido> lista_pedidos;

    bool conflito();
    bool desiquilibrio();

};

#endif