/**
 * @file Meio.c
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
#include "Meio.h"

Meio *inserirMeios(Meio *lista, int id, char *tipo, int bateria, float autonomia, char *localizacao)
{
    if (!existeMeios(lista, id))
    {
        // Alocar memória para o novo meio
        Meio *novo_meio = malloc(sizeof(struct meio));
        // Verificar se a memória foi alocada corretamente
        if (novo_meio != NULL)
        {
            // Atribuir os valores fornecidos ao novo meio
            novo_meio->id = id;
            strncpy(novo_meio->tipo, tipo, TIPOLENGTH - 1);
            novo_meio->tipo[TIPOLENGTH - 1] = '\0';
            novo_meio->bateria = bateria;
            novo_meio->custo = 0.20; // 0.20 centavos por minuto
            novo_meio->autonomia = autonomia;
            strncpy(novo_meio->localizacao, localizacao, LOCATION - 1);
            novo_meio->localizacao[LOCATION - 1] = '\0';
            // Inserir o novo meio no início da lista
            novo_meio->seguinte = lista;
            // Retornar o novo meio como a nova lista
            return novo_meio;
        }
    }else
    // Se o meio já existe ou houve um erro na alocação de memória, retornar a lista atualizada
    return lista;
}

 // Função para ler meios de um arquivo e armazená-los em uma lista ligada
Meio *lerMeios(){
    
    FILE *fp;
    int id,bateria;
    float  autonomia,custo;
    char tipo[TIPOLENGTH];
    char localizacao[LOCATION];
    
    // Inicializar a lista de meios como vazia
    Meio *aux = NULL;
    
    // Abrir o arquivo para leitura
 fp = fopen("Meios.bin", "rb");
 // Verificar se o arquivo foi aberto corretamente
    if (fp != NULL){

    // Ler o arquivo até o final
        while (!feof(fp))
        {
            // Ler os valores de um meio do arquivo
            fscanf(fp, "%d;%d;%s;%f;%[^;];%[^\n]s\n", &id,tipo, &bateria,&custo, &autonomia, localizacao);
            
            // Inserir o meio na lista
            aux = inserirMeios(id, tipo, bateria, custo, autonomia,localizacao);
        }
        
        // Fechar o arquivo
        fclose(fp);
    }else{
        fp = fopen("Meios.txt", "r");
 // Verificar se o arquivo foi aberto corretamente
    if (fp != NULL){

    // Ler o arquivo até o final
        while (!feof(fp))
        {
            // Ler os valores de um meio do arquivo
            fscanf(fp, "%d;%d;%f;%f;%[^;];%[^\n]s\n", &id, &bateria,custo, &autonomia, tipo, localizacao);
            
            // Inserir o meio na lista
            aux = inserirMeios(aux, id, tipo, bateria, autonomia, localizacao);
        }
        
        // Fechar o arquivo
        fclose(fp);
    }
    
    // Retornar a lista de meios
    return (aux);
 }
}
// Função para listar na consola o conteúdo da lista ligada dos meios
void listarMeios(Meio* lista)
{
    // Iniciar um loop que percorre a lista ligada até o último elemento
    while (lista != NULL)
    {
        // Escreveas informações do meio atual na tela,
        // incluindo id, tipo, bateria, autonomia e localização
        printf("%d %s %.2f %.2f %s\n", lista->id, lista->tipo, (float)lista->bateria, lista->autonomia, lista->localizacao);
        
        // Atualizar o ponteiro 'lista' para apontar para o próximo meio da lista
        lista = lista->seguinte;
    }
    // Fim da função, após percorrer e listar todos os meios da lista ligada

}

// Função para verificar a existência de um meio na lista ligada
bool existeMeios(Meio* lista, int id)
{
    // Iniciar um loop que percorre a lista ligada até o último elemento
    while(lista != NULL)
    {
        // Verificar se o 'id' do meio atual corresponde ao 'id' fornecido
        if (lista->id == id) return true; // Se encontrar, retorna verdadeiro
        
        // Atualizar o ponteiro 'lista' para apontar para o próximo meio da lista
        lista = lista->seguinte;
    }
    // Se o loop terminar sem encontrar o 'id', retorna falso
    return false;
}

// Função para remover um elemento do tipo Meio a partir do seu id
Meio *removerMeios(Meio *lista, int id)
{
    // Ponteiros para percorrer a lista e armazenar os elementos atual, anterior e auxiliar
    Meio *anterior = lista, *atual = lista, *aux;

    // Caso a lista esteja vazia, retorna NULL
    if (atual == NULL)
        return (NULL);

    // Caso o primeiro elemento da lista tenha o id a ser removido
    else if (atual->id == id)
    {
        // Armazena o próximo elemento em aux
        aux = atual->seguinte;
        // Libera a memória do elemento atual
        free(atual);
        // Retorna o ponteiro aux (agora apontando para o novo primeiro elemento)
        return (aux);
    }

    // Caso o elemento a ser removido não seja o primeiro da lista
    else
    {
        // Percorre a lista até encontrar o elemento com o id desejado ou chegar ao final
        while ((atual != NULL) && (atual->id != id))
        {
            anterior = atual;
            atual = atual->seguinte;
        }

        // Se atual == NULL, o id não foi encontrado na lista, retorna a lista inalterada
        if (atual == NULL)
            return (lista);

        // Caso o id tenha sido encontrado na lista
        else
        {
            // Atualiza o ponteiro seguinte do elemento anterior, removendo o elemento atual da lista
            anterior->seguinte = atual->seguinte;
            // Libera a memória do elemento atual
            free(atual);
            // Retorna a lista atualizada
            return (lista);
        }
    }
}

// Listar Meios que estão na localização dada pelo utilizador
void listarVGeo(Meio *lista, char localizacao[LOCATION])
{
	// Percorre a lista enquanto não chegar ao final
	while (lista != NULL)
	{
		// Imprime a mensagem de localização fora do if, para evitar repetições desnecessárias
		printf("Meios na localizacao %s:\n", localizacao);
		
		// Verifica se a localização do meio é igual à localização dada pelo utilizador
		if (strcmp(lista->localizacao, localizacao) == 0)
		{
			// Imprime informações sobre o meio
			printf("%d %s %.2d %.2f\n", lista->id, lista->tipo, lista->bateria, lista->autonomia);
		}
		
		// Move para o próximo meio da lista
		lista = lista->seguinte;
	}
}

//funçao para guardar meios atribuindo o valor de true or false
bool guardarMeios(Meio* lista) {
    // Define o caminho completo do arquivo a ser criado
    char caminho_bin[100];
    char caminho_txt[100];
    //snprintf-formatar e escrever dados em um buffer de caracteres.
    snprintf(caminho_bin, sizeof(caminho_bin), "Caminho/para/Meios.bin");
    snprintf(caminho_txt, sizeof(caminho_txt), "Caminho/para/Meios.txt");

    // Abre o arquivo para escrita em modo binário
    FILE* fp = fopen(caminho_bin, "wb");
    if (fp == NULL) {
        // Se não foi possível abrir o arquivo Meios.bin, tenta abrir o arquivo Meios.txt
        fp = fopen(caminho_txt, "w");
        if (fp == NULL) {
            // Verifica se ocorreu um erro ao abrir o arquivo Meios.txt
            return false;
        }
    }

    // Percorre a lista de meios e escreve cada um no arquivo
    const Meio* meioAtual = lista;
    while (meioAtual != NULL) {
        if (fp == NULL) {
            // Verifica se ocorreu um erro ao abrir o arquivo
            return false;
        }
        //escreve as informaçoes do meio no ficheiro
        fprintf(fp, "%d,%s,%d,%.2f,%.2f,%s\n", meioAtual->id, meioAtual->tipo, meioAtual->bateria, meioAtual->custo, meioAtual->autonomia, meioAtual->localizacao);
        meioAtual = meioAtual->seguinte;
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