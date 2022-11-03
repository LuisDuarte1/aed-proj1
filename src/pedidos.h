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
    /**
     * @brief Verifica se dois pedidos são iguais excluindo o n_up.
     * 
     * @param p2 
     * @return true se forem iguais
     * @return false se forem diferentes
     */
    bool operator==(const Pedido& p2);
    /**
     * @brief Alterna a turma de um determinado estudante de uma UC
     */
    void alterar_turma();
    /**
     * @brief Get the Tipo Pedido object
     * 
     * @return TipoPedido 
     */
    inline TipoPedido getTipoPedido() const {return tipo;};
    /**
     * @brief Get the Student Number object
     * 
     * @return int 
     */
    inline int getStudentNumber() const {return nup;};
    /**
     * @brief Get the Turma Inicio object
     * 
     * @return std::shared_ptr<Turma> 
     */
    inline std::shared_ptr<Turma> getTurmaInicio() const {return turma_inicio;};
    /**
     * @brief Get the Turma Final object
     * 
     * @return std::shared_ptr<Turma> 
     */
    inline std::shared_ptr<Turma> getTurmaFinal() const {return turma_final;};

};


class ConjuntoPedidos{
public:
    /**
     * @brief Construtor de ConjuntoPedidos sem pedidos iniciais
     * 
     */
    ConjuntoPedidos();
    /**
     * @brief Construtor de ConjuntoPedidos com pedidos iniciais
     * 
     * @param lista lista a adicionar ao conjunto de pedidos
     */
    ConjuntoPedidos(std::list<Pedido> lista);
    std::list<Pedido> lista_pedidos;
    /**
     * @brief Verfica se há pedidos neste conjunto que surgem
     * num conflito de horários. 
     * (Exclui as teóricas.)
     * Complexidade(n^2)
     * 
     * @return true se houver conflito
     * @return false se não houver conflito
     */
    bool conflito();
    /**
     * @brief Verifica quais os pedidos surgem num desequilibrio de turmas e retorna
     * os pedidios que surgem nelas. Se não existir desquilibrio retorna uma lista vazia
     * Complexidade(n^2)
     * @return std::list<Pedido> lista com pedidos que surgem num desequilibrio de turmas
     */
    std::list<Pedido> desiquilibrio();
    /**
     * @brief Adiciona um pedido ao conjunto de pedidos.
     * Complexidade O(1)
     * 
     * @param pedido a adicionar
     */
    void adicionarpedido(Pedido pedido);
    /**
     * @brief Verifica na integra, se entre dois conjuntos de pedidos eles são
     * estritamente iguais e na mesma ordem.
     * 
     * @param p2 segundo conjuntopedido
     * @return true se for igual
     * @return false se for diferente
     */
    bool operator==(const ConjuntoPedidos& p2) const;
};

#endif