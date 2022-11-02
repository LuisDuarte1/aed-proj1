#include <iostream>
#include "gestaoHorarios.h"
#include "menu.h"
int main(){
    GestaoHorarios::lerFicheiros();
    auto it = GestaoHorarios::estudantes.begin();
    while(it != GestaoHorarios::estudantes.end()){
        std::cout << (*it).getStudentNumber() <<" "<< (*it).getTurmas().size() << "\n";
        it++;

    }
    menu menu;
    menu.iniciar();
}