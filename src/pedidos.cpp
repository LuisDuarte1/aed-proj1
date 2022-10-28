

#include <iostream>
#include "pedidos.h"
#include "estudante.h"

Pedidos::Pedidos(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma){
    this->numero_up=numero_up;
    this->tipo=tipo;
    if(tipo==TipoPedido::Adicionar){
        this->turma_inicio=turma;}
    else if (tipo==TipoPedido::Remover){
        this->turma_final=turma;}
    else {
        exit(1);
    }
}

Pedidos::Pedidos(int numero_up, TipoPedido tipo, std::shared_ptr<Turma> turma_inicio, std::shared_ptr<Turma> turma_final){
    this->numero_up=numero_up;
    this->tipo=tipo;
    this->turma_inicio=turma_inicio;
    this->turma_final=turma_final;
}

bool Pedidos::desiquilibrio(){
    if(this->turma_inicio->getestudantes()<this->turma_final->getestudantes()+3)
        return true;
    return false;
}

void Pedidos::adicionar_turma(){
    this->turma_final->addestudantes();
    Estudante aluno (this->numero_up,"a");
    //find

}
