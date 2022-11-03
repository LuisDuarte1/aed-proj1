#include <iostream>
#include <memory>
#include <algorithm>
#include "gestaoHorarios.h"
#include "menu.h"
#include "turma.h"
#include "pedidos.h"


int main(){
    GestaoHorarios::lerFicheiros();
    menu menu;
    menu.iniciar();
}


