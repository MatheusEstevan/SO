#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int num_ref = 12;
CRITICAL_SECTION cs;

//aux functions


void Sync1()
{
 
   HANDLE l_hsProtect=CreateSemaphore(NULL,1,1,NULL);
  //InterlockedIncrement((LPLONG)&num_ref);
  //InterlockedDecrement(&num_ref);
	  WaitForSingleObject(l_hsProtect,INFINITE);
	  num_ref--;
	  ReleaseSemaphore(l_hsProtect,1,NULL);
 
}

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
		Sync1();
		printf("%d\n", num_ref);
	}
}

DWORD WINAPI convidadoThread(int stopT,int id) {
  // Do stuff.  This will be the first function called on the new thread.
  // When this function returns, the thread goes away.  See MSDN for more details.
  //while(stopT == 1){
  
	    if(num_ref > 0){
		 
		  buscarRef(id);
		  comer(id); 
		}
		else{
			chamarCozinheiro(); 
		}
	//}

  
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
	
	
HANDLE thread;
HANDLE thread2 ;
 HANDLE convidados[12];
		int i = 0;
		for(i; i < 12; i++){
		
		 convidados[i] = _beginthread(convidadoThread(1,i), 0, NULL);
		 
		 
		}
	      WaitForMultipleObjects(2, convidados, TRUE, INFINITE);
	
	      //for (int ii = 0; ii <=1; ii++)
	      CloseHandle (convidados[0]);
	      CloseHandle (convidados[1]);
	
	
	      DeleteCriticalSection(&cs);
}

