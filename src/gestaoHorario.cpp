#include "gestaoHorarios.h"
#include "estudante.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>

std::set<Estudante> GestaoHorarios::estudantes;
std::list<std::shared_ptr<Turma>> GestaoHorarios::turmas;
std::list<ConjuntoPedidos> GestaoHorarios::pedidos_pendentes;
std::queue<ConjuntoPedidos> GestaoHorarios::pedidos_recusados;

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
    throw "skill issue";
}



std::string& trim_string(std::string& str) {
    #ifndef _WIN32
        /*
            O windows usa \r\n para sinalizar o fim de uma linha, Enquanto que o linux só usa \n.
            Ou seja ao ler ficheiros com o formato do windows no linux vamos ter um caracter a mais
            e vai induzir em erros na comparação de turmas.
        */
        if(str.find_first_of('\r') != std::string::npos)
            str = str.substr(0, str.size()-1);
    #endif
    return str;
}


void GestaoHorarios::lerFicheiros(){
    //o windows usa \\ para os diretórios enquanto o unix usa /
    #ifndef _WIN32
        std::ifstream ucs = std::ifstream("../recursos/classes_per_uc.csv");
        std::ifstream estudantes_turma = std::ifstream("../recursos/students_classes.csv");
        std::ifstream turma_horario = std::ifstream("../recursos/classes.csv");
    #else
        std::ifstream ucs = std::ifstream("..\\recursos\\classes_per_uc.csv");
        std::ifstream estudantes_turma = std::ifstream("..\\recursos\\students_classes.csv");
        std::ifstream turma_horario = std::ifstream("..\\recursos\\classes.csv");
    #endif

    //primeiro processamos as ucs
    std::string uc_linha;
    //queremos ignorar a primeira linha porque dá nos a ordem dos atributos e não é nos relevante porque 
    //é constante neste caso
    std::getline(ucs,uc_linha);
    
    while(std::getline(ucs,uc_linha).good()){
        std::istringstream uc_linha_stream(uc_linha);
        std::shared_ptr<Turma> t = std::make_shared<Turma>();
        
        std::getline(uc_linha_stream, (*t).uc_code, ',');
        std::getline(uc_linha_stream,(*t).class_code, ',');
        trim_string((*t).class_code);
        (*t).estudantes = 0;


        GestaoHorarios::turmas.push_back(t);
    }


    //agora processamos os horarios de turma
    //queremos ignorar a primeira linha porque dá nos a ordem dos atributos e não é nos relevante porque 
    //é constante neste caso
    std::getline(turma_horario,uc_linha);
    
    while(std::getline(turma_horario,uc_linha).good()){

        std::istringstream uc_linha_stream(uc_linha);
        Turma t;
        std::getline(uc_linha_stream,t.class_code, ',');
        std::getline(uc_linha_stream, t.uc_code, ',');

        std::shared_ptr<Turma> t_found;
        bool found = false;
        for(auto it = GestaoHorarios::turmas.begin(); it != GestaoHorarios::turmas.end(); it++){
            if(*(*it) == t) {
                t_found = *it;
                found = true;
                break;
            }
        }
        if(!found){
            std::cout << "Nao foi encontrada a turma: " << t.uc_code << ":" << t.class_code << "\n"; 
            exit(1);
        }

        t.estudantes = 0;
        Slot s;
        std::string cache_string;
        std::getline(uc_linha_stream, s.dia, ',');
        std::getline(uc_linha_stream, cache_string, ',');
        s.hora_inicio = std::atof(cache_string.c_str());

        std::getline(uc_linha_stream, cache_string, ',');
        float duracao = std::atof(cache_string.c_str());
        s.hora_final = s.hora_inicio + duracao;

        std::getline(uc_linha_stream, cache_string, ',');
        #ifndef _WIN32
            if(cache_string == "TP\r" || cache_string == "TP"){
                s.tipo_aula = Teorico_Pratica;
            }else if(cache_string == "T\r" || cache_string == "T"){
                s.tipo_aula = Teorica;
            } else if(cache_string == "PL\r" || cache_string == "PL"){
                s.tipo_aula = Pratica_Laboratorial;
            } else{
                std::cout << "Nao foi reconhecido o tipo de aula: " << cache_string <<"\n";
                exit(1);
            }
        #else
            if(cache_string == "TP"){
                s.tipo_aula = Teorico_Pratica;
            }else if(cache_string == "T"){
                s.tipo_aula = Teorica;
            } else if(cache_string == "PL"){
                s.tipo_aula = Pratica_Laboratorial;
            } else{
                std::cout << "Nao foi reconhecido o tipo de aula: " << cache_string <<"\n";
                exit(1);
            }
        #endif
        

        (*t_found).aulas.push_back(s);
    }
    

    //agora lemos os estudantes
    //no ficheiro dos estudantes cada cadeira do estudante está em ordem mas,
    //para assegurar consistencia caso isso não acontecer com outro data-set, vamos usar um
    //algoritmo de inserção um bocadinho mais complexo

    //ignoramos a primeira linha claro
    std::getline(estudantes_turma, uc_linha);

    while(std::getline(estudantes_turma, uc_linha).good()){
        std::istringstream estudantes_linha(uc_linha);
        
        std::string cache;

        std::getline(estudantes_linha, cache, ',');
        int codigo_estudante = std::atoi(cache.c_str());
        std::getline(estudantes_linha, cache, ',');
        
        
        Estudante temp(codigo_estudante, cache);

        Estudante& e = temp;

        auto e_it = GestaoHorarios::estudantes.find(temp);
        if(e_it != GestaoHorarios::estudantes.end()){
                e = *e_it;
        } else{
            auto insert_it = GestaoHorarios::estudantes.insert(temp);
            e = *insert_it.first;
        }
        Turma t_cmp;
        std::getline(estudantes_linha, t_cmp.uc_code, ',');
        std::getline(estudantes_linha, t_cmp.class_code, ',');
        trim_string(t_cmp.class_code);

        //ver se a turma é válida
        bool valida = false;
        auto t_it = GestaoHorarios::turmas.begin();
        for(;t_it != GestaoHorarios::turmas.end(); t_it++){
            if(*(*t_it) == t_cmp){
                valida = true;
                break;
            }
        }
        if(valida){
            adicionarEstudanteTurma(GestaoHorarios::estudantes, e, *t_it);
        } else {
            std::cout << "Turma do estudante nao e valida... Ignorando esta entry.\n";
            //TODO (luisd): usar ostream overloads para dar melhor print ao erro
            continue;
        }
    }
}

void GestaoHorarios::guardarFicheiros(){
    #ifndef _WIN32
        std::ofstream ucs = std::ofstream("../recursos/classes_per_uc.csv");
        std::ofstream estudantes_turma = std::ofstream("../recursos/students_classes.csv");
        std::ofstream turma_horario = std::ofstream("../recursos/classes.csv");
        std::ofstream pedidos_rejeitados = std::ofstream("../recursos/pedidos_rejeitados.csv");

    #else
        std::ofstream ucs = std::ofstream("..\\recursos\\classes_per_uc.csv");
        std::ofstream estudantes_turma = std::ofstream("..\\recursos\\students_classes.csv");
        std::ofstream pedidos_rejeitados = std::ofstream("..\\recursos\\pedidos_rejeitados.csv");
        std::ofstream turma_horario = std::ofstream("..\\recursos\\classes.csv");
    #endif

    //first we save the ucs, again
    ucs << "UcCode,ClassCode" << std::endl;
    for(auto i : GestaoHorarios::turmas){
        ucs << i->uc_code << "," << i->class_code << std::endl;
    }

    //then we go on to estudantes_turma
    estudantes_turma << "StudentCode,StudentName,UcCode,ClassCode" << std::endl;
    for(auto i : GestaoHorarios::estudantes){
        for(auto turma : i.getTurmas()){
            estudantes_turma << i.getStudentNumber() << "," << i.getStudentName() 
                << "," << turma->uc_code << "," << turma ->class_code << std::endl;
        }
    }

    //then we go on to turmas again to save the schedules
    turma_horario << "ClassCode,UcCode,Weekday,StartHour,Duration,Type" << std::endl;
    for(auto i : GestaoHorarios::turmas){
        for(Slot s : i->getaulas()){
            turma_horario << i->class_code << "," << i->uc_code << "," << s.dia << "," << s.hora_inicio 
                << "," << (s.hora_final - s.hora_inicio) << "," << (convertTipoAula(s.tipo_aula)) << std::endl;

        }
    }

    pedidos_rejeitados << "UPCode,RequestType,UcCodeInital,ClassCodeInitial,UcCodeFinal,ClassCodeFinal" 
        << std::endl;
    
    while(pedidos_recusados.size() != 0){
        auto i = pedidos_recusados.front();
        pedidos_recusados.pop();
        for(auto l : i.lista_pedidos){
            switch(l.getTipoPedido()){
                case Adicionar:
                    pedidos_rejeitados << l.getStudentNumber() << "," << "Adicionar" << ",,," 
                        << l.getTurmaFinal()->uc_code << "," << l.getTurmaFinal()->class_code << std::endl;
                    break;

                case Remover:
                    pedidos_rejeitados << l.getStudentNumber() << "," << "Remover" << ","
                        << l.getTurmaInicio()->uc_code << "," << l.getTurmaInicio()->class_code <<
                        ",," << std::endl;
                    break;

                case Mudar:
                    pedidos_rejeitados << l.getStudentNumber() << "," << "Mudar" << ","
                        << l.getTurmaInicio()->uc_code << "," << l.getTurmaInicio()->class_code << ","
                        << l.getTurmaFinal()->uc_code << "," <<  l.getTurmaFinal()->class_code << std::endl;
                
                    break;
            }
        }
    }
}



void GestaoHorarios::aceitarpedidos(ConjuntoPedidos conjuntopedidos) {
    auto it = GestaoHorarios::estudantes.find(Estudante(conjuntopedidos.lista_pedidos.begin()->getStudentNumber(), ""));
    for(Pedido pedido : conjuntopedidos.lista_pedidos){
        if(pedido.getTipoPedido()==Adicionar) adicionarEstudanteTurma(GestaoHorarios::estudantes, *it, pedido.getTurmaFinal());
        else if(pedido.getTipoPedido()==Remover) removerEstudanteTurma(GestaoHorarios::estudantes, *it, pedido.getTurmaInicio());
        else{
            adicionarEstudanteTurma(GestaoHorarios::estudantes, *it, pedido.getTurmaFinal());
            removerEstudanteTurma(GestaoHorarios::estudantes, *it, pedido.getTurmaInicio());}
    }
}


std::list<Pedido> inverso_pedido(std::list<Pedido> input){
    std::list<Pedido> out;
    for(Pedido i : input){
        switch(i.getTipoPedido()){
            case Adicionar:
                out.push_back(Pedido(i.getStudentNumber(), Remover, i.getTurmaInicio(), i.getTurmaFinal()));
                break;
            case Remover:
                out.push_back(Pedido(i.getStudentNumber(), Adicionar, i.getTurmaInicio(), i.getTurmaFinal()));
                break;
            case Mudar:
                out.push_back(Pedido(i.getStudentNumber(), Mudar, i.getTurmaInicio(), i.getTurmaFinal()));


        }
    }
    return out;
}

void GestaoHorarios::processarPedidos() {

    //primeira run verificar se existem pedidos que tem conflito, já que esses podem ser logo removidos
    for(auto it = pedidos_pendentes.begin(); it != pedidos_pendentes.end(); it++){
       if((*it).conflito()){
            pedidos_recusados.push(*it);
            it = pedidos_pendentes.erase(it);
            it--;
       }
    }
    //agora sim vemos se nos possiveis há desequilibrio
    std::vector<ConjuntoPedidos> pedidos_a_remover;
    std::map<size_t,std::set<size_t>> matches_encontrados_pendentes;
    for(auto it = pedidos_pendentes.begin(); it != pedidos_pendentes.end(); it++){
        auto desq_1 = (*it).desiquilibrio();
        if(desq_1.size() == 0){ // se não há desequilibrio podemos aceitar diretamente
            continue;
        } else{
            std::set<size_t> matches_encontrados;
            std::list<Pedido> desq_1_inv = inverso_pedido(desq_1);
            //encontra possiveis matches com outros pedidos na queue
            for(auto it_2 = it; it != pedidos_pendentes.end(); it_2++){
                if(it_2 == it) continue;
                for(Pedido i: desq_1_inv){
                    if(std::find((*it_2).lista_pedidos.begin(), (*it_2).lista_pedidos.end(), i) !=
                        (*it_2).lista_pedidos.end()){
                            size_t dist = std::distance(pedidos_pendentes.begin(), it_2);
                            matches_encontrados.insert(dist);
                    }
                }                
            }
            //se não foram encontrados matches suficientes, remove-mos este e todos os outros que dependem deste
            if(matches_encontrados.size() != desq_1_inv.size()){
                size_t dist = std::distance(pedidos_pendentes.begin(), it);
                for(auto pog = matches_encontrados_pendentes.begin(); pog != matches_encontrados_pendentes.end(); pog++){
                    auto it_i = pog->second.find(dist);
                    if(it_i != pog->second.end()){
                        pedidos_a_remover.push_back(*std::next(pedidos_pendentes.begin(),pog->first));
                        pog = matches_encontrados_pendentes.erase(pog);
                        pog--;
                        continue;
                    }
                pedidos_a_remover.push_back(*std::next(pedidos_pendentes.begin(),dist));
                }
            } else{
                //se foram encontrados matches suficientes nos adicionamos à lista dos matches_encontrados_pendentes
                size_t dist = std::distance(pedidos_pendentes.begin(), it);
                matches_encontrados_pendentes.insert(std::make_pair(dist, matches_encontrados));
            }
        }
    }
    for(ConjuntoPedidos t: pedidos_a_remover){
        pedidos_recusados.push(t);
        pedidos_pendentes.remove(t);
    }
    for(ConjuntoPedidos i : pedidos_pendentes){
        aceitarpedidos(i);
    }
}