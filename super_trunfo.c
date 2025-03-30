#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QTD_CARTAS 2

// Estrutura com todos os elementos necessários para cadastar uma carta do Super Trunfo
typedef struct
{
	char siglaEstado[3];
	char codigoCarta[5];
	char nomeCidade[51];
	unsigned long int populacao;
	float area;
	float pib;
	int pontosTuristicos;
	float densidadeDemografica;
	float pibPerCapita;

} Carta;

void readln(char* s, int size) // Lê o input, remove o \n da string e descarta o restante do input
{
	int ch;
	int i = 0;
	while (1)
	{
		ch = getchar();
		if (ch == '\n' || ch == EOF)
			break;
		else if (i < size - 1)
		{
			s[i] = ch;
			i++;
		}
	}
	s[i] = '\0';
}

void menu_inicial();
void cadastrar_cartas();
void escolher_atributo();

Carta cartas[QTD_CARTAS];
int cartasCadastradas;

int main() 
{	
	printf("\nBem vindo ao jogo Super Trunfo!\n");
	menu_inicial();
	return 0;
}

void menu_inicial()
{
	char resposta[2];
	
	int opcao = 0;
	do {
		printf("\nSelecione uma opção:\n");
		printf("1 - Cadastrar cartas.\n2 - Comparar atributos.\n3 - Sair.\n");
		printf("Opção: ");
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%d", &opcao);
		
		switch (opcao)
		{
			case 1:
				cadastrar_cartas();
			break;
			
			case 2:
				escolher_atributo();
			break;
			
			case 3:
				printf("Volte logo!\n");
				exit(0);
			break;

			default:
				printf("Opção inválida!\n");
		}
	}while (opcao < 1 || opcao > 3);

}

void cadastrar_cartas()
{
	char resposta[51];
	
	cartasCadastradas = 0;

	int i = 0;
	while (i < QTD_CARTAS)
	{
		char confirmacao[2] = "n"; // Caractere que irá guardar a opção escolhida pelo usuário na confirmação
		int cartaNumero = i + 1;

		printf("\nInforme a seguir os dados da sua %dª carta para o jogo Super Trunfo.\n", cartaNumero);

		printf("Sigla do estado (ex: XX): ");
		readln(cartas[i].siglaEstado, sizeof cartas[i].siglaEstado);

		printf("Código da carta (ex: %s01): ", cartas[i].siglaEstado);
		readln(cartas[i].codigoCarta, sizeof cartas[i].codigoCarta);

		printf("Nome da cidade: ");
		readln(cartas[i].nomeCidade, sizeof cartas[i].nomeCidade);

		printf("População da cidade %s: ", cartas[i].nomeCidade);
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%lu", &cartas[i].populacao);

		printf("Área da cidade %s em km²: ", cartas[i].nomeCidade);
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%f", &cartas[i].area);

		printf("PIB da cidade %s em bilhões de reais: ", cartas[i].nomeCidade);
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%f", &cartas[i].pib);

		printf("Número de pontos turísticos da cidade %s: ", cartas[i].nomeCidade);
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%d", &cartas[i].pontosTuristicos);

		printf("\n%dª Carta cadastrada com os seguintes dados:\n", cartaNumero);
		printf("Estado: %s\n", cartas[i].siglaEstado);
		printf("Código: %s\n", cartas[i].codigoCarta);
		printf("Nome da Cidade: %s\n", cartas[i].nomeCidade);
		printf("População: %lu\n", cartas[i].populacao);
		printf("Área: %.2f km²\n", cartas[i].area);
		printf("PIB: %.2f bilhões de reais\n", cartas[i].pib);
		printf("Número de pontos turísticos: %d\n", cartas[i].pontosTuristicos);
	
		//Cálculo da densidade demográfica
		cartas[i].densidadeDemografica = cartas[i].populacao / cartas[i].area;
		printf("Densidade demográfica: %.2f hab/km²\n", cartas[i].densidadeDemografica);	
		
		//Cálculo do pib per capita
		cartas[i].pibPerCapita = (cartas[i].pib * 1000000000) / cartas[i].populacao;
		printf("Pib per capita: %.2f reais\n", cartas[i].pibPerCapita);
		
		 // Loop para verificar se digitou outra opção além de 's' e 'n' na confirmação do registro da carta
		do
		{
			if (confirmacao[0] != 's' && confirmacao[0] != 'n')
				printf("Opção inválida!\n");

			printf("\nConfirma os dados? (s/n): ");
			readln(resposta, sizeof resposta);
			sscanf(resposta, "%c", confirmacao);	
		} while (confirmacao[0] != 's' && confirmacao[0] != 'n');
		i++;
		cartasCadastradas++;

		if (confirmacao[0] == 'n')
		{
			i--;
			cartasCadastradas--;
		}
	}
	printf("Todas as cartas foram cadastradas com sucesso!\n");

	menu_inicial();
}

void escolher_atributo()
{
	if (cartasCadastradas < QTD_CARTAS)
	{
		printf("%d cartas cadastradas.\n", cartasCadastradas);
		menu_inicial();
		return;
	}

	char resposta[2];
	int opcao = 0;

	do {
		printf("\nSelecione o atributo para comparação:\n");
		printf("1 - Nome da cidade\n");
		printf("2 - População\n");
		printf("3 - Área\n");
		printf("4 - PIB\n");
		printf("5 - Número de pontos turísticos\n");
		printf("6 - Densidade demográfica\n");
		printf("7 - Voltar ao menu principal\n");

		printf("Opção: ");
		readln(resposta, sizeof resposta);
		sscanf(resposta, "%d", &opcao);
		
		printf("\n");
		
		switch (opcao)
		{
			case 1:
				printf("Nome da cidade:\n");
				printf("Carta 1 - %s (%s)\n", cartas[0].nomeCidade, cartas[0].siglaEstado);
				printf("Carta 2 - %s (%s)\n", cartas[1].nomeCidade, cartas[1].siglaEstado);
			break;
			
			case 2:
				printf("População:\n");
				printf("Carta 1 - %s (%s): %lu\n", cartas[0].nomeCidade, cartas[0].siglaEstado, cartas[0].populacao);
				printf("Carta 2 - %s (%s): %lu\n", cartas[1].nomeCidade, cartas[1].siglaEstado, cartas[1].populacao);
			
				if ( (cartas[0].populacao - cartas[1].populacao) == 0)
					printf("Empate!\n");
				else if (cartas[0].populacao > cartas[1].populacao)
					printf("Carta 1 venceu!\n");
				else
					printf("Carta 2 venceu!\n");
			break;
			
			case 3:
				printf("Área:\n");
				printf("Carta 1 - %s (%s): %.2f km²\n", cartas[0].nomeCidade, cartas[0].siglaEstado, cartas[0].area);
				printf("Carta 2 - %s (%s): %.2f km²\n", cartas[1].nomeCidade, cartas[1].siglaEstado, cartas[1].area);
			
				if ( (cartas[0].area - cartas[1].area) == 0)
					printf("Empate!\n");
				else if (cartas[0].area > cartas[1].area)
					printf("Carta 1 venceu!\n");
				else
					printf("Carta 2 venceu!\n");
			break;
			
			case 4:
				printf("PIB:\n");
				printf("Carta 1 - %s (%s): %.2f bilhões de reais\n", cartas[0].nomeCidade, cartas[0].siglaEstado, cartas[0].pib);
				printf("Carta 2 - %s (%s): %.2f bilhões de reais\n", cartas[1].nomeCidade, cartas[1].siglaEstado, cartas[1].pib);
			
				if ( (cartas[0].pib - cartas[1].pib) == 0)
					printf("Empate!\n");
				else if (cartas[0].pib > cartas[1].pib)
					printf("Carta 1 venceu!\n");
				else
					printf("Carta 2 venceu!\n");
			break;
			
			case 5:
				printf("Número de pontos turísticos:\n");
				printf("Carta 1 - %s (%s): %d\n", cartas[0].nomeCidade, cartas[0].siglaEstado, cartas[0].pontosTuristicos);
				printf("Carta 2 - %s (%s): %d\n", cartas[1].nomeCidade, cartas[1].siglaEstado, cartas[1].pontosTuristicos);
			
				if ( (cartas[0].pontosTuristicos - cartas[1].pontosTuristicos) == 0)
					printf("Empate!\n");
				else if (cartas[0].pontosTuristicos > cartas[1].pontosTuristicos)
					printf("Carta 1 venceu!\n");
				else
					printf("Carta 2 venceu!\n");
			break;
			
			case 6:
				printf("Densidade demográfica:\n");
				printf("Carta 1 - %s (%s): %.2f hab/km²\n", cartas[0].nomeCidade, cartas[0].siglaEstado, cartas[0].densidadeDemografica);
				printf("Carta 2 - %s (%s): %.2f hab/km²\n", cartas[1].nomeCidade, cartas[1].siglaEstado, cartas[1].densidadeDemografica);
			
				if ( (cartas[0].densidadeDemografica - cartas[1].densidadeDemografica) == 0)
					printf("Empate!\n");
				else if (cartas[0].densidadeDemografica > cartas[1].densidadeDemografica)
					printf("Carta 2 venceu!\n");
				else
					printf("Carta 1 venceu!\n");
			break;
			
			case 7:
				menu_inicial();
			break;

			default:
				printf("Opção inválida!\n");
		}
	} while (opcao < 1 || opcao > 6);

	escolher_atributo();
}
