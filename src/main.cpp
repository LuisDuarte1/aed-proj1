#include <iostream>
#include <memory>
#include <algorithm>
#include "gestaoHorarios.h"
#include "menu.h"
#include "turma.h"
#include "pedidos.h"


int main(){
    GestaoHorarios gestao;
    gestao.lerFicheiros();
    auto it = gestao.estudantes.begin();
    while(it != gestao.estudantes.end()){
        std::cout << (*it).getStudentNumber() <<" "<< (*it).getTurmas().size() << "\n";
        it++;

    }
    teste();
    menu menu;
    menu.iniciar();
}


