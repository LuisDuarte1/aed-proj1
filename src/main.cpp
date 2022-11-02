#include <iostream>
#include "gestaoHorarios.h"
#include "menu.h"
int main(){
    GestaoHorarios::lerFicheiros();
    menu menu;
    menu.iniciar();
}