#include "estudante.h"


bool Estudante::operator==(const Estudante& outro_estudante){
    return outro_estudante.getStudentNumber() == numero_up;
}

void Estudante::adicionarTurma(const Turma& nova_turma){
    turmas_inscrito.push_back(nova_turma);
}

void Estudante::removerTurma(Turma& turma_remover){
    bool encontrado = false;
    for(auto i = turmas_inscrito.begin(); i != turmas_inscrito.end(); i++){
        if((*i) == turma_remover){
            turmas_inscrito.erase(i);
            encontrado = true;
            break;
        }
    }
    if(!encontrado){
        std::cout << "Nao foi encontrado a turma para remover ao estudante...\n";
        //TODO (luisd): talvez usar uma exceção?
        //TODO (luisd): fazer ostream para dar print à turma para quando dar erro mostrar esta.
    }
}


Estudante::Estudante(int _numero_up, std::string _nome) : numero_up(_numero_up), nome(_nome){

}

bool operator<(const Estudante& a, const Estudante& b){
    return a.numero_up < b.numero_up;
}



