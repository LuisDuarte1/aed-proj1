//
// Created by wwwjo on 24/10/2022.
//
#include "menu.h"
void menu::iniciar() {
    int n;
    cout <<"Sistema de horarios para LEIC\n"
                  "Por favor, selecione a opção desejada, introduzindo o numero correspondente ao que pretende:\n\n"
                  "1-Procura por horario de Estudante:\n"
                  "2-Procura por UC/Turma(Horario ou Ocupacao)/Ano:\n"
                  "3-Procura por estudantes com mais de n UCs:\n"
                  "4-Pedido de alteração de turma:\n";
    cin >> n;
    switch(n){
        case 1:
            return menu::estudante();
        case 2:
            return menu::UCandTurmaandAno();
        case 3:
            return menu::estudantesmaisnucs();
        case 4:
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
void menu::UCandTurmaandAno(){
    int n;
    cout<<"Por favor, selecione ao que pretende relativamente a pesquisa(insira o numero pretendido):\n"
          "1-UC\n"
          "2-Turma\n"
          "3-Ano\n";
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
            int code;
            cout << "O codigo de uma turma e composta pelo ano da turma, a sigla do curso e um determinado numero\n"
                    "Exemplo:1LEIC01\n"
                    "Por favor, insira o CODIGO da turma em questão\n"
                    "Nota:Não se esqueca dos 0's a esquerda.\n";
            cin >> nturma;
            cout<<"\nPretende a ocupacao da turma ou o horario:\n"
                  "1-Ocupacao"
                  "2-Horario";
            cin >> code;
            switch(code){
                case 1:{
                    //Incompleto
                }
                case 2:{
                    //Incompleto
                }
                default:{
                    cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
                    return menu::UCandTurmaandAno();
                }
            }
            //Incompleto
        }
        case 3: {
            string nano;
            cout << "Por favor insira o ano em questao:\n";
            cin >> nano;
            //Incompleto
        }
        default: {
            cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
            return menu::UCandTurmaandAno();
        }
    }

}

void menu::estudantesmaisnucs() {
    string nestudante;
    cout << "Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
    cin >> nestudante;
    string up = "up";
    transform(nestudante.begin(), nestudante.end(), nestudante.begin(), ::tolower);
    if (nestudante.substr(0, 2) == up) {
        cout << "Por favor, insira sem o 'up' \n";
        return menu::estudante();
    }
    nestudante = "up" + nestudante;
    int n;
    cout <<"Por favor insira o numero de UCs:\n";
    cin >>n;
    //Incompleto
}

void menu::pedidosalteracao(){
    int n;
    wcout << "Por favor, especifique o tipo de pedido que pretende:\n"
            "1-Remover estudante de turma/UC.\n"
            "2-Adicionar estudante a uma turma/UC.\n"
            "Notas: So é possivel se o horario é compativel e nao provoca desequilíbrio nas turmas dessa UC.\n"
            "Desequilibrio significa que a diferenca do número de estudantes entre duas turmas da mesma UC é >=4.\n"
            "3-Alterar a turma/UC de algum estudante.\n"
            "4-Alterar um conjunto de turmas/UC de um estudante.\n"
            "Nota: Para as opções 3 e 4, ter em atenção a nota da opção 2.\n";
    cin >> n;
    switch(n){
        case 1:{//Remover UC
            string nestudante;
            cout << "Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
            cin >> nestudante;
            string up = "up";
            transform(nestudante.begin(), nestudante.end(), nestudante.begin(), ::tolower);
            if (nestudante.substr(0, 2) == up) {
                cout << "Por favor, insira sem o 'up' \n";
                return menu::pedidosalteracao();
            }
            nestudante = "up" + nestudante;
            string turma;
            wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                     "Exemplo: 1LEIC01\n"
                     "Por favor insira o codigo correspondente a turma pretendida (a qual se pretende remover):\n";
            cin>>turma;
            string UC;
            wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                     "Exemplo:L.EIC01\n"
                     "Por favor insira o codigo da UC pretendida:\n";
            cin>>UC;
            //Incompleto
        }
        case 2:{
            string nestudante;
            cout << "Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
            cin >> nestudante;
            string up = "up";
            transform(nestudante.begin(), nestudante.end(), nestudante.begin(), ::tolower);
            if (nestudante.substr(0, 2) == up) {
                cout << "Por favor, insira sem o 'up' \n";
                return menu::pedidosalteracao();
            }
            nestudante = "up" + nestudante;
            string turma;
            wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                     "Exemplo: 1LEIC01\n"
                     "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
            cin>>turma;
            string UC;
            wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                     "Exemplo:L.EIC01\n"
                     "Por favor insira o codigo da UC.\n";
            cin>>UC;
            //Incompleto
        }
        case 3:{
            string nestudante;
            cout << "Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
            cin >> nestudante;
            string up = "up";
            transform(nestudante.begin(), nestudante.end(), nestudante.begin(), ::tolower);
            if (nestudante.substr(0, 2) == up) {
                cout << "Por favor, insira sem o 'up' \n";
                return menu::pedidosalteracao();
            }
            nestudante = "up" + nestudante;
            string turma;
            wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                     "Exemplo: 1LEIC01\n"
                     "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
            cin>>turma;
            string UC;
            wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                     "Exemplo:L.EIC01\n"
                     "Por favor insira o codigo da UC.\n";
            cin>>UC;
            //Incompleto
        }
        case 4:{
            int numero;
            cout << "Quantas alteracoes pretende efetuar?\n";
            cin >> numero;
            for(int i = 0;i<n;i++){
                string nestudante;
                cout << "Por favor insira o numero mecanografico do estudante: (Nota: sem o 'up')\n";
                cin >> nestudante;
                string up = "up";
                transform(nestudante.begin(), nestudante.end(), nestudante.begin(), ::tolower);
                if (nestudante.substr(0, 2) == up) {
                    cout << "Por favor, insira sem o 'up' \n";
                    return menu::pedidosalteracao();
                }
                nestudante = "up" + nestudante;
                string turma;
                wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                         "Exemplo: 1LEIC01\n"
                         "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
                cin>>turma;
                string UC;
                wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                         "Exemplo:L.EIC01\n"
                         "Por favor insira o codigo da UC.\n";
                cin>>UC;
                //Incompleto
            }
            //Incompleto
        }

    }
}
bool compareinicio(Slot a1,Slot a2){
    return(a1.hora_inicio < a2.hora_inicio);
}
void menu::printhorario(list<Slot> horarios) {
    cout << "    Horas    |    Segunda    |    Terca    |    Quarta    |    Quinta    |    Sexta    |";
    float inicial = 8.00;
    float final = 8.5;
    horarios.sort(compareinicio);





}

