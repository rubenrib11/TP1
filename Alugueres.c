/**
 * @file Algueres.c
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Alugueres.h"


// Inserção de um novo registo
Aluguer *inserirAluguer(Aluguer *lista, int nifcliente, int idveiculo, char data[], char hora[], char localizacao[])
{
	if (!existeAluguer(lista, idveiculo))
	{
		Aluguer *novo = malloc(sizeof(struct aluguer));
		if (novo != NULL)
		{
			novo->nif = nifcliente;
			novo->idveiculo = idveiculo;
			strcpy(novo->data, data);
			strcpy(novo->hora, hora);
			strcpy(novo->localizacao, localizacao);
			novo->seguinte = lista;
			return (novo);
		}
	}
	else
		return (lista);
}

Aluguer *lerAlugueres()
{
    FILE *fp;
    int nifcliente;
    int idveiculo;
    char data[DATALENGTH];
    char hora[HORALENGTH];
    char localizacao[LOCALIZACAOLENGTH];
    
    // Inicializa um ponteiro auxiliar para a lista de Alugueres
    Aluguer *aux = NULL;

    // Abre o arquivo de Alugueres binário para leitura
    fp = fopen("Alugueres.bin", "rb");

    // Verificar se o arquivo foi aberto corretamente
    if (fp != NULL)
    {
        // Ler o arquivo até o final
        while (fscanf(fp, "%d;%d;%[^;];%[^;];%s\n", &nifcliente, &idveiculo, data, hora, localizacao) == 5)
        {
            // Insere o aluguer na lista, usando a função inserirAluguer
            aux = inserirAluguer(aux, nifcliente, idveiculo, data, hora, localizacao);
        }

        // Fechar o arquivo
        fclose(fp);
    }
    else
    {
        fp = fopen("Alugueres.txt", "r");

        // Verificar se o arquivo foi aberto corretamente
        if (fp != NULL)
        {
            // Ler o arquivo até o final
            while (fscanf(fp, "%d;%d;%[^;];%[^;];%s\n", &nifcliente, &idveiculo, data, hora, localizacao) == 5)
            {
                // Insere o aluguer na lista, usando a função inserirAluguer
                aux = inserirAluguer(aux, nifcliente, idveiculo, data, hora, localizacao);
            }
            
            // Fechar o arquivo
            fclose(fp);
        }
    }

    // Retornar a lista de Alugueres
    return aux;
}

void listarAlugueres(Aluguer *lista)
{
    // Faz um loop para percorrer a lista até o final
    while (lista != NULL)
    {
        // Imprime os valores dos campos do aluguer atual da lista
        printf("%d %d %s %s %s\n", lista->nif, lista->idveiculo, lista->data, lista->hora, lista->localizacao);

        // Atualiza o ponteiro 'lista' para apontar para o próximo aluguer da lista
        lista = lista->seguinte;
    }
}

// Função para verificar se existe um aluguer com o NIF do cliente na lista ligada
bool existeAluguer(Aluguer *lista, int idveiculo)
{
    while (lista != NULL)
    {
        // Verifica se o id do veiculo é do aluguer atual é igual ao NIF fornecido
        if (lista->idveiculo == idveiculo)
            return true; // Retorna true se encontrar um aluguer com o NIF
        
        // Atualiza o ponteiro 'lista' para apontar para o próximo aluguer da lista
        lista = lista->seguinte;
    }
    // Retorna false se não encontrar um aluguer com o NIF
    return false; 
}
// Remover um Aluguer a partir do seu id
Aluguer *removerAluguer(Aluguer *lista, int idveiculo)
{
	Aluguer *anterior = lista, *atual = lista, *aux;

	if (atual == NULL)
		return (NULL);
	else if (atual->idveiculo == idveiculo) 
	{
		aux = atual->seguinte;
		free(atual);
		return (aux);
	}
	else
	{
		while ((atual != NULL) && (atual->idveiculo != idveiculo))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL)
			return (lista);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return (lista);
		}
	}
}

//funçao para guardar alugueres atribuindo o valor de true or false
bool guardarAluguer(Aluguer* lista)
{
    // Define o caminho completo do arquivo a ser criado
    char caminho_bin[100];
    char caminho_txt[100];
    snprintf(caminho_bin, sizeof(caminho_bin), "Caminho/para/Alugueres.bin");
    snprintf(caminho_txt, sizeof(caminho_txt), "Caminho/para/Alugueres.txt");

    // Abre o arquivo para escrita em modo binário
    FILE* fp = fopen(caminho_bin, "wb");
    if (fp == NULL) {
        // Se não foi possível abrir o arquivo Gestores.bin, tenta abrir o arquivo Gestores.txt
        fp = fopen(caminho_txt, "w");
        if (fp == NULL) {
            // Verifica se ocorreu um erro ao abrir o arquivo Gestores.txt
            return false;
        }
    }

    // Percorre a lista de gestores e escreve cada um no arquivo
    Aluguer* aluguerAtual = lista;
    while ( aluguerAtual!= NULL) {
        if (fp == NULL) {
            // Verifica se ocorreu um erro ao abrir o arquivo
            return false;
        }
        fprintf(fp, "%d,%d,%s,%s,%s\n", aluguerAtual->nif, aluguerAtual->idveiculo, aluguerAtual->data, aluguerAtual->hora, aluguerAtual->localizacao);
        aluguerAtual = aluguerAtual->seguinte;
    }

    // Fecha o arquivo
    fclose(fp);
    if (ferror(fp)) {
        // Verifica se ocorreu um erro ao fechar o arquivo.
        return false;
    }

    // Retorna verdadeiro se tudo foi executado com sucesso
    return true;
}

