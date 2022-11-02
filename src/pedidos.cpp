

#include <iostream>
#include "pedidos.h"
#include "estudante.h"
#include "gestaoHorarios.h"

Pedido::Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma){
    this->nup=numero_up;
    this->tipo=tipo;
    if(tipo==TipoPedido::Adicionar){
        this->turma_inicio=turma;}
    else{
        this->turma_final=turma;}
}

Pedido::Pedido(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma_inicio, std::shared_ptr<Turma> turma_final){
    this->nup=numero_up;
    this->tipo=tipo;
    this->turma_inicio=turma_inicio;
    this->turma_final=turma_final;
}

bool ConjuntoPedidos::desiquilibrio(){
}

void Pedido::adicionar_turma(){
    auto it = GestaoHorarios::estudantes.find(Estudante(this->nup, ""));
    adicionarEstudanteTurma(GestaoHorarios::estudantes,*it,turma_final);
}

void Pedido::remover_turma(){
    auto it = GestaoHorarios::estudantes.find(Estudante(this->nup, ""));
    removerEstudanteTurma(GestaoHorarios::estudantes,*it,turma_inicio);
}

void Pedido::alterar_turma(){
    auto it = GestaoHorarios::estudantes.find(Estudante(this->nup, ""));
    removerEstudanteTurma(GestaoHorarios::estudantes,*it,turma_inicio);
    adicionarEstudanteTurma(GestaoHorarios::estudantes,*it,turma_final);
}

bool ConjuntoPedidos::conflito(){


}