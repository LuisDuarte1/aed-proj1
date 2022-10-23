#ifndef SLOT_H
#define SLOT_H

#include <iostream>

/**
 * @enum Tipo descreve os tipos de aulas existentes na feup: Teoricas(opcionais), Teórico-prática e prática laboratorial
 * 
 */
enum Tipo{
    Teorica,
    Teorico_Pratica,
    Pratica_Laboratorial
};


/**
 * @brief Guarda as informações relativas a uma aula 
 * 
 */
struct Slot{
    std::string dia;
    float hora_inicio;
    float hora_final;
    Tipo tipo_aula;
};


#endif