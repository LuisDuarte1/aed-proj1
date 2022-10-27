#include <iostream>
#include "gestaoHorarios.h"
#include "menu.h"
int main(){
    GestaoHorarios gestao;
    gestao.lerFicheiros();
    menu menu;
    menu.iniciar();
}