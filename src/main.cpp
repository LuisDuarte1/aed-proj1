#include <iostream>
#include "gestaoHorarios.h"
#include "menu.h"
int main(){
    GestaoHorarios gestao;
    gestao.lerFicheiros();
    auto it = gestao.estudantes.begin();
    while(it != gestao.estudantes.end()){
        std::cout << (*it).getStudentNumber() <<" "<< (*it).getTurmas().size() << "\n";
        it++;
    }
    menu menu;
    menu.iniciar();
}