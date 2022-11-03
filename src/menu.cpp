//
// Created by wwwjo on 24/10/2022.
//
#include "menu.h"

using namespace std;

void menu::iniciar() {
    int n;
    cout <<"\nSistema de horarios para LEIC\n"
                  "Por favor, selecione a opcao desejada, introduzindo o numero correspondente ao que pretende:\n\n"
                  "1-Procura por horario de Estudante:\n"
                  "2-Procura por UC/Turma(Horario ou Ocupacao):\n"
                  "3-Procura por estudantes com mais de n UCs:\n"
                  "4-Pedido de alteração de turma:\n"
                  "5-Guardar, processar os pedidos e sair do programa\n";
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
        case 5:
            menu::saireguardar();
        default:
            cout << "O numero que inseriu nao foi aceite, por favor insira um numero valido\n";
            return menu::iniciar();
    }
    menu::iniciar();
}

void menu::saireguardar(){
    GestaoHorarios::processarPedidos();
    GestaoHorarios::guardarFicheiros();
    exit(0);
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
    int n_up = atoi(nestudante.c_str());

    auto it = GestaoHorarios::estudantes.find(Estudante(n_up, ""));

    if(it == GestaoHorarios::estudantes.end()){
        cout << "Esse estudante nao foi encontrado... tente de novo...\n";
        return menu::estudante();
    }

    menu::printhorario(it->getTurmas());

}
void menu::UCandTurmaandAno(){
    int n;
    cout<<"Por favor, selecione ao que pretende relativamente a pesquisa(insira o numero pretendido):\n"
          "1-UC\n"
          "2-Turma\n";
    cin>>n;
    switch(n){
        case 1: {
            string ncurso;
            cout << "O codigo de uma UC e composta pela sigla do curso e um determinado numero\n"
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
                cout << "Nao foram encontradas correspondencias com a turma: " << ncurso << "\n"
                    "Tente novamente...";
                return menu::UCandTurmaandAno();
            }

            cout << "Selecione as seguintes opcoes:\n"
                "1 - Numero de estudantes em cada turma\n"
                "2 - Horarios de cada turma\n"
                "3 - Estudantes de cada turma\n"
                "4- Vagas disponíveis de cada turma\n"
                "Selecione a opcao:\n ";
            
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
            case 4:
                cout << "\n Vagas disponíveis sem causar desequilibrio: \n";
                int min_alunos = (*std::min_element(turmas_curso.begin(), turmas_curso.end(),
                    [](std::shared_ptr<Turma> a, std::shared_ptr<Turma> b){
                        return a->getestudantes() < b->getestudantes();
                    }))->getestudantes();
                for(auto t : turmas_curso){
                    cout << "\n" << t->class_code << ":" << t->uc_code << " :: " 
                        << (abs(min_alunos - t->getestudantes()) >= 4 ? 0 : abs(min_alunos - t->getestudantes())) 
                        << " vagas \n";
                }
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
                    "Por favor, insira o CODIGO da turma em questao\n"
                    "Nota:Nao se esqueca dos 0's a esquerda.\n"
                    "Input: ";
            cin >> nturma;

            std::list<std::shared_ptr<Turma>> t_p;

            copy_if(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(),
                back_inserter(t_p),
                [nturma](std::shared_ptr<Turma> i){
                    return i->class_code == nturma;
                }
            );

            if(t_p.size() == 0){
                cout << "Nao foi encontrado uma turma correspondente... tente outra vez.\n";
                return menu::UCandTurmaandAno();
            }

            cout<<"Pretende a ocupacao da turma ou o horario:\n"
                  "1-Ocupacao\n"
                  "2-Horario\n"
                  "3-Vagas disponíveis\n";
            cin >> code;
            switch(code){
                case 1:{
                    for(auto t : t_p){
                        cout << "\n" << t->class_code <<":" <<t->uc_code << " :: " << t->estudantes << " estudantes...\n";

                    }
                    break;
                }
                case 2:{
                    cout <<"\n Horario de " << (*t_p.begin())->class_code << "\n\n";
                    menu::printhorario(t_p);

                    break;
                }
                case 3:{
                    cout << "\n Vagas disponíveis sem causar desequilibrio: \n";
                    int min_alunos = (*std::min_element(t_p.begin(), t_p.end(),
                        [](std::shared_ptr<Turma> a, std::shared_ptr<Turma> b){
                            return a->getestudantes() < b->getestudantes();
                        }))->getestudantes();
                    for(auto t : t_p){
                        cout << "\n" << t->class_code << ":" << t->uc_code << " :: " 
                            << (abs(min_alunos - t->getestudantes()) >= 4 ? 0 : abs(min_alunos - t->getestudantes())) 
                            << " vagas \n";
                    }
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

    int n;
    cout <<"Por favor insira o numero de UCs:\n";
    if(!(cin >> n)){
        cout << "Número de UCs inválido... tente novamente....\n\n";
        return menu::estudantesmaisnucs();
    }

    std::vector<Estudante> estudantes_ucs;
    copy_if(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(),
        std::back_inserter(estudantes_ucs),
        [n](Estudante e){
            return e.getTurmas().size() >= n;
        });
    
    if(estudantes_ucs.size() == 0){
        cout << "Nao foi encontrado nenhum estudante com numero igual e maior de que " << n << " UCs...";
        return;
    }

    cout << "Por favor, especifique a ordem que quer dar display aos estudantes\n"
        "1 - Nº UCs por ordem decrescente\n"
        "2 - Ordem alfabetica\n";
    cin >> n;
    Turma t = {"turma", "uc"};
    switch (n)
    {
    case 1:
        std::sort(estudantes_ucs.begin(), estudantes_ucs.end(), [](Estudante a, Estudante b){
            return a.getTurmas().size()>b.getTurmas().size();
        });
        cout << "Listagem de estudantes...\n\n";
        for(Estudante e: estudantes_ucs){
           cout << "up" <<  e.getStudentNumber() << " : " << e.getStudentName() << " : " << e.getTurmas().size() << "\n";
        }
        return;
    case 2:
        std::sort(estudantes_ucs.begin(), estudantes_ucs.end(), [](Estudante a, Estudante b){
            return a.getStudentName()<b.getStudentName();
        });
        cout << "Listagem de estudantes...\n\n";
        for(Estudante e: estudantes_ucs){
           cout << "up" <<  e.getStudentNumber() << " : " << e.getStudentName() << " : " << e.getTurmas().size() << "\n";
        }
        return;
    default:
        cout << "\n Opcao invalida... por favor tente outra vez...\n";
        return menu::estudantesmaisnucs();
    }
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
            int n_up = atoi(nestudante.c_str());
            if(find(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(), Estudante(n_up, ""))
                == GestaoHorarios::estudantes.end()){
                cout << "O número de estudante é inválido, tente outra vez..\n\n";
                return menu::pedidosalteracao();
            }
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

            Turma t = {turma, UC};
            auto turma_to_find = std::make_shared<Turma>(t);
            auto it = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find);
            if(it == GestaoHorarios::turmas.end()){
                cout << "Turma invalida tente outra vez...\n\n";
                return menu::pedidosalteracao();
            }

            ConjuntoPedidos c_p;
            c_p.lista_pedidos.push_back(Pedido(n_up, Remover, *it));
            GestaoHorarios::pedidos_recusados.push_back(c_p);
            
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
            int n_up = atoi(nestudante.c_str());
            if(find(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(), Estudante(n_up, ""))
                == GestaoHorarios::estudantes.end()){
                cout << "O número de estudante é inválido, tente outra vez..\n\n";
                return menu::pedidosalteracao();
            }
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

            Turma t = {turma, UC};
            auto turma_to_find = std::make_shared<Turma>(t);
            auto it = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find);
            if(it == GestaoHorarios::turmas.end()){
                cout << "Turma invalida tente outra vez...\n\n";
                return menu::pedidosalteracao();
            }

            ConjuntoPedidos c_p;
            c_p.lista_pedidos.push_back(Pedido(n_up, Adicionar, *it));
            GestaoHorarios::pedidos_recusados.push_back(c_p);
            
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
            int n_up = atoi(nestudante.c_str());
            auto it_es = find(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(), Estudante(n_up, ""));
            if( it_es == GestaoHorarios::estudantes.end()){
                cout << "O número de estudante é inválido, tente outra vez..\n\n";
                return menu::pedidosalteracao();
            }
            cout << "\n\n Insira a Turma Incial \n\n ";
            string turma_inicial;
            wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                     "Exemplo: 1LEIC01\n"
                     "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
            cin>>turma_inicial;
            string UC_inicial;
            wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                     "Exemplo:L.EIC01\n"
                     "Por favor insira o codigo da UC.\n";
            cin>>UC_inicial;
            //Incompleto
            Turma t_i = {turma_inicial, UC_inicial};
            auto turma_to_find_i = std::make_shared<Turma>(t_i);
            auto it_inicial = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find_i);
            if(it_inicial == GestaoHorarios::turmas.end()){
                cout << "Turma incial invalida tente outra vez...\n\n";
                return menu::pedidosalteracao();
            }

            //===================================

            cout << "\n\n Insira a Turma Final \n\n ";
            string turma_final;
            wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                     "Exemplo: 1LEIC01\n"
                     "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
            cin>>turma_final;
            string UC_final;
            wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                     "Exemplo:L.EIC01\n"
                     "Por favor insira o codigo da UC.\n";
            cin>>UC_final;
            //Incompleto
            Turma t_f = {turma_final, UC_final};
            auto turma_to_find = std::make_shared<Turma>(t_f);
            auto it_final = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find);
            if(it_inicial == GestaoHorarios::turmas.end()){
                cout << "Turma Final invalida tente outra vez...\n\n";
                return menu::pedidosalteracao();
            }

            //sanity check that we are not replacing things that we can't

            if((*it_inicial)->uc_code != (*it_final)->uc_code){
                cout << "As turmas a trocar nao sao da mesma uc... tente novamente.\n\n";
                return menu::pedidosalteracao();
            }

            if((*it_inicial) == (*it_final)){
                cout << "Nao se pode trocar a mesma turma... duh \n\n";
                return menu::pedidosalteracao();
            }

            Pedido p(n_up, Mudar, (*it_inicial), (*it_final));

            ConjuntoPedidos p_pedidos;

            p_pedidos.lista_pedidos.push_back(p);

            GestaoHorarios::pedidos_pendentes.push_back(p_pedidos);
            break;
        }
        case 4:{
            int numero;
            cout << "Quantas alteracoes pretende efetuar?\n";
            cin >> numero;
            ConjuntoPedidos p_pedidos;
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
                int n_up = atoi(nestudante.c_str());
                auto it_es = find(GestaoHorarios::estudantes.begin(), GestaoHorarios::estudantes.end(), Estudante(n_up, ""));
                if( it_es == GestaoHorarios::estudantes.end()){
                    cout << "O número de estudante é inválido, tente outra vez..\n\n";
                    return menu::pedidosalteracao();
                }
                cout << "\n\n Insira a Turma Incial \n\n ";
                string turma_inicial;
                wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                        "Exemplo: 1LEIC01\n"
                        "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
                cin>>turma_inicial;
                string UC_inicial;
                wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                        "Exemplo:L.EIC01\n"
                        "Por favor insira o codigo da UC.\n";
                cin>>UC_inicial;
                //Incompleto
                Turma t_i = {turma_inicial, UC_inicial};
                auto turma_to_find_i = std::make_shared<Turma>(t_i);
                auto it_inicial = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find_i);
                if(it_inicial == GestaoHorarios::turmas.end()){
                    cout << "Turma incial invalida tente outra vez...\n\n";
                    return menu::pedidosalteracao();
                }

                //===================================

                cout << "\n\n Insira a Turma Final \n\n ";
                string turma_final;
                wcout << "O codigo de uma turma é composto pelo ano correspondente, seguido pela sigla do curso correspondente e, de seguida, a respoetiva turma.\n"
                        "Exemplo: 1LEIC01\n"
                        "Por favor insira o codigo correspondnete a turma que pretende ser adicionado:\n";
                cin>>turma_final;
                string UC_final;
                wcout << "O codigo de uma UC é composta pela sigla do curso e um determinado número.\n"
                        "Exemplo:L.EIC01\n"
                        "Por favor insira o codigo da UC.\n";
                cin>>UC_final;
                //Incompleto
                Turma t = {turma_final, UC_final};
                auto turma_to_find = std::make_shared<Turma>(t);
                auto it_final = std::find(GestaoHorarios::turmas.begin(), GestaoHorarios::turmas.end(), turma_to_find);
                if(it_inicial == GestaoHorarios::turmas.end()){
                    cout << "Turma Final invalida tente outra vez...\n\n";
                    return menu::pedidosalteracao();
                }

                //sanity check that we are not replacing things that we can't

                if((*it_inicial)->uc_code != (*it_final)->uc_code){
                    cout << "As turmas a trocar nao sao da mesma uc... tente novamente.\n\n";
                    return menu::pedidosalteracao();
                }

                if((*it_inicial) == (*it_final)){
                    cout << "Nao se pode trocar a mesma turma... duh \n\n";
                    return menu::pedidosalteracao();
                }

                Pedido p(n_up, Mudar, (*it_inicial), (*it_final));

                p_pedidos.lista_pedidos.push_back(p);

            }
            //Incompleto
            break;
        }

    }
}


string ConvertHora(float hour){
    int hora=(int)hour;
    int minute = (int)((hour-hora)*60);
    string minstr = to_string(minute);
    if(minstr == "0"){ minstr += "0";}
    string result = to_string(hora) + ":" + minstr;
    return result;

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
    if(segundas.size()>0){
        cout <<"\nSegunda-feira:\n\n";
    }
    for(int i = 0;i<segundas.size();i++){
        cout << "\t- UC: " << segundas[i].second<<" Tipo de aula: "<< convertTipoAula(segundas[i].first.tipo_aula) <<" Hora de inicio: "<<ConvertHora(segundas[i].first.hora_inicio)<<" Hora final: "<<ConvertHora(segundas[i].first.hora_final)<<".\n";
    }
    if(tercas.size()>0){
        cout <<"\nTerca-feira:\n\n";
    }
    for(int i = 0;i<tercas.size();i++){
        cout << "\t- UC: " << tercas[i].second<<" Tipo de aula: "<< convertTipoAula(tercas[i].first.tipo_aula) <<" Hora de inicio: "<<ConvertHora(tercas[i].first.hora_inicio)<<" Hora final: "<<ConvertHora(tercas[i].first.hora_final)<<".\n";
    }
    if(quartas.size()>0){
        cout <<"\nQuarta-feira:\n\n";
    }
    for(int i = 0;i<quartas.size();i++){
        cout << "\t- UC: " << quartas[i].second<<" Tipo de aula: "<< convertTipoAula(quartas[i].first.tipo_aula) <<" Hora de inicio: "<<ConvertHora(quartas[i].first.hora_inicio)<<" Hora final: "<<ConvertHora(quartas[i].first.hora_final)<<".\n";
    }
    if(quintas.size()>0){
        cout <<"\nQuinta-feira:\n\n";
    }
    for(int i = 0;i<quintas.size();i++){
        cout << "\t- UC: " << quintas[i].second<<" Tipo de aula: "<< convertTipoAula(quintas[i].first.tipo_aula) <<" Hora de inicio: "<<ConvertHora(quintas[i].first.hora_inicio)<<" Hora final: "<<ConvertHora(quintas[i].first.hora_final)<<".\n";
    }
    if(sextas.size()>0){
        cout <<"\nSexta-feira:\n\n";
    }
    for(int i = 0;i<sextas.size();i++){
        cout << "\t- UC: " << sextas[i].second<<" Tipo de aula: "<< convertTipoAula(sextas[i].first.tipo_aula) <<" Hora de inicio: "<<ConvertHora(sextas[i].first.hora_inicio)<<" Hora final: "<<ConvertHora(sextas[i].first.hora_final)<<".\n";
    }
}

