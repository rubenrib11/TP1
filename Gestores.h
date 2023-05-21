
 /**
 * @file Gestores.h
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>
#include <stdio.h>

typedef struct gestores {
    int id;
    char nome[50];
    char email[50];
    int nif;
    struct gestores *seguinte;
} Gestores;


// Inserção de um novo registo
Gestores *inserirGestores(Gestores *lista, int id, char nome[], char email[], int nif);
//funaço para ler gestores na lista
Gestores *lerGestores();
// listar na consola o conteúdo da lista ligada
void listarGestores(Gestores* lista);
// Verifica se já existe um gestor com o número de ID fornecido
bool existeGestores(Gestores *lista, int id);
// Remover um gestor a partir do seu código
Gestores *removerGestores(Gestores *lista, int id);
//funçao para guardar gestores atribuindo o valor de true or false
bool guardarGestores(Gestores* lista);


