/*
 * Sistema de gestão de ingressos em cinema
 */
 
#include <stdio.h>

#define SALA_NORMAL 30.00
#define SALA_3D 40.00 

int validaOperacao(void);
float calculaValorIngresso(int tipoSala, int tipoIngresso);
float processaIngressos(int qtdIngresso);
void exibeResultadoFinal(int qtdIngresso, float totalCompra);

int main(void){
	
	int op, numCartao, qtdIngresso, comprasProcessadas = 0, consolidadoIngresso = 0;
	float totalCompra, consolidadoCompra = 0.00;
	
	op = validaOperacao();
	
	while(op){
		printf("Informe o número do cartão de crédito: ");
		scanf("%i", &numCartao);
		
		printf("Informe a quantidade de ingressos: ");
		scanf("%i", &qtdIngresso);
		
		totalCompra = processaIngressos(qtdIngresso);
		
		printf("compra de R$ %.2f realizada no cartão %i\n", totalCompra, numCartao);
		printf("Valor médio pago pelos ingressos nesta compra: %.2f\n\n", totalCompra / qtdIngresso);
		
		consolidadoIngresso += qtdIngresso;
		consolidadoCompra += totalCompra;
		comprasProcessadas++;
		
		op = validaOperacao();
		
	} //Fim op
	
	printf("\n------------------------------------------------------------------------\n");
	printf("O valor total de compras feitas com cartão é R$ %.2f\n", consolidadoCompra);
	printf("O número médio de ingressos por compra é %.1f\n", (float)consolidadoIngresso / comprasProcessadas);
	
	
	return 0;
}


int validaOperacao(void){
	int op;
	
	printf("Digite 1 para registrar compras ou 0 para finalizar o programa: ");
	scanf("%i", &op);
	
	while(op < 0 || op > 1){
		printf("OPERAÇÃO INVÁLIDA!!!\n");
		printf("Digite 1 para registrar compras ou 0 para finalizar o programa: ");
		scanf("%i", &op);
	}
	
	return op;
}



float processaIngressos(int qtdIngresso){
	
	int tipoSala, tipoIngresso;
	float valorIngresso = 0.00;
	
	for(int i = 1; i <= qtdIngresso; i++){
		printf("Informe o tipo de sala do ingresso %i\n1 - Sala Normal\n3 - Sala 3D\n", i);
		scanf("%i", &tipoSala);
		if(tipoSala != 3){
			tipoSala = 1;
		}
		
		printf("Informe o tipo de ingresso %i\n1 - Inteiro\n2 - Estudante(meia)\n", i);
		scanf("%i", &tipoIngresso);
		if(tipoIngresso != 2){
			tipoIngresso = 1;
		}
			
		valorIngresso += calculaValorIngresso(tipoSala, tipoIngresso);
	}
		
	return valorIngresso;
}




float calculaValorIngresso(int tipoSala, int tipoIngresso){
	
	float valor;
	
	if(tipoSala == 3){
		valor = SALA_3D / tipoIngresso;
	}else{
		valor = SALA_NORMAL / tipoIngresso;
	}
	
	return valor;
		
}
