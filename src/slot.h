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
public:
    /**
     * @brief Dá return ao dia (da semana Ex: "Monday", "Tuesday", etc...) de uma determinada aula.
     * @return std::string dia
     */
    std::string getdia();
    /**
     * @brief Dá return á hora do ínicio de uma determinada aula
     * @return float hora_inicio
     */
    float geth_inicio();
    /**
     * @brief Dá return á hora final de uma determinada aula
     * @return float hora_final
     */
    float geth_final();
    /**
     * @brief Dá return ao "Tipo" de uma determinada aula (Teórico-Prática,Prática Laboratorial,Teórica)
     * @return Tipo tipo_aula
     */
    Tipo gettipo_aula();
};


#endif