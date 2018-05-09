/******************************************************************************
* arquivo: FIFO_SIMULA.c <data criação>
* autor:   Matheus Estevan de Campos Silva
* curso: BSI
*******************************************************************************/



/* Estrutura para armazenar os frames de memória */
typedef struct defMemoria
{
	struct defMemoria *prox;
	int valor;
} memoriaFifo;

/* Exemplo de uma forma de ler o arquivo */
char diretório [100] = "C:\\Aulas PUC\\Workspace\\Simula_FIFO\\arquivo1txt";
void lerArq()
{
	int numLido;
	char info[10];
	FILE *arquivo;
	if ((arquivo = fopen(diretorio, "r")) == NULL)
	{
		printf("Erro ao abrir arquivo!!!\n\n");
		exit(1);
		return;
	}
	while (!feof(arquivo))
	{
		fgets(info, 9, arquivo);
		if (!feof(arquivo))
		{
			numLido = atoi(info); // Transforma de char para int
			paginas += 1; // qtde paginas lidas
			// mostra o conteúdo da memoria
			 printf("\n Numero lido: %d", numLido);
		}
	}fclose(arquivo);
	return;
}

void main(){
	
	//vetor de defMemoria
	memoriaFifo quatroFramesMemoria[4];
	//Ler arquivo 
	
	//gerenciamento de memoria do vetor
	
	//print relatorio
	
	
	
}
