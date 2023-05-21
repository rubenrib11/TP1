/**
 * @file Clientes.c
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Clientes.h"

 // Insere um cliente no registo
Cliente *inserirCliente(Cliente *lista, int nifcliente, char nomecliente[], char moradacliente[], float saldocliente)
 {
    // Verifica se já existe um cliente com o mesmo NIF
    if (!existeCliente(lista, nifcliente))
    {
        // Aloca memória para um novo cliente
        Cliente *novo_cliente = malloc(sizeof(Cliente));
        // Verifica se a alocação de memória foi bem-sucedida
        if (novo_cliente != NULL)
        {
            // Inicializa os campos do novo cliente
            novo_cliente->nif = nifcliente;
            strcpy(novo_cliente->nome, nomecliente);
            strcpy(novo_cliente->morada, moradacliente);
            novo_cliente->saldo = saldocliente;
            // Insere o novo cliente no início da lista
            novo_cliente->seguinte = lista;
            // Retorna a nova lista com o cliente inserido
            return novo_cliente;
        }
    }
    // Se o cliente já existe, retorna a lista original
    return lista;
}

// Função para ler clientes de um arquivo e armazená-los em uma lista ligada
Cliente *lerClientes()
{
    // Declaração de variáveis para armazenar os dados do cliente lidos do arquivo
    FILE *fp;
    int nifcliente;
    float saldocliente;
    char nomecliente[NOMELENGTH];
    char moradacliente[MORADALENGTH];

    // Inicializa um ponteiro auxiliar para a lista de clientes
    Cliente *aux = NULL;

    // Abre o arquivo de clientes para leitura
    fp = fopen("Clientes.bin", "rb");

    // Verifica se o arquivo foi aberto corretamente
    if (fp != NULL) {
        // Lê o arquivo até o final
        while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &nifcliente, nomecliente, moradacliente, &saldocliente) == 4) {
            // Insere o cliente na lista, usando a função inserirCliente
            aux = inserirCliente(aux, nifcliente, nomecliente, moradacliente, saldocliente);
        }

        // Fecha o arquivo
        fclose(fp);
    } else {
        fp = fopen("Clientes.txt", "r");

        // Verifica se o arquivo foi aberto corretamente
        if (fp != NULL) {
            // Lê o arquivo até o final
            while (fscanf(fp, "%d;%[^;];%[^;];%f\n", &nifcliente, nomecliente, moradacliente, &saldocliente) == 4) {
                // Insere o cliente na lista
                aux = inserirCliente(aux, nifcliente, nomecliente, moradacliente, saldocliente);
            }
            
            // Fecha o arquivo
            fclose(fp);
        }
    }
    
    // Retorna a lista de clientes
    return aux;
}
// Listar na consola o conteúdo da lista ligada
void listarClientes(Cliente *lista)
{
    // Inicia um loop que percorre a lista ligada até encontrar um elemento nulo (fim da lista)
    while (lista != NULL)
    {
        // Imprime os dados do cliente atual na consola, usando o formato especificado
        printf("%d %s %s %.2f\n", lista->nif, lista->nome, lista->morada, lista->saldo);

        // Atualiza o ponteiro para o próximo cliente na lista
        lista = lista->seguinte;
    }
}

// Determinar existência do 'nif' na lista ligada 'lista'
bool existeCliente(Cliente *lista, int nif)
{
    // Inicia um loop que percorre a lista ligada até encontrar um elemento nulo (fim da lista)
    while (lista != NULL)
    {
        // Verifica se o NIF do cliente atual é igual ao NIF procurado
        if (lista->nif == nif)
            // Se o NIF for encontrado, retorna true
            return (true);

        // Atualiza o ponteiro para o próximo cliente na lista
        lista = lista->seguinte;
    }

    // Se o NIF não foi encontrado na lista, retorna false
    return (false);
}

// Remover um Cliente a partir do seu código
Cliente *removerCliente(Cliente *lista, int nif)
{
     // Inicializa três ponteiros do tipo Cliente:
     // 'anterior' aponta para o cliente anterior na lista ligada
     // 'atual' aponta para o cliente atual na lista ligada
     // 'aux' é um ponteiro auxiliar usado durante o processo de remoção
    Cliente *anterior = lista, *atual = lista, *aux;

    // Verifica se a lista está vazia
    if (atual == NULL)
        // Retorna NULL se a lista estiver vazia
        return (NULL);
    // Verifica se o primeiro cliente da lista possui o NIF desejado
    else if (atual->nif == nif)
    {
        // Armazena o ponteiro para o próximo cliente
        aux = atual->seguinte;
        // Libera a memória do cliente atual
        free(atual);
        // Retorna o ponteiro para o próximo cliente (novo início da lista)
        return (aux);
    }
    else
    {
        // Percorre a lista até encontrar o cliente com o ID desejado ou chegar ao fim da lista
        while ((atual != NULL) && (atual->nif != nif))
        {
            anterior = atual;
            atual = atual->seguinte;
        }

        // Verifica se o cliente não foi encontrado (atual é NULL)
        if (atual == NULL)
            // Retorna o ponteiro para o início da lista sem alterações
            return (lista);
        else
        {
            // Atualiza o ponteiro 'seguinte' do cliente anterior, "pulando" o cliente atual
            anterior->seguinte = atual->seguinte;
            // Libera a memória do cliente atual
            free(atual);
            // Retorna o ponteiro para o início da lista, que não foi alterado
            return (lista);
        }
    }
}

// Edita o saldo de um cliente com base no seu 'nif'
bool editarSaldo(Cliente *lista, int nif, float novosaldo)
{
    // Inicia um loop que percorre a lista ligada até encontrar um elemento nulo (fim da lista)
    while (lista != NULL)
    {
        // Verifica se o 'nif' do cliente atual corresponde ao 'nif' fornecido
        if(lista->nif == nif)
        {
            // Atualiza o saldo do cliente encontrado com o novo valor fornecido
            lista->saldo = novosaldo;
            // Retorna 'true', indicando que o saldo foi atualizado com sucesso
            return(true);
        }
        // Atualiza o ponteiro para o próximo cliente na lista
        lista = lista->seguinte;
    }
    // Retorna 'false', indicando que o cliente com o 'nif' fornecido não foi encontrado na lista
    return(false);
}

bool guardarClientes(Cliente* lista) 
{

    // Define o caminho completo do arquivo a ser criado
    char caminho_bin[100];
    char caminho_txt[100];
    snprintf(caminho_bin, sizeof(caminho_bin), "Caminho/para/Clientes.bin");
    snprintf(caminho_txt, sizeof(caminho_txt), "Caminho/para/Clientes.txt");

    // Abre o arquivo para escrita em modo binario
    FILE* fp = fopen(caminho_bin, "wb");
    if (!fp) {
        // Se não foi possível abrir o arquivo "Clientes.bin", tenta abrir o arquivo "Clientes.txt"
        fp = fopen(caminho_txt, "w");
        if (!fp) {
            // Se não foi possível abrir nenhum dos arquivos, retorna false
            return false;
        }
    }

    // Percorre a lista de clientes e escreve cada um no arquivo
    const Cliente* clienteAtual = lista;
    while (clienteAtual != NULL) {
        fprintf(fp, "%d,%s,%s,%.2f\n", clienteAtual->nif, clienteAtual->nome, clienteAtual->morada, clienteAtual->saldo);
        clienteAtual = clienteAtual->seguinte;
    }

    // Fecha o arquivo
    fclose(fp);
    if (ferror(fp)) {
        // Verifica se ocorreu um erro ao fechar o arquivo
        return false;
    }

    // Retorna verdadeiro se tudo foi executado com sucesso
    return true;
}




