#include "gestaoHorarios.h"

#include <fstream>
#include <sstream>
#include <algorithm>

std::string& trim_string(std::string& str) {
    #ifndef _WIN32
        /*
            O windows usa \r\n para sinalizar o fim de uma linha, Enquanto que o linux só usa \n.
            Ou seja ao ler ficheiros com o formato do windows no linux vamos ter um caracter a mais
            e vai induzir em erros na comparação de turmas.
        */
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
        Turma t;
        std::getline(uc_linha_stream, t.uc_code, ',');
        std::getline(uc_linha_stream,t.class_code, ',');
        trim_string(t.class_code);
        t.estudantes = 0;

        this->turmas.push_back(t);
    }


    //agora processamos os horarios de turma
    //queremos ignorar a primeira linha porque dá nos a ordem dos atributos e não é nos relevante porque 
    //é constante neste caso
    std::getline(turma_horario,uc_linha);
    
    while(std::getline(turma_horario,uc_linha).good()){
        Horario h;

        std::istringstream uc_linha_stream(uc_linha);
        Turma t;
        std::getline(uc_linha_stream,t.class_code, ',');
        std::getline(uc_linha_stream, t.uc_code, ',');

        //TODO: verficar se é áçido
        t.estudantes = 0;
        h.turma = t;
        Slot s;
        std::string cache_string;
        std::getline(uc_linha_stream, s.dia, ',');
        std::getline(uc_linha_stream, cache_string, ',');
        s.hora_inicio = std::atof(cache_string.c_str());

        std::getline(uc_linha_stream, cache_string, ',');
        float duracao = std::atof(cache_string.c_str());
        s.hora_final = s.hora_inicio + duracao;

        std::getline(uc_linha_stream, cache_string, ',');

        if(cache_string == "TP\r"){
            s.tipo_aula = Teorico_Pratica;
        }else if(cache_string == "T\r"){
            s.tipo_aula = Teorica;
        } else if(cache_string == "PL\r"){
            s.tipo_aula = Pratica_Laboratorial;
        } else{
            std::cout << "Nao foi reconhecido o tipo de aula: " << cache_string <<"\n";
            exit(1);
        }
        h.slot = s;
        

        this->horarios.push_back(h);
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

        auto e_it = this->estudantes.find(temp);
        if(e_it != this->estudantes.end()){
                e = *e_it;
        } else{
            auto insert_it = this->estudantes.insert(temp);
            e = *insert_it.first;
        }
        Turma t_cmp;
        std::getline(estudantes_linha, t_cmp.uc_code, ',');
        std::getline(estudantes_linha, t_cmp.class_code, ',');
        trim_string(t_cmp.class_code);

        //ver se a turma é válida
        bool valida = false;
        for(auto t_it = this->turmas.begin(); t_it != this->turmas.end(); t_it++){
            if((*t_it) == t_cmp){
                valida = true;
                break;
            }
        }
        if(!valida){
            std::cout << "Turma do estudante nao e valida... Ignorando esta entry.\n";
            //TODO (luisd): usar ostream overloads para dar melhor print ao erro
            continue;
        }
        e.adicionarTurma(t_cmp);

    }
}