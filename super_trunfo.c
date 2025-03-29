#include <stdio.h>
#include <string.h>

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
	float densidadePopulacional;
	float pibPerCapita;

} Carta;

void flush_stdin() // Limpar a entrada após um scanf para remover o \n
{
	int c;
	while ( (c = getchar()) != '\n' && c != EOF);
}

void fgets_flush(char* s, int comprimento) // Função fgets com verificação de \n na string e na entrada para evitar pular os próximos fgets
{
	fgets(s, comprimento, stdin);
	
	int posnl = -1;
	for (int i = 0; i < comprimento; i++)
	{
		if (s[i] == '\n')
		{
			posnl = i;
			s[i] = '\0';
			break;
		}
	}
	int c;
	if (posnl == -1)
		while ( (c = getchar()) != '\n' && c != EOF);
}

int main() 
{	
	int quantidadeCartas = 2; // Quantidade de cartas a serem cadastradas

	Carta cartas[quantidadeCartas];
	
	int i = 0;
	while (i < quantidadeCartas)
	{
		char confirmacao = 'n'; // Caractere que irá guardar a opção escolhida pelo usuário na confirmação
		int cartaNumero = i + 1;

		printf("Informe a seguir os dados da sua %dª carta para o jogo Super Trunfo.\n", cartaNumero);

		printf("Sigla do estado (ex: XX): ");
		fgets_flush(cartas[i].siglaEstado, sizeof cartas[i].siglaEstado);

		printf("Código da carta (ex: %s01): ", cartas[i].siglaEstado);
		fgets_flush(cartas[i].codigoCarta, sizeof cartas[i].codigoCarta);

		printf("Nome da cidade: ");
		fgets_flush(cartas[i].nomeCidade, sizeof cartas[i].nomeCidade);

		printf("População da cidade %s: ", cartas[i].nomeCidade);
		scanf("%lu", &cartas[i].populacao);

		printf("Área da cidade %s em km²: ", cartas[i].nomeCidade);
		scanf("%f", &cartas[i].area);

		printf("PIB da cidade %s em bilhões de reais: ", cartas[i].nomeCidade);
		scanf("%f", &cartas[i].pib);

		printf("Número de pontos turísticos da cidade %s: ", cartas[i].nomeCidade);
		scanf("%d", &cartas[i].pontosTuristicos);

		printf("\n%dª Carta cadastrada com os seguintes dados:\n", cartaNumero);
		printf("Estado: %s\n", cartas[i].siglaEstado);
		printf("Código: %s\n", cartas[i].codigoCarta);
		printf("Nome da Cidade: %s\n", cartas[i].nomeCidade);
		printf("População: %lu\n", cartas[i].populacao);
		printf("Área: %.2f km²\n", cartas[i].area);
		printf("PIB: %.2f bilhões de reais\n", cartas[i].pib);
		printf("Número de pontos turísticos: %d\n", cartas[i].pontosTuristicos);
	
		//Cálculo da densidade populacional
		cartas[i].densidadePopulacional = cartas[i].populacao / cartas[i].area;
		printf("Densidade populacional: %.2f hab/km²\n", cartas[i].densidadePopulacional);	
		
		//Cálculo do pib per capita
		cartas[i].pibPerCapita = (cartas[i].pib * 1000000000) / cartas[i].populacao;
		printf("Pib per capita: %.2f reais\n", cartas[i].pibPerCapita);
		
		 // Loop para verificar se digitou outra opção além de 's' e 'n' na confirmação do registro da carta
		do
		{
			if (confirmacao !='s' && confirmacao !='n')
				printf("Opção inválida!\n");

			printf("\nConfirma os dados? (s/n): ");
			scanf(" %c", &confirmacao);
		} while (confirmacao !='s' && confirmacao !='n');

		flush_stdin();

		i++;
		
		if (confirmacao == 'n')
			 i--;
	}
	printf("Todas as cartas foram cadastradas com sucesso!\n");

	// Comparação de um atributo escolhido
	printf("\nComparação de cartas (Atributo: População)\n");
	printf("Carta 1 - %s (%s): %lu\n", cartas[0].nomeCidade,
				cartas[0].siglaEstado, cartas[0].populacao);
	printf("Carta 2 - %s (%s): %lu\n", cartas[1].nomeCidade,
				cartas[1].siglaEstado, cartas[1].populacao);
	
	if (cartas[0].populacao > cartas[1].populacao)
		printf("Resultado: Carta 1 (%s) venceu!\n", cartas[0].nomeCidade);
	else
		printf("Resultado: Carta 2 (%s) venceu!\n", cartas[1].nomeCidade);

	// Comparação de todos os atributos
	printf("\nComparação de cartas (todos os atributos):\n");
	printf("População: Carta %d venceu!\n",
			2 - (cartas[0].populacao > cartas[1].populacao));
	
	printf("Área: Carta %d venceu!\n",
			2 - (cartas[0].area > cartas[1].area));
	
	printf("Pib: Carta %d venceu!\n",
			2 - (cartas[0].pib > cartas[1].pib));
	
	printf("Pontos turísticos: Carta %d venceu!\n",
			2 - (cartas[0].pontosTuristicos > cartas[1].pontosTuristicos));
	
	printf("Densidade populacional: Carta %d venceu!\n",
			2 - (cartas[0].densidadePopulacional < cartas[1].densidadePopulacional));
	
	printf("Pib per capita: Carta %d venceu!\n\n",
			2 - (cartas[0].pibPerCapita > cartas[1].pibPerCapita));
	
	return 0;
}
