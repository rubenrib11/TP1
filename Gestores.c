
 /**
 * @file Gestores.c
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

 #include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <stdbool.h>
#include "Gestores.h"

// Inserção de um novo registo
Gestores *inserirGestores(Gestores *lista, int id, char nome[], char email[], int nif){
    // Verifica se não existe um gestor com o mesmo ID
    if (!existeGestores(lista, id)) { 
        // Aloca memória para um novo gestor
        Gestores *novo_gestor = malloc(sizeof(struct gestores)); 
        // Verifica se a alocação de memória foi bem-sucedida
        if (novo_gestor != NULL) { 
            novo_gestor->id = id; 
            // Copia o nome para o novo gestor
            strcpy(novo_gestor->nome, nome); 
            // Copia o email para o novo gestor
            strcpy(novo_gestor->email, email); 
            novo_gestor->nif = nif;
            // O novo gestor aponta para o proximo gestor na lista
            novo_gestor->seguinte = lista; 
            // Retorna o ponteiro para o novo gestor, que agora é o início da lista
            return novo_gestor; 
        }
    } else { 
        // Caso já exista um gestor com o mesmo ID
        printf("Já existe um gestor com este número.\n"); 
        // Retorna a lista original sem fazer alterações
        return lista; 
    }
}

//funaço para ler gestores na lista
Gestores *lerGestores(){
    FILE *fp;
    int id, nif;
    char nome[50], email[50];
    
    // Inicializar a lista de gestores como vazia
    Gestores *aux = NULL;
    
    // Abrir o arquivo para leitura
 fp = fopen("Gestores.bin", "rb");
 // Verificar se o arquivo foi aberto corretamente
    if (fp != NULL){

    // Ler o arquivo até o final
        while (!feof(fp))
        {
            // Ler os valores de um gestor do arquivo
            fscanf(fp, "%d;%[^;];%[^;];%d\n", &id, nome, email, &nif);
            
            // Inserir o gestor na lista
            aux = inserirGestores(aux, id, nome, email, nif);
        }
        
        // Fechar o arquivo
        fclose(fp);
    }else{
        fp = fopen("Gestores.txt", "r");
    // Verificar se o arquivo foi aberto corretamente
    if (fp != NULL){
    // Ler o arquivo até o final
        while (!feof(fp))
        {
            // Ler os valores de um gestor do arquivo
            fscanf(fp, "%d;%[^;];%[^;];%d\n", &id, nome, email, &nif);
            
           // Inserir o gestor na lista
            aux = inserirGestores(aux, id, nome, email, nif);
        }
        
        // Fechar o arquivo
        fclose(fp);
    }
    
    // Retornar a lista de gestores
    return (aux);
 }
}

// listar na consola o conteúdo da lista ligada
void listarGestores(Gestores* lista) {
    //percorre a lista ate ao ultimo elemento 
     while (lista != NULL) 
    {
        //escreve as informaçoes do gestor.
        printf("%d %s %s %d\n", lista->id, lista->nome, lista->email, lista->nif);
        //aponta para o proximo gestor
        lista = lista->seguinte;
    }

}

// Verifica se já existe um gestor com o número de ID fornecido
bool existeGestores(Gestores *lista, int id){
    // Ponteiro "atual" aponta para o início da lista
    Gestores *atual = lista; 
    // Percorre a lista ate chegar ao final
    while (atual != NULL) { 
        // Se o ID do gestor atual for igual ao ID fornecido
        if (atual->id == id) { 
             // Retorna true, indicando que o gestor já existe
            return true;
        }
        // Avança para o próximo gestor na lista
        atual = atual->seguinte; 
    }
    // Se não encontrou o gestor com o ID fornecido, retorna false
    return false; 
}

// Remover um gestor a partir do seu código
Gestores *removerGestores(Gestores *lista, int id) {
    Gestores *anterior = lista, *atual = lista;

    // Verifica se o gestor a ser removido é o primeiro da lista
    if (atual == lista) {
        // Atualiza o ponteiro da lista para o próximo gestor
        lista = lista->seguinte; 
        // Libera a memória do gestor removido
        free(atual); 
    } else {
        // Percorre a lista para procurar o gestor com o ID perciso
        while ((atual != NULL) && (atual->id != id)) {
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual != NULL) {
            // Atualiza o ponteiro do gestor anterior para o próximo gestor
            anterior->seguinte = atual->seguinte; 
             // Libera a memória do gestor removido
            free(atual);
        }
    }
}

//funçao para guardar gestores atribuindo o valor de true or false
bool guardarGestores(Gestores* lista){
    // Define o caminho completo do arquivo a ser criado
    char caminho_bin[100];
    char caminho_txt[100];
    snprintf(caminho_bin, sizeof(caminho_bin), "Caminho/para/Gestores.bin");
    snprintf(caminho_txt, sizeof(caminho_txt), "Caminho/para/Gestores.txt");

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
    Gestores* gestorAtual = lista;
    while (gestorAtual != NULL) {
        if (fp == NULL) {
            // Verifica se ocorreu um erro ao abrir o arquivo
            return false;
        }
        fprintf(fp, "%d,%s,%s,%d\n", gestorAtual->id, gestorAtual->nome, gestorAtual->email, gestorAtual->nif);
        gestorAtual = gestorAtual->seguinte;
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
