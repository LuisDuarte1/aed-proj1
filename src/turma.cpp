#include "turma.h"


bool Turma::operator==(const Turma& outra_turma){
    return this->class_code == outra_turma.class_code && this->uc_code == outra_turma.uc_code;
}

int Turma::getestudantes(){
    return this->estudantes;
}
void Turma::addestudantes(){
    this->estudantes++;
}
void Turma::removeestudantes(){
    this->estudantes--;
}