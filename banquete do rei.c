#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int num_ref = 12;
CRITICAL_SECTION cs;

//aux functions

int randomNumber(int lower, int upper)
{
    int num = (rand() + lower) % (upper + 1);
    return num;   
}


void chamarCozinheiro(){
	printf("Tacho vazio, chamando cozinheiro \n");
	//cozinheiroThread.start();
	
}


void comer(int id){
	
	//uniTempo
	int r = rand();  
	printf("convidado %d esta comendo \n",id);
	sleep(randomNumber(2,5));
}


//convidado
void buscarRef(int id){
	sleep(1);
	if(num_ref == 0){
		printf("convidado %d esta chamando o cozinheiro \n",id);
		chamarCozinheiro();
	}
	else{
		printf("convidado %d esta se servindo \n",id);
	
		EnterCriticalSection(&cs);	
			num_ref--;
		LeaveCriticalSection(&cs);
	}
}

DWORD WINAPI convidadoThread(void* data, int stopT,int id) {
  // Do stuff.  This will be the first function called on the new thread.
  // When this function returns, the thread goes away.  See MSDN for more details.
  while(stopT==1){
	    if(num_ref > 0){
		 
		  buscarRef(id);
		  comer(id); 
		}
		else{
			chamarCozinheiro(); 
		}
	}
  
  return 0;
}
//fim convidado

//cozinheiro

// encher tacho
//preparar comida
void prepararComida(){
	
	sleep(3);
	num_ref = 12;
	
}

//trocar tacho
void trocarTacho(){
	if(num_ref == 0){ 
	sleep(2);
	printf("Comida pronta, pode servir\n"); 
	}
}

void avisarCorte(){
	printf("Comida esta servida \n");
//	notifyAll(); 
}
void voltarCozinha(){
//sleep(ate ser chamado);
}

DWORD WINAPI cozinheiroThread(void* data) {
  // Do stuff.  This will be the first function called on the new thread.
  // When this function returns, the thread goes away.  See MSDN for more details.
	EnterCriticalSection(&cs);	  
	    prepararComida();
		trocarTacho();
		avisarCorte();
	LeaveCriticalSection(&cs);
	voltarCozinha();
    return 0;
}
//fim cozinheiro




//main

void main(){

 HANDLE thread = CreateThread(NULL, 0, convidadoThread(num_ref,1,1), NULL, 0, NULL);
 HANDLE thread2 = CreateThread(NULL, 0, convidadoThread(num_ref,1,2), NULL, 0, NULL);

}



