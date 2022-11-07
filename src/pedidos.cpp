

#include <iostream>
#include <algorithm>
#include <climits>
#include "pedidos.h"
#include "estudante.h"
#include "gestaoHorarios.h"


Pedido::Pedido(int nup, TipoPedido tipo, std::shared_ptr<Turma> turma){
    this->nup=nup;
    this->tipo=tipo;
    if(tipo!=TipoPedido::Adicionar){
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


std::list<Pedido> ConjuntoPedidos::desiquilibrio(){
    std::list<Pedido> ret;
    for(Pedido pedido : lista_pedidos){
        if(pedido.getTipoPedido()==Remover) continue;
        std::vector<std::shared_ptr<Turma>> turmas_curso;
        std::string uc_c = pedido.getTurmaFinal()->getuc_code();
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
        if(pedido.getTipoPedido()==TipoPedido::Adicionar){
            if(min+3<pedido.getTurmaFinal()->getestudantes())
                ret.push_back(pedido);
            }
        else if(pedido.getTurmaInicio()->getestudantes()!=min){
            if(min+3<pedido.getTurmaFinal()->getestudantes()) ret.push_back(pedido);}
        else{
            if(min+2<pedido.getTurmaFinal()->getestudantes()) ret.push_back(pedido);
        }}
    return ret;
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
    auto it = GestaoHorarios::estudantes.find(Estudante(lista_pedidos.begin()->getStudentNumber(), ""));
    std::list<std::shared_ptr<Turma>> novasturmas = it->getTurmas();
    for(Pedido pedido : lista_pedidos){
        if(pedido.getTipoPedido()==Remover){
            novasturmas.remove(pedido.getTurmaInicio());}
        else if(pedido.getTipoPedido()==Adicionar){
            novasturmas.push_back(pedido.getTurmaFinal());}
        else{
            novasturmas.push_back(pedido.getTurmaFinal());
            novasturmas.remove(pedido.getTurmaInicio());}
    }
    std::list<std::pair<Slot, std::shared_ptr<Turma>>> novohorario;
    for(std::shared_ptr<Turma> turma : novasturmas){
        for(Slot aula : turma->getaulas()){
            if(aula.getTipoPedido_aula()!=Teorica)
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

ConjuntoPedidos::ConjuntoPedidos(std::list<Pedido> lista){
    lista_pedidos = lista;
}

bool ConjuntoPedidos::operator==(const ConjuntoPedidos& p2) const{
    if(p2.lista_pedidos.size() != lista_pedidos.size()) return false;
    auto it1 = lista_pedidos.begin();
    auto it2 = p2.lista_pedidos.begin();
    while(it1 != lista_pedidos.end()){
        if(!(it1->getStudentNumber() == it2->getStudentNumber() && it1->getTipoPedido() == it2->getTipoPedido()
            && it1->getTurmaInicio() == it2->getTurmaInicio() && it1->getTurmaFinal() == it2->getTurmaFinal()))
            return false;
        it1++;
        it2++;
    }
    return true;

}


ConjuntoPedidos::ConjuntoPedidos(){

}

bool Pedido::operator==(const Pedido& p2){
    if(tipo != p2.tipo) return false;
    switch (tipo) {
        case Adicionar:
            if(turma_final == p2.turma_final) return true;
            return false;
        case Remover:
            if(turma_inicio == p2.turma_inicio) return true;
            return false;
        case Mudar:
            if(turma_inicio == p2.turma_inicio && turma_final == p2.turma_final) return true;
            return false;
    }
    return false;
}