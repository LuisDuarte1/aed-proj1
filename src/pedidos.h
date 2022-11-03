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
    /**
     * @brief Cria um determinado pedido de um determinado tipo,estudante e turma.
     * Nota: caso o tipo for "Adicionar" o parâmetro turma deverá ser a turma final.
     * Caso o tipo for "Remover" o parâmetro turma deverá ser a turma inicial.
     *
     * @param numero_up int nup
     * @param tipo TipoPedido tipo
     * @param turma std::shared_ptr<Turma> turma_inicio OU std::shared_ptr<Turma> turma_final (Conforme o tipo)
     */
    Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma);
    /**
     * @brief Cria um determinado pedido de um determinado tipo,estudante,turma inicial e turma final.
     * Uma versão mais ""completa"" da função construtora de mesmo nome com 3 parâmetros.
     *
     * @param numero_up int nup
     * @param tipo TipoPedido tipo
     * @param turma_inicio std::shared_ptr<Turma> turma_inicio
     * @param turma_final std::shared_ptr<Turma> turma_final
     */
    Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma_inicio, std::shared_ptr<Turma> turma_final);
    /**
     * @brief Adiciona um estudante a uma determinada turma de uma UC
     */
    void adicionar_turma();
    /**
     * @brief Remove um estudante a uma determinada turma de uma UC
     */
    void remover_turma();
    bool operator==(const Pedido& p2);
    std::shared_ptr<Turma> get_turmaf();
    std::shared_ptr<Turma> get_turmai();
    TipoPedido gettipo();
    int getnup();
    /**
     * @brief Alterna a turma de um determinado estudante de uma UC
     */
    void alterar_turma();

    inline TipoPedido getTipoPedido() const {return tipo;};
    inline int getStudentNumber() const {return nup;};
    inline std::shared_ptr<Turma> getTurmaInicio() const {return turma_inicio;};
    inline std::shared_ptr<Turma> getTurmaFinal() const {return turma_final;};

};


class ConjuntoPedidos{
public:
    ConjuntoPedidos();
    ConjuntoPedidos(std::list<Pedido> lista);
    std::list<Pedido> lista_pedidos;
    bool conflito();
    std::list<Pedido> desiquilibrio();
    void adicionarpedido(Pedido pedido);
    
    bool operator==(const ConjuntoPedidos& p2) const;
};

#endif