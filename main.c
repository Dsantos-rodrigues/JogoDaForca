    /*Alunos: Davi Santos Rodrigues, André Luiz Ribeiro de Araújo Lima
Curso: Informática  Matéria: Estrutura de Dados  Turma: 302
Data: 17/11/2020*/

#include <stdio.h>
#include <stdlib.h> // para usar a função exit()
#include <string.h>
#include <time.h> // para usar a função rand()
#include <unistd.h> // para usar a função sleep()
#include <ctype.h>
#include "forca.h"

char chave[46];
char dica[30];
char chutes[26];
int chutesdados = 0;

void abertura() // dá as boas vindas ao usuário
{
  printf("/*****************/\n");
  printf("/* Jogo da Forca */\n");
  printf("/*****************/\n\n");
}

void chuta() // recebe o chute do usuario
{
  char chute;

  printf("\nQual a letra? \t");
  scanf(" %c", &chute);

  chute = tolower(chute);

  if(letraexiste(chute))
  {
    printf("\nVocê acertou! A palavra possui a letra %c.\n\n", chute);
  }
  else
  {
    printf("\nVocê errou :(\tA palavra NÃO possui a letra %c\n\n", chute);
  }

  chutes[chutesdados] = chute;
  chutesdados+=1;
}

int jachutou(char letra) // verifica se o usuário já chutou alguma letra da palavra chave
{
  int letra_certa = 0;

  for(int j=0;j<chutesdados;j++)
  {
    if(chutes[j]==letra)
    {
      letra_certa = 1;
      break;
    }
  }
  return letra_certa;
}

void desenhaforca() // revela as letras da palavra chave a medida que o usuário vai acertando
{
  int i;
  int erros = chuteserrados();

	printf("  _______       \n");
	printf(" |/      |     (%s)\n",dica);
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
	printf(" |             Lista de letras chutadas: %s \n", chutes);
	printf("_|___           \n\n");

  for(i=0; i < strlen(chave); i++)
  {
    if(jachutou(chave[i]))
    {
      printf("%c ",chave[i]);
    }
    else
    {
      printf("_ ");
    }
  }
  printf("\n");
}

void escolhepalavra() // escolhe qual será a palavra chave
{
  FILE* f;
  int qtd_palavras, randomico;

  f = fopen("palavras.txt","rt");
  if(f == NULL)
  {
    printf("Banco de dados de palavras não disponível\n\n");
    exit(1);
  }
  fscanf(f, "%d", &qtd_palavras);

  srand(time(0));
  randomico = rand() % qtd_palavras;

  for(int i = 0; i <= randomico; i++)
  {
    fscanf(f, "%s", chave);
  }
  fclose(f);

  f = fopen("dicas.txt","rt");
  if(f == NULL)
  {
    printf("Banco de dados de dicas não disponível");
    exit(1);
  }
  for(int i = 0; i <= randomico + 1; i++)
  {
    fscanf(f,"%s", dica);
  }
  fclose(f);
}

int win() // verifica se usuário já acertou todas as letras
{
  for(int i = 0; i < strlen(chave); i++)
  {
    if(!jachutou(chave[i]))
    {
      return 0;
    }
  }
  return 1;
}

int letraexiste(char letra)
{
  for(int j=0; j<strlen(chave); j++)
  {
    if(letra == chave[j])
    {
      return 1;
    }
  }
  return 0;
}

int chuteserrados() // confere quantas vezes o usuáiro errou
{
  int erros = 0;

  for(int i=0;i<chutesdados;i++)
  {
    if(!letraexiste(chutes[i]))
    {
       erros++;
    }
  }
  return erros;
}

int lose() // confere se o usuário perdeu o jogo de acordo com a quantidade de erros
{
  return chuteserrados() >= 5;
}

void addpalavras() // permite ao usuário adicionar palavras ao banco de dados
{
  char quer;

  printf("\nVoce deseja adicionar uma palavra para nosso jogo? (S/N) \n\n");
  scanf(" %c", &quer);

  quer = toupper(quer);

  if(quer == 'S')
  {
    char novapalavra[46];
    char novadica[30];

    printf("\nDiga a palavra que quer adicionar.\n\n");
    scanf("%s", novapalavra);

    for (int i = 0; i<strlen(novapalavra); i++)
    {
      novapalavra[i] = tolower(novapalavra[i]);
    }

    printf("\nDê uma dica para essa palavra (fruta, animal, objeto...)\n\n");
    scanf("%s", novadica);

    for (int i = 0; i<strlen(novadica); i++)
    {
      novadica[i] = tolower(novadica[i]);
    }

    FILE* f;

    f = fopen("palavras.txt","r+");

    if(f == 0)
    {
      printf("Banco de dados indisponivel. \n\n");
      exit(1);
    }

    int qtd_palavras;
    fscanf(f, "%d", &qtd_palavras);

    qtd_palavras++;
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd_palavras);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);

    f = fopen("dicas.txt","r+");

    if(f == 0)
    {
      printf("Banco de dados indisponivel. \n\n");
      exit(1);
    }

    int qtd_dicas;
    fscanf(f, "%d", &qtd_dicas);

    qtd_dicas++;
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd_dicas);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novadica);

    fclose(f);

  }
  printf("\nObrigado por jogar :)\n");
}

void desenhos()
{
  if(win())
  {
    	printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");
  }
  else
  {
    printf("\nPuxa, você foi enforcado!\n");
		printf("A palavra era **%s**\n\n", chave);

		printf("    _______________         \n");
		printf("   /               \\       \n");
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
  }
}

int main(void)
{
  abertura();
  escolhepalavra();

  do
  {
    desenhaforca();
    chuta();
    sleep(1);
    system("clear");
  }while(!win() && !lose());

  desenhaforca();
  sleep(1);
  system("clear");

  desenhos();
  addpalavras();

  return 0;
}
