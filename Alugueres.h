/**
 * @file Algueres.h
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#define DATALENGTH 10
#define HORALENGTH 5
#define LOCALIZACAOLENGTH 5

typedef struct aluguer
{
    int nif;
    int idveiculo;
    char data[DATALENGTH];
    char hora[HORALENGTH];
    char localizacao[LOCALIZACAOLENGTH];
    struct aluguer *seguinte;
} Aluguer;

// Inserção de um novo registo
Aluguer *inserirAluguer(Aluguer *lista, int nifcliente, int idveiculo, char data[], char hora[], char localizacao[]);
 // Função para ler alugueres de um arquivo e armazená-los em uma lista ligada
Aluguer *lerAlugueres();
 // Função para listar na consola o conteúdo da lista ligada de alugueres
void listarAlugueres(Aluguer *lista);
// Função para verificar se existe um aluguer com o NIF do cliente na lista ligada
bool existeAluguer(Aluguer *lista, int idveiculo);
// Remover um Aluguer a partir do seu id
Aluguer *removerAluguer(Aluguer *lista, int idveiculo);
//funçao para guardar alugueres atribuindo o valor de true or false
bool guardarAluguer(Aluguer* lista);
