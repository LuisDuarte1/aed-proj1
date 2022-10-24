//
// Created by wwwjo on 24/10/2022.
//

#include "menu.h"
void menu::iniciar() {
    int n;
    std::cout <<"Sistema de horarios para LEIC\n
                  "Por favor, selecione a opção desejada, introduzindo o numero correspondente ao que pretende:\n\n"
                  "1-Procura por Estudante:\n"
                  "2-Procura por UC e/ou turma:\n"
                  "3-Procura por estudantes com mais de n UCs:\n"
                  "4-Procura por estudantes inscritos em uma determinada UC:\n"
                  "5-Pedido de alteração de turma:\n";
    std::cin >> n;
    switch(n){
        case 1:
            return menu::estudante();
        case 2:
            return menu::UCandTurma();
        case 3:
            return menu::estudantesmaisnucs();
        case 4:
            return menu::estudantesemumauc();
        case 5:
            return menu::pedidosalteracao();
        default:
            std::cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido";
            return menu::iniciar();
    }
}
