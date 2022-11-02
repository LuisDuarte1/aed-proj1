//
// Created by wwwjo on 24/10/2022.
//
#include "menu.h"

using namespace std;

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
            menu::estudante();
            break;
        case 2:
            menu::UCandTurmaandAno();
            break;
        case 3:
            menu::estudantesmaisnucs();
            break;
        case 4:
            menu::pedidosalteracao();
            break;
        default:
            cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
            return menu::iniciar();
    }
    menu::iniciar();
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
          "2-Turma\n\n";
    cin>>n;
    switch(n){
        case 1: {
            string ncurso;
            cout << "\nO codigo de uma UC e composta pela sigla do curso e um determinado numero\n"
                    "Exemplo:L.EIC017\n";
            cin >> ncurso;
            std::vector<std::shared_ptr<Turma>> turmas_curso;
            copy_if(GestaoHorarios::turmas.begin(), 
                GestaoHorarios::turmas.end(), 
                std::back_inserter(turmas_curso),
                [ncurso](std::shared_ptr<Turma> turma){
                    return turma->uc_code == ncurso;
                }
            );

            if(turmas_curso.size() == 0){
                cout << "\n Nao foram encontradas correspondencias com a turma: " << ncurso << "\n"
                    "Tente novamente...";
                return menu::UCandTurmaandAno();
            }

            cout << "\nSelecione as seguintes opções:\n"
                "1 - Nº de estudantes em cada turma\n"
                "2 - Horarios de cada turma\n"
                "3 - Estudantes de cada turma\n\n"
                "Selecione a opção: ";
            
            int opcao = -1;
            cin >> opcao;

            switch (opcao)
            {
            case 1: 
                for(auto i : turmas_curso){
                    std::cout<< i->class_code << " " <<  i->getestudantes() << "\n";
                }
                break;
            case 2:
                for(auto i : turmas_curso){
                    cout <<"\n Horario de " << i->class_code <<":" <<i->uc_code << ":\n";
                    
                    menu::printhorario({i});

                    cout << "\n\n ===================================================== \n\n";
                }
                break;

            case 3:
                for(auto i: turmas_curso){
                    std::cout << "Turma: " << i->class_code << "\n";
                    std::vector<Estudante> turma_estudantes;
                    copy_if(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(),
                        std::back_inserter(turma_estudantes),
                        [&i](Estudante e){
                            auto e_turmas = e.getTurmas();
                            return std::find(e_turmas.begin(), e_turmas.end(), i) != e_turmas.end();
                        }

                    );
                    if(turma_estudantes.size() == 0){
                        std::cout << "ATENÇAO: ESTA TURMA NÃO TEM ESTUDANTES!\n";
                        continue;
                    }
                    for(Estudante estudante : turma_estudantes){
                        std::cout << "\t up" << estudante.getStudentNumber() << " : " << estudante.getStudentName() << "\n";
                    }
                }
                break;

            default:
                break;
            }



            break;
        }
        case 2: {
            string nturma;
            string nuc;
            int code;
            cout << "O codigo de uma turma e composta pelo ano da turma, a sigla do curso e um determinado numero\n"
                    "Exemplo:1LEIC01\n"
                    "Por favor, insira o CODIGO da turma em questão\n"
                    "Nota:Não se esqueca dos 0's a esquerda.\n"
                    "Input: ";
            cin >> nturma;

            cout << "\nO codigo de uma UC e composta pela sigla do curso e um determinado numero\n"
                    "Exemplo:L.EIC017\n";
            cin >> nuc;
            Turma t {nturma, nuc};
            std::shared_ptr<Turma> t_p;
            bool found = false;
            for(auto it = GestaoHorarios::turmas.begin(); it != GestaoHorarios::turmas.end(); it++){
                if(*(*it) == t){
                    t_p = *it;
                    found = true;
                    break;
                }
            }
            if(!found){
                cout << "Nao foi encontrado uma turma correspondente... tente outra vez.\n";
                return menu::UCandTurmaandAno();
            }

            cout<<"\nPretende a ocupacao da turma ou o horario:\n"
                  "1-Ocupacao"
                  "2-Horario";
            cin >> code;
            switch(code){
                case 1:{
                    cout << "\n" << t_p->class_code <<":" <<t_p->uc_code << " :: " << t_p->estudantes << " estudantes...\n";
                    break;
                }
                case 2:{
                    cout <<"\n Horario de " << t_p->class_code <<":" <<t_p->uc_code << ":\n";
                    menu::printhorario({t_p});
                    break;
                }
                default:{
                    cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
                    return menu::UCandTurmaandAno();
                }
            }
            //Incompleto
            break;
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
            break;
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
            break;
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
            break;
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
            break;
        }

    }
}

std::string convertTipoAula(Tipo t){
    switch (t)
    {
    case(Teorica):
        return "T";
    case(Teorico_Pratica):
        return "TP";
    case(Pratica_Laboratorial):
        return "PL";
    }
}

bool compareinicio(pair<Slot,string> a, pair<Slot,string> b){
    return(a.first.hora_inicio < b.first.hora_inicio);
}
void menu::printhorario(list<shared_ptr<Turma>> horarios) {
    vector<pair<Slot, string>> segundas;
    vector<pair<Slot, string>> tercas;
    vector<pair<Slot, string>> quartas;
    vector<pair<Slot, string>> quintas;
    vector<pair<Slot, string>> sextas;
    for(auto it=horarios.begin();it !=horarios.end();++it){
        list<Slot> f = (*it)->getaulas();
        for(auto iter=f.begin();iter !=f.end();++iter){
            if(iter->dia == "Monday"){
                segundas.push_back(make_pair(*iter, (*it)->uc_code));
            }
            else if(iter->dia == "Tuesday"){tercas.push_back(make_pair(*iter, (*it)->uc_code));}
            else if(iter->dia == "Wednesday"){quartas.push_back(make_pair(*iter, (*it)->uc_code));}
            else if(iter->dia == "Thursday"){quintas.push_back(make_pair(*iter, (*it)->uc_code));}
            else if(iter->dia == "Friday"){sextas.push_back(make_pair(*iter, (*it)->uc_code));}
        }
    }
    sort(segundas.begin(),segundas.end(), compareinicio);
    sort(tercas.begin(),tercas.end(), compareinicio);
    sort(quintas.begin(),quintas.end(), compareinicio);
    sort(quartas.begin(),quartas.end(), compareinicio);
    sort(sextas.begin(),sextas.end(), compareinicio);
    
    for(int i = 0;i<segundas.size() && cout << "\nSegunda-feira:\n\n";i++){
        cout << "\t- UC: " << segundas[i].second<<" Tipo de aula: "<< convertTipoAula(segundas[i].first.tipo_aula) <<" Hora de inicio: "<<segundas[i].first.hora_inicio<<" Hora final: "<<segundas[i].first.hora_final<<".\n";
    }
    for(int i = 0;i<tercas.size() && cout << "\nTerca-feira:\n\n";i++){
        cout << "\t- UC: " << tercas[i].second<<" Tipo de aula: "<< convertTipoAula(tercas[i].first.tipo_aula) <<" Hora de inicio: "<<tercas[i].first.hora_inicio<<" Hora final: "<<tercas[i].first.hora_final<<".\n";
    }
    for(int i = 0;i<quartas.size() && cout << "\nQuarta-feira:\n\n";i++){
        cout << "\t- UC: " << quartas[i].second<<" Tipo de aula: "<< convertTipoAula(quartas[i].first.tipo_aula) <<" Hora de inicio: "<<quartas[i].first.hora_inicio<<" Hora final: "<<quartas[i].first.hora_final<<".\n";
    }
    for(int i = 0;i<quintas.size() && cout << "\nQuinta-feira:\n\n";i++){
        cout << "\t- UC: " << quintas[i].second<<" Tipo de aula: "<< convertTipoAula(quintas[i].first.tipo_aula) <<" Hora de inicio: "<<quintas[i].first.hora_inicio<<" Hora final: "<<quintas[i].first.hora_final<<".\n";
    }
    for(int i = 0;i<sextas.size() && cout << "\nSexta-feita:\n\n";i++){
        cout << "\t- UC: " << sextas[i].second<<" Tipo de aula: "<< convertTipoAula(sextas[i].first.tipo_aula) <<" Hora de inicio: "<<sextas[i].first.hora_inicio<<" Hora final: "<<sextas[i].first.hora_final<<".\n";
    }
}

