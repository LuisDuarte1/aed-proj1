

#include <iostream>
#include <algorithm>
#include "pedidos.h"
#include "estudante.h"
#include "gestaoHorarios.h"


Pedido::Pedido(int nup, TipoPedido tipo, std::shared_ptr<Turma> turma){
    this->nup=nup;
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

std::shared_ptr<Turma> Pedido::get_turmaf(){
    return turma_final;
}
std::shared_ptr<Turma> Pedido::get_turmai(){
    return turma_inicio;
}

TipoPedido Pedido::gettipo(){
    return this->tipo;
}

int Pedido::getnup() {
    return nup;
}

bool ConjuntoPedidos::desiquilibrio(){
    for(Pedido pedido : lista_pedidos){
        if(pedido.gettipo()==Remover) continue;
        std::vector<std::shared_ptr<Turma>> turmas_curso;
        std::string uc_c = pedido.get_turmaf()->getuc_code();
        std::copy_if(GestaoHorarios::turmas.begin(),
                     GestaoHorarios::turmas.end(),
                     std::back_inserter(turmas_curso),
                     [uc_c](std::shared_ptr<Turma> turma){
                         return turma->uc_code == uc_c;
                     });
        int min = INT_MAX;
        for(std::shared_ptr<Turma> turma : turmas_curso){
            if(turma->getestudantes()<min) min = turma->getestudantes();
        }
        if(pedido.gettipo()==TipoPedido::Adicionar){
            if(min+3<pedido.get_turmaf()->getestudantes()) return true;}
        else if(pedido.get_turmai()->getestudantes()!=min){
            if(min+3<pedido.get_turmaf()->getestudantes()) return true;}
        else{
            if(min+2<pedido.get_turmaf()->getestudantes()) return true;
        }}
    return false;
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
    if(lista_pedidos.size() == 0 ) return true;
    auto it = GestaoHorarios::estudantes.find(Estudante(lista_pedidos.begin()->getnup(), ""));
    std::list<std::shared_ptr<Turma>> novasturmas = it->getTurmas();
    for(Pedido pedido : lista_pedidos){
        if(pedido.gettipo()==Remover){
            novasturmas.remove(pedido.get_turmai());}
        else if(pedido.gettipo()==Adicionar){
            novasturmas.push_back(pedido.get_turmaf());}
        else{
            novasturmas.push_back(pedido.get_turmaf());
            novasturmas.remove(pedido.get_turmai());}
    }
    std::list<std::pair<Slot, std::shared_ptr<Turma>>> novohorario;
    for(std::shared_ptr<Turma> turma : novasturmas){
        for(Slot aula : turma->getaulas()){
            if(aula.gettipo_aula()!=Teorica)
                novohorario.push_back(std::make_pair(aula, turma));}}
    for(auto aula1 : novohorario){
        for(auto aula2 : novohorario){
            if(aula1.second == aula2.second) continue;
            if(aula1.first.getdia()!=aula2.first.getdia()) continue;
            if((aula1.first.geth_inicio()<aula2.first.geth_inicio() && aula1.first.geth_final()>aula2.first.geth_inicio()) || (aula1.first.geth_inicio()<aula2.first.geth_final() && aula1.first.geth_final()>aula2.first.geth_final()) || (aula1.first.geth_inicio()==aula2.first.geth_final() && aula1.first.geth_final()==aula2.first.geth_final()))
                return true;
        }
    }
    return false;
}

void ConjuntoPedidos::adicionarpedido(Pedido pedido){
    lista_pedidos.push_back(pedido);
}



