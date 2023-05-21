/**
 * @file Clientes.h
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
#define MORADALENGTH 100
#define NOMELENGTH 50

typedef struct cliente
{
    int id;
    int nif;
    char nome[NOMELENGTH];
    char morada[MORADALENGTH];
    float saldo;
    struct cliente *seguinte;
} Cliente;


// Insere um cliente no registo
Cliente *inserirCliente(Cliente *lista, int nifcliente, char nomecliente[], char moradacliente[], float saldocliente);
// Função para ler clientes de um arquivo e armazená-los em uma lista ligada
Cliente *lerClientes();
// Listar na consola o conteúdo da lista ligada
void listarClientes(Cliente *lista);
// Determinar existência do 'nif' na lista ligada 'inicio'
bool existeCliente(Cliente *lista, int nif);
// Remover um Cliente a partir do seu código
Cliente *removerCliente(Cliente *lista, int nif);
// Edita o saldo de um cliente com base no seu 'nif'
bool editarSaldo(Cliente *lista, int nif, float novosaldo);
// Estrutura Cliente e declarações aqui (não fornecidas na pergunta)
bool guardarClientes(Cliente* lista);


//alterar morada 