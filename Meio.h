/**
 * @file Meio.h
 * @author ruben 
 * @brief 
 * @version 0.1
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#define TIPOLENGTH 50
#define LOCATION 5

 typedef struct meio
 {
    int id;//unico para cada meio de mobilidade diferente 
    char tipo[TIPOLENGTH]; //tipo de meio
    int bateria; //0 a 100 (porcentagem)
    float custo; //preco por minuto em euros
    float autonomia;// autonomia do Meio
    char localizacao[LOCATION]; //localizacao gerada atraves de geocodigo what3words.com 
    struct meio *seguinte;
} Meio;

// Função para inserir um novo veículo na lista ligada
Meio *inserirMeios(Meio *lista, int id, char *tipo, int bateria, float autonomia, char *localizacao);
// Função para ler veículos de um arquivo e armazená-los em uma lista ligada
Meio *lerMeios();
// Função para listar na consola o conteúdo da lista ligada de veículos
void listarMeios(Meio* lista);
// Verificar a existência de um veiculo
bool existeMeios(Meio* lista, int id);
// Função para remover um elemento do tipo Meio a partir
Meio *removerMeios(Meio *lista, int id);
// Listar Meios que estão na localização dada pelo utilizador
void listarVGeo(Meio *lista, char localizacao[]);
//Funçao para Guardar Meios que sao inseridos
bool guardarMeios(Meio* lista);

//corrigir a funçao existe em todos



