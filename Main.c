
/**
 * @file Main.c
 * @author ruben
 * @brief 
 * @version 0.1
 * @date 2023-04-27
 * @copyright Copyright (c) 2023
 */


#include <stdbool.h>
#include <stdio.h>
#include "Meio.h"
#include "Clientes.h"
#include "Gestores.h"
#include "Alugueres.h"


int menu()
{
	int op;
	printf("-----------Meios-----------\n");
	printf("	1-Inserir Meio\n");
	printf("	2-Listar Meios\n");
	printf("	3-Remover Meios\n");
	printf("	4-Guardar meios\n");
	printf("	5-Ler Veiculos\n");
	printf("	6-ListarVGeo \n");
	printf("-----------Clientes-----------\n");
	printf("	7-Inserir Cliente\n");
	printf("	8-Listar Clientes\n");
	printf("	9-Remover Cliente\n");
	printf("	10-Editar Saldo\n");
	printf("	11-Guardar Clientes\n");
	printf("	12-Ler Clientes\n");
	printf("-----------Gestores-----------\n");
	printf("	13-Inserir Gestor\n");
	printf("	14-Listar Gestor\n");
	printf("	15-Remover Gestor\n");
	printf("	16-Guardar Gestores\n");
	printf("	17-Ler Gestores\n");
	printf("-----------Alugueres-----------\n");
	printf("	18-Inserir Aluguer\n");
	printf("	19-Listar Aluguer\n");
	printf("	20-Remover Aluguer\n");
	printf("	21-Guardar Aluguer\n");
	printf("	22-Ler Aluguer\n");
	printf("	0 Sair\n");
	printf("Opcao:\n");
	scanf("%d",&op);
	return(op);
}


int main()
{
    int op;

    Meio *meios = NULL;
    int idmeios, bateria;
    float autonomia;
    char tipo[TIPOLENGTH];
    char localizacao[LOCATION];

    Cliente *clientes = NULL;
    int nifclientes;
    char nome[NOMELENGTH];
    char morada[MORADALENGTH];
    float saldo;

    Gestores *gestores = NULL;
    int idgestores;
    char nomegestores[50];
    char email[50];
    int nifgestores;

    Aluguer *alugueres = NULL;
    int nifalugueres;
    int idveiculo;
    char data[DATALENGTH];
    char hora[HORALENGTH];
    char localizacaoAluguer[LOCALIZACAOLENGTH];

    do
    {
        op = menu();
        switch (op)
        {
            case 1:
                printf("ID?\n");
                scanf("%d", &idmeios);
                scanf("%*c");
                printf("Tipo?\n");
                scanf("%[^\n]s", tipo);
                printf("Nivel da bateria?\n");
                scanf("%d", &bateria);
                printf("Autonomia\n");
                scanf("%f", &autonomia);
                fflush(stdin);
                printf("Localizacao (Ex: D15)\n");
                scanf("%[^\n]s", localizacao);
                meios = inserirMeios(meios, idmeios, tipo, bateria, autonomia, localizacao);
                break;
            case 2:
                listarMeios(meios);
                break;
            case 3:
                printf("Codigo do meio de mobilidade a remover?\n");
                scanf("%d", &idmeios);
                meios = removerMeios(meios, idmeios);
                break;
            case 4:
                if (guardarMeios(meios) == true)
                {
                    printf("TRUE");
                }
                else
                {
                    printf("FALSE");
                }
                break;
            case 5:
                meios = lerMeios();
                break;
            case 6:
                listarVGeo(meios, localizacao);
                break;
            case 7:
                printf("Nif?\n");
                scanf("%d", &nifclientes);
                scanf("%*c");
                printf("Nome\n");
                scanf("%[^\n]s", nome);
                fflush(stdin);
                printf("Morada\n");
                scanf("%[^\n]s", morada);
                printf("Saldo\n");
                scanf("%f", &saldo);
                clientes = inserirCliente(clientes, nifclientes, nome, morada, saldo);
                break;
            case 8:
                listarClientes(clientes);
                break;
            case 9:
                printf("Nif da pessoa a remover?\n");
                scanf("%d", &nifclientes);
                clientes = removerCliente(clientes, nifclientes);
                break;
            case 10:
                printf("Nif?\n");
                scanf("%d", &nifclientes);
                printf("Novo saldo\n");
                scanf("%f", &saldo);
                editarSaldo(clientes, nifclientes, saldo);
                break;
            case 11:
                if (guardarClientes(clientes) == true)
                {
                    printf("true");
                }
                else
                {
                    printf("false");
                }
                break;
            case 12:
                clientes = lerClientes();
                break;
            case 13:
                printf("ID?\n");
                scanf("%d", &idgestores);
                scanf("%*c");
                printf("Nome?\n");
                scanf("%[^\n]s", nomegestores);
                fflush(stdin);
                printf("Email?\n");
                scanf("%[^\n]s", email);
                printf("NIF?\n");
                scanf("%d", &nifgestores);
                gestores = inserirGestores(gestores, idgestores, nomegestores, email, nifgestores);
                break;
            case 14:
                listarGestores(gestores);
                break;
            case 15:
                printf("ID do gestor a remover?\n");
                scanf("%d", &idgestores);
                gestores = removerGestores(gestores, idgestores);
                break;
            case 16:
                if (guardarGestores(gestores) == true)
                {
                    printf("TRUE");
                }
                else
                {
                    printf("FALSE");
                }
                break;
            case 17:
                gestores = lerGestores();
                break;
            case 18:
                printf("NIF?\n");
                scanf("%d", &nifalugueres);
                scanf("%*c");
                printf("ID?\n");
                scanf("%d", &idveiculo);
                fflush(stdin);
                printf("Data?\n");
                scanf("%[^\n]s", data);
                printf("Hora?\n");
                scanf("%[^\n]s", hora);
                printf("Localizacao?\n");
                scanf("%[^\n]s", localizacaoAluguer);
                alugueres = inserirAluguer(alugueres, nifalugueres, idveiculo, data, hora, localizacaoAluguer);
                break;
				case 19:
				 listarAlugueres(alugueres);
				 break;
				case 20:
				     printf("ID do veiculo a remover?\n");
                scanf("%d", &idveiculo);
                alugueres = removerAluguer(alugueres, idveiculo);
				break;
				case 21:
				  if (guardarAluguer(alugueres) == true)
                {
                    printf("true");
                }
                else
                {
                    printf("false");
                }
				break;
				case 22:
				alugueres = lerAlugueres();
				break;
        }
    } while (op != 0);
    
    return 0;
}

//perhuntar ao carlos de ser alugeres = .....