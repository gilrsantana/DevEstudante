/*
 * Matricula Curso
 * 
 */


#include <stdio.h>

#define TAM_CURSO 14 // Quantidade de cursos ofertados
#define TAM_UNIDADE 8 // Quantidade de unidades da instituição

int busca(int valor, int v[], int qtd);
void preencheArray(int v[], int qtd, int valor);
float calculaValorCurso(int horas, float valor);
int buscaMaior(int v[], int qtd);

int main(void){
	/* 
	 * Vetores referentes aos horários da unidades.
	 * Entenda que são 8 unidades e cada posição do vetor representa uma unidade,
	 * assim sendo, a unidade 1 (posição "0" dos vetores) abre às 8h e fecha às 14h,
	 * a unidade 2 (posição "1" dos vetores) abre às 8h e fecha às 16h,
	 * a unidade 3 (posição "2" dos vetores) abre às 9h e fecha às 20h,
	 * e assim por diante até a oitava unidade das 14h até às 22h.
	 * 
	 * Um macete aqui é que como não existe a unidade "0", para você associar o curso
	 * e a unidade, é preciso fazer uma conta simples diminuindo 1 para se adequar a 
	 * unidade 1 à posição 0 do vetor (1 - 1 = 0),
	 * unidade 2 à posição 1 do vetor (2 - 1 = 1),
	 * unidade 3 à posição 2 do vetor (3 - 1 = 2),
	 * ...
	 * unidade 8 à posição 7 do vetor (8 - 1 = 7).
	 * 
	 * Essa estrutura é encontrada na expressão
	 * posHrUnidade = unidade - 1; no código abaixo.
	 * A partir dela se associa a unidade ao horário de abertura:
	 * abertura = vHoraAbertura[posHrUnidade];
	 * e fechamento:
	 * fechamento = vHoraFechamento[posHrUnidade];
	 * 
	 */
	int vHoraAbertura[TAM_UNIDADE] = {8,8,9,9,10,12,8,14};
	int vHoraFechamento[TAM_UNIDADE]= { 14,16,20,20,20,22,22,22};
	
	/*
	 * Vetores referentes às características dos cursos.
	 * vCod é um vetor chave que faz a declaração dos códigos dos cursos utilizando
	 * números aleatórios não sequenciais. Isto faz com que seja necessário se fazer 
	 * uma busca no vetor para verificar se o número digitado pelo operador corresponde, 
	 * ou não, a um curso válido dentro do vetor.
	 * 
	 * A função: int busca(int valor, int v[], int qtd);
	 * executa essa busca devolvendo a posição dentro do vetor vCod a qual o curso
	 * digitado está ou -1 caso o curso digitado não corresponda a um código válido.
	 * Se o operador digitar código 121 receberá posição = 0;
	 * Se o operador digitar código 123 receberá posição = 1;
	 * Se o operador digitar código 234 receberá posição = 2;
	 * ...
	 * Se o operador digitar código 887 receberá posição = 13
	 * pos = busca(cod, vCod, TAM_CURSO);
	 * 
	 * Essa poição (pos) é fundamental, pois através dela é que obtém os seus equivalentes
	 * nos vetores de valor de hora do curso (vValHora), quantidade de horas do curso
	 * (vQtHoras) e unidade que oferece o curso (vUnid).
	 * Essa estruturação é o que chamamos de vetores paralelos, onde uma entidade qualquer,
	 * onde aqui chamamos de curso, tem seus atributos organizados de forma estruturada
	 * em cada um dos vetores de acordo com a sua posição.
	 * 
	 * O curso 121, posição "0", tem valor de hora "10", horas "20", na unidade "1",
	 * O curso 123, posição "1", tem valor de hora "20", horas "20", na unidade "8",
	 * O curso 234, posição "2", tem valor de hora "30", horas "30", na unidade "2",
	 * ...
	 * O curso 887, posição "13", tem valor de hora "50", horas "100", na unidade "4",
	 */

	int vCod[TAM_CURSO]= { 121,123,234,345,456,567,678,789,332,443,554,665,776,887};
	float vValHora[TAM_CURSO]= { 10,20,30,10,20,30,40,20,30,50,10,10,30,50};
	int vQtHoras[TAM_CURSO]= { 20,20,30,30,40,40,50,50,60,60,80,80,100,100};
	int vUnid[TAM_CURSO]= { 1,8,2,7,3,6,4,5,6,1,8,2,1,4};
	
	/*
	 * Os vetores abaixo servem para acumular a quantidade de inscrições em um determinado
	 * curso (vCursoEscolhido) e a quantidade de alunos em uma unidade (vAlunoMatriculado).
	 * Eles são iniciados com 0 em todas as posições, operação feita pela função:
	 * void preencheArray(int v[], int qtd, int valor);
	 * A partir daí, após cada interação, é acrescentada uma unidade na posição do curso
	 * escolhido e na unidade que oferece o curso.
	 * 
	 * Essa estruturação nos dará no final do programa o relatório com o total de alunos 
	 * inscritos em cada curso e em cada unidade.
	 * vCursoEscolhido[0] representa a quantidade de alunos inscritos no curso 121 (vCod[0]);
	 * vCursoEscolhido[1] representa a quantidade de alunos inscritos no curso 123 (vCod[1]);
	 * vCursoEscolhido[2] representa a quantidade de alunos inscritos no curso 234 (vCod[2]);
	 * ...
	 * vCursoEscolhido[13] representa a quantidade de alunos inscritos no curso 887 (vCod[13]);
	 * 
	 * vAlunoMatriculado[0] representa a quantidade de alunos matriculados na unidade 1;
	 * vAlunoMatriculado[1] representa a quantidade de alunos matriculados na unidade 2;
	 * vAlunoMatriculado[2] representa a quantidade de alunos matriculados na unidade 3;
	 * ...
	 * vAlunoMatriculado[7] representa a quantidade de alunos matriculados na unidade 8;
	 * O mesmo raciocínio para os vetores de abertura e fechamento das unidades
	 */
	
	int vCursoEscolhido[TAM_CURSO];
	int vAlunoMatriculado[TAM_UNIDADE];
	
	/*
	 * Variáveis necessárias para estruturação do programa.
	 */

	int cod, unidade, posHrUnidade, abertura, fechamento, maxCurso, maxUnid;
	
	// Adicionados valor na variável para não obter valores irreais no relatório geral
	int pos = -1;
	
	
	float valorCurso; //valor hora * carga horaria
	
	
	// Fim de declaração das variáveis
	
	
	
	// Início da execução das instruções
	
	preencheArray(vCursoEscolhido, TAM_CURSO, 0); // Preenchendo o vCursoEscolhido com "0"
	preencheArray(vAlunoMatriculado, TAM_UNIDADE, 0);  // Preenchendo vAlunoMatriculado com "0"
	
	
	printf("Informe o código do curso ou 0 para sair: ");
	scanf("%i", &cod);
	while(cod != 0){ // Se o código for diferente de zero executa o bloco de instrução
		
		pos = busca(cod, vCod, TAM_CURSO); //Retorna a posição (0 a 13) ou -1 caso não encontre
		
		if(pos != -1){ // Se a resposta for diferente de -1 executa o bloco de instrução.
			
			vCursoEscolhido[pos]++; // Acrescenta 1 aluno na posição (0 a 13) do vetor
			
			// Calcula o valor do curso (valor da hora  * quantidade de horas)
			valorCurso = calculaValorCurso(vQtHoras[pos], vValHora[pos]); 
			
			unidade = vUnid[pos]; // Encontra a unidade que o curso é oferecido
			
			// Faz a relação da unidade com a posição do vetor que trata das unidade do curso
			posHrUnidade = unidade - 1; 
			
			// unidade = 1 -> 1 - 1 = 0 
			
			abertura = vHoraAbertura[posHrUnidade]; // Hora de abertura da unidade
			fechamento = vHoraFechamento[posHrUnidade]; // Hora de fechamento da unidade
			
			vAlunoMatriculado[posHrUnidade]++; //Acrescenta 1 aluno na posição (0 a 7) do vetor
			
			// Exibe as respostas de acordo com o código do curso escolhido
			printf("Curso escolhido -> %i\n", cod);
			printf("Unidade que oferece o curso -> %i\n", unidade);
			printf("Hora de abertura da unidade - %i horas\n", abertura);
			printf("Hora de fechamento da unidade - %i horas\n", fechamento);
			printf("Valor do curso -> R$ %.2f\n\n", valorCurso);
			
		}else{
			// Mensagem para caso o código do curso digitado não corresponda a um curso válido
			printf("O código digitado não corresponde a um curso válido, tente novamente.\n");
		}
		
		// Solicita nova entrada de dados dentro do loop while
		printf("Informe o novo código do curso ou 0 para sair: ");
		scanf("%i", &cod);
	}
	
	
	
	/*
	 * 	Essa condição é criada pois se o operador não fizer nenhuma interação com o programa
	 * 	colocando "0" já na primeira entrada evita que se tenham falsos positivos no 
	 * relatório geral
	 */
	 
	if(pos != -1){
		
		
		
		//Código do curso com maior número de alunos inscritos
		maxCurso = buscaMaior(vCursoEscolhido, TAM_CURSO);
		
		//Montante total recebido pelas inscrições em cada unidade
		// É preciso acrescentar + 1 pois a função me retorna a posição e não o número da unidade.
		// posição 0 corresponde a unidade 1 (0 + 1)
		maxUnid = buscaMaior(vAlunoMatriculado, TAM_UNIDADE);
		
		
		printf("\n\n******************** RELATÓRIO GERAL *********************\n");
		printf("Curso mais escolhido:........ Código  %3i ..... %3i alunos\n", vCod[maxCurso], vCursoEscolhido[maxCurso]);
		printf("Unidade com mais alunos:..... Unidade %3i ..... %3i alunos\n", maxUnid + 1, vAlunoMatriculado[maxUnid]);
		
		printf("Alunos inscritos por unidade\n");
		for(int i = 1; i <= TAM_UNIDADE; i++){
			printf("Unidade %i .... %i alunos\n", i, vAlunoMatriculado[i - 1]);
		}
	}
	
	
	return 0;
}


// Função que busca os valores válidos dentro do vetor retornando a posição ou -1
int busca(int valor, int v[], int qtd){
	
	for(int i = 0; i < qtd; i++){
		if(valor == v[i]){
			return i;
		}
		
	}
	
	return -1;	
}




// Função que preenche o vetor com um valor especificado
void preencheArray(int v[], int qtd, int valor){
	
	for(int i = 0; i < qtd; i++){
		v[i] = valor;
	}
}




// Função que calcula o valor do curso retornando esse cálculo
float calculaValorCurso(int horas, float valor){

	return horas * valor;
}
/*
 * vCursoEscolhido[TAM_CURSO]
 * pos 0 = 1 matriculados
 * pos 1 = 0 matriculados
 * pos 2 = 3 matriculados
 * pos 3 = 2 matriculados
 * pos 4 = 1 matriculados
 *  .....
 * pos 13 = 4 matriculados
 */




// Função que busca o maior valor dentro de um vetor e retorna a posição deste maior valor
int buscaMaior(int v[], int qtd){
	
	int maior = -1;
	int maiorPos = -1;
	
	for(int i = 0; i < qtd; i++){
		if(maior < v[i]){
			maior = v[i];
			maiorPos = i;
		}
	
	}
	
	return maiorPos;
}
