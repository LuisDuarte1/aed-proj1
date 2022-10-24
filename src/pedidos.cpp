

#include <iostream>
#include "pedidos.h"

Pedidos::Pedidos(int numero_up, TipoPedido tipo, Turma turma){
    this->numero_up=numero_up;
    this->tipo=tipo;
    if(tipo==TipoPedido::Adicionar){
        this->turma_inicio=turma;}
    else{
        this->turma_final=turma;}
}

Pedidos::Pedidos(int numero_up, TipoPedido tipo, Turma turma_inicio, Turma turma_final){
    this->numero_up=numero_up;
    this->tipo=tipo;
    this->turma_inicio=turma_inicio;
    this->turma_final=turma_final;
}

bool Pedidos::desiquilibrio(){
    if(this->turma_inicio.getestudantes()<this->turma_final.getestudantes()+3)
        return true;
    return false;
}

void Pedidos::adicionar_turma(){
    this->turma_final.addestudantes();

}
