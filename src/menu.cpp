//
// Created by wwwjo on 24/10/2022.
//
#include "menu.h"
void menu::iniciar() {
    int n;
    cout <<"Sistema de horarios para LEIC\n"
                  "Por favor, selecione a opção desejada, introduzindo o numero correspondente ao que pretende:\n\n"
                  "1-Procura por Estudante:\n"
                  "2-Procura por UC e/ou turma:\n"
                  "3-Procura por estudantes com mais de n UCs:\n"
                  "4-Procura por estudantes inscritos em uma determinada UC:\n"
                  "5-Pedido de alteração de turma:\n";
    cin >> n;
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
            cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
            return menu::iniciar();
    }
}

void menu::estudante(){
    string nestudante;
    cout<<"Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
    cin>>nestudante;
    string up = "up";
    transform(nestudante.begin(),nestudante.end(),nestudante.begin(),::tolower);
    if(nestudante.substr(0,2)==up){
        cout<<"Por favor, insira sem o 'up' \n";
        return menu::estudante();
    }
    nestudante="up"+nestudante;
    //Incompleto
}
void menu::UCandTurma() {
    int n;
    cout<<"Por favor, selecione se pretende o horario de uma determinada UC ou de uma determinada turma (insira o numero pretendido)\n"
          "1-UC\n"
          "2-Turma\n";
    cin>>n;
    switch(n){
        case 1: {
            string ncurso;
            cout << "O codigo de uma UC e composta pela sigla do curso e um determinado numero\n"
                    "Exemplo:LEIC017\n"
                    "Por favor, insira o NUMERO correspondente a UC\n"
                    "Nota:Não se esqueca dos 0's a esquerda.\n";
            cin >> ncurso;
            ncurso = "LEIC" + ncurso;
            //Incompleto

        }
        case 2: {
            string nturma;
            cout << "O codigo de uma UC e composta pelo ano da turma, a sigla do curso e um determinado numero\n"
                    "Exemplo:1LEIC01\n"
                    "Por favor, insira o CODIGO da turma em questão\n"
                    "Nota:Não se esqueca dos 0's a esquerda.\n";
            cin >> nturma;
            //Incompleto
        }
        default: {
            cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
            return menu::UCandTurma();
        }
    }

}

