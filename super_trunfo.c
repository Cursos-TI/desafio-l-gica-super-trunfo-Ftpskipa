#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QTD_CARTAS 2
#define QTD_ATRIBUTOS 2

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
	float somaAtributos;

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
void escolher_atributos();
void comparar_atributos();

Carta cartas[QTD_CARTAS];
int cartasCadastradas;

int main() 
{	
	cartasCadastradas = 0;

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
		sscanf(resposta, "%1d", &opcao);
		
		switch (opcao)
		{
			case 1:
				cadastrar_cartas();
			break;
			
			case 2:
				escolher_atributos();
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
		char confirmacao[2]; // Caractere que irá guardar a opção escolhida pelo usuário na confirmação
		int cartaNumero = i + 1;

		printf("\nInforme a seguir os dados da sua %dª carta para o jogo Super Trunfo.\n", cartaNumero);

		printf("Sigla do estado (ex: XX): ");
		readln(cartas[i].siglaEstado, sizeof cartas[i].siglaEstado);

		printf("Código da carta (ex: %s01): ", cartas[i].siglaEstado);
		readln(cartas[i].codigoCarta, sizeof cartas[i].codigoCarta);

		printf("Nome da cidade: ");
		readln(cartas[i].nomeCidade, sizeof cartas[i].nomeCidade);
	
		do {
			printf("População da cidade %s: ", cartas[i].nomeCidade);
			readln(resposta, sizeof resposta);
		} while (sscanf(resposta, "%lu", &cartas[i].populacao) != 1);

		do {
			printf("Área da cidade %s em km²: ", cartas[i].nomeCidade);
			readln(resposta, sizeof resposta);
		} while (sscanf(resposta, "%f", &cartas[i].area) != 1);

		do {
			printf("PIB da cidade %s em bilhões de reais: ", cartas[i].nomeCidade);
			readln(resposta, sizeof resposta);
		} while (sscanf(resposta, "%f", &cartas[i].pib) != 1);

		do {
			printf("Número de pontos turísticos da cidade %s: ", cartas[i].nomeCidade);
			readln(resposta, sizeof resposta);
		} while (sscanf(resposta, "%d", &cartas[i].pontosTuristicos) != 1);

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
			printf("\nConfirma os dados? (s/n): ");
			readln(resposta, sizeof resposta);
			sscanf(resposta, "%c", confirmacao);	
			
			if (confirmacao[0] != 's' && confirmacao[0] != 'n')
				printf("Opção inválida!\n");

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

void escolher_atributos()
{
	if (cartasCadastradas < QTD_CARTAS)
	{
		printf("%d cartas cadastradas.\n", cartasCadastradas);
		menu_inicial();
		return;
	}

	int atributo[QTD_ATRIBUTOS];
	int qtdAtributos = sizeof(atributo) / sizeof(int);

	char opcoes[][100] = {
		"1 - Nome da Cidade\n",
		"2 - População\n",
		"3 - Área\n",
		"4 - PIB\n",
		"5 - Número de pontos turísticos\n",
		"6 - Densidade demográfica\n"
	};
	int qtdOpcoes = sizeof(opcoes) / sizeof(opcoes[0]);

	char resposta[2];
	int opcao = 0;
	int escolhidos = 0;
	
	do {
		printf("\nSelecione o atributo para comparação:\n");
		
		for (int i = 0; i < qtdOpcoes; i++)
		{
			int igual = 0;
			for (int j = 0; j < (sizeof(atributo)/sizeof(int)); j++)
			{
				if ( (i + 1) == atributo[j] )
					igual = 1;
			}
			if (igual == 0)
				printf("%s", opcoes[i]);
		}
		do {
			printf("Opção: ");
			readln(resposta, sizeof resposta);
			if ( sscanf(resposta, "%1d", &opcao) == 1 && opcao >= 1 && opcao <= qtdOpcoes )
			{
				atributo[escolhidos] = opcao;
				escolhidos++;
			}

			if (opcao < 1 || opcao > qtdOpcoes)
				printf("Opção inválida!\n");

		} while (opcao < 1 || opcao > qtdOpcoes);
	} while (escolhidos < qtdAtributos);

	comparar_atributos(atributo, qtdAtributos);
}

void comparar_atributos(int atributo[], int length)
{
	int somaAtributos[QTD_CARTAS];
	char numerosEmpate[(QTD_CARTAS * 2) + 1];
	numerosEmpate[sizeof(numerosEmpate) - 1] = '\0';
	int empatados = 0;

	int vencedora;
	unsigned long int uimax;
	float fmax;

	for (int i = 0; i < length; i++)
	{
		printf("\n");
		switch (atributo[i])
		{
			case 1:
				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Nome da cidade:\n");
					printf("Carta %d - %s (%s)\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado);
				}
			break;		
			case 2:
				printf("População:\n");
				
				vencedora;
				uimax = cartas[0].populacao;
				numerosEmpate[0] = '1';
				empatados = 0;

				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Carta %d - %s (%s): %lu\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado, cartas[j].populacao);
					if (cartas[j].populacao > uimax)
					{
						vencedora = j;
						uimax = cartas[j].populacao;
						empatados = 0;
					} else if (cartas[j].populacao == uimax)
					{
						if (empatados > 0)
							numerosEmpate[empatados - 1] = ',';
						numerosEmpate[empatados] = (j+1) + '0';
						numerosEmpate[empatados + 1] = '\0';
						empatados += 2;
					}
					cartas[j].somaAtributos += cartas[j].populacao;
				}
					if (empatados == 0)
						printf("Carta %d venceu em população!\n", vencedora + 1);
					else 
						printf("Cartas %s empataram!\n", numerosEmpate);
			break;
			case 3:
				printf("Área:\n");
				
				vencedora;
				fmax = cartas[0].area;
				numerosEmpate[0] = '1';
				empatados = 0;

				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Carta %d - %s (%s): %.2f\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado, cartas[j].area);
					if (cartas[j].area > fmax)
					{
						vencedora = j;
						fmax = cartas[j].area;
						empatados = 0;
					} else if (cartas[j].area == fmax)
					{
						if (empatados > 0)
							numerosEmpate[empatados - 1] = ',';
						numerosEmpate[empatados] = (j+1) + '0';
						numerosEmpate[empatados + 1] = '\0';
						empatados += 2;
					}

					cartas[j].somaAtributos += cartas[j].area;
				}
					if (empatados == 0)
						printf("Carta %d venceu em população!\n", vencedora + 1);
					else 
						printf("Cartas %s empataram!\n", numerosEmpate);
			break;
			case 4:
				printf("PIB:\n");
				
				vencedora;
				fmax = cartas[0].pib;
				numerosEmpate[0] = '1';
				empatados = 0;
				
				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Carta %d - %s (%s): %.2f\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado, cartas[j].pib);
					if (cartas[j].pib > fmax)
					{
						vencedora = j;
						fmax = cartas[j].pib;
						empatados = 0;
					} else if (cartas[j].pib == fmax)
					{
						if (empatados > 0)
							numerosEmpate[empatados - 1] = ',';
						numerosEmpate[empatados] = (j+1) + '0';
						numerosEmpate[empatados + 1] = '\0';
						empatados += 2;
					}

					cartas[j].somaAtributos += cartas[j].pib;
				}
					if (empatados == 0)
						printf("Carta %d venceu em PIB!\n", vencedora + 1);
					else 
						printf("Cartas %s empataram!\n", numerosEmpate);
			break;
			case 5:
				printf("Número de pontos turísticos:\n");
				
				vencedora;
				uimax = cartas[0].pontosTuristicos;
				numerosEmpate[0] = '1';
				empatados = 0;

				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Carta %d - %s (%s): %d\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado, cartas[j].pontosTuristicos);
					if (cartas[j].pontosTuristicos > uimax)
					{
						vencedora = j;
						uimax = cartas[j].pontosTuristicos;
						empatados = 0;
					} else if (cartas[j].pontosTuristicos == uimax)
					{
						if (empatados > 0)
							numerosEmpate[empatados - 1] = ',';
						numerosEmpate[empatados] = (j+1) + '0';
						numerosEmpate[empatados + 1] = '\0';
						empatados += 2;
					}

					cartas[j].somaAtributos += cartas[j].pontosTuristicos;
				}
					if (empatados == 0)
						printf("Carta %d venceu em número de pontos turísticos!\n", vencedora + 1);
					else 
						printf("Cartas %s empataram!\n", numerosEmpate);
			break;
			
			case 6:
				printf("Densidade demográfica:\n");
				
				vencedora;
				fmax = cartas[0].densidadeDemografica;
				numerosEmpate[0] = '1';
				empatados = 0;

				for (int j = 0; j < QTD_CARTAS; j++)
				{
					printf("Carta %d - %s (%s): %.2f\n", j + 1, cartas[j].nomeCidade, cartas[j].siglaEstado, cartas[j].densidadeDemografica);
					if (cartas[j].densidadeDemografica < fmax)
					{
						vencedora = j;
						fmax = cartas[j].densidadeDemografica;
						empatados = 0;
					} else if (cartas[j].densidadeDemografica == fmax)
					{
						if (empatados > 0)
							numerosEmpate[empatados - 1] = ',';
						numerosEmpate[empatados] = (j+1) + '0';
						numerosEmpate[empatados + 1] = '\0';
						empatados += 2;
					}

					cartas[j].somaAtributos += cartas[j].densidadeDemografica;
				}
					if (empatados == 0)
						printf("Carta %d venceu em densidade demográfica!\n", vencedora + 1);
					else 
						printf("Cartas %s empataram!\n", numerosEmpate);
			break;
		}

	}
		fmax = cartas[0].somaAtributos;
		numerosEmpate[0] = '1';
		empatados = 0;

		for (int i = 0; i < QTD_CARTAS; i++)
		{
			if (cartas[i].somaAtributos > fmax)
			{
				fmax = cartas[i].somaAtributos;
				vencedora = i;
				empatados = 0;
			} else if (cartas[i].somaAtributos == fmax)
			{
				if (empatados > 0)
					numerosEmpate[empatados - 1] = ',';
				numerosEmpate[empatados] = (i+1) + '0';
				numerosEmpate[empatados + 1] = '\0';
				empatados += 2;
			}

		}
			if (empatados == 0)
				printf("\nCarta %d venceu a rodada!\n", vencedora + 1);
			else 
				printf("\nCartas %s empataram na rodada!\n", numerosEmpate);
		
	menu_inicial();
}
