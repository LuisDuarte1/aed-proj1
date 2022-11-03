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
    std::shared_ptr<Turma> get_turmaf();
    std::shared_ptr<Turma> get_turmai();
    TipoPedido gettipo();
    int getnup();
};


class ConjuntoPedidos{
public:
    std::list<Pedido> lista_pedidos;
    bool conflito();
    bool desiquilibrio();
    void adicionarpedido(Pedido pedido);
};

#endif