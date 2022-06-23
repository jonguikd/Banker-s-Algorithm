#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[ ]) {

    int j, i = 0;
    int consumidores[10];
    char comandoAtual[100];    
    int linhaAtual[30];
    int recursos;
    char c, linha = '\n';
    int numberCustomers = 1;
    int numberResources = 3; 
    int available[numberResources];
    int allocation[numberCustomers][numberResources];
    int nedd[numberCustomers][numberResources]; 
    

    FILE *arq;

    arq = fopen("customer.txt", "rt");
    if (arq == NULL) 
    {
        printf("Problemas na abertura do arquivo customer.txt\n");
    }
    
    //pegando o número de clientes 
    while(fread (&c, sizeof(char), 1, arq)) 
    {
        if(c == linha) 
        {
            numberCustomers++;
        }
    }

    fclose(arq);
    // fechando e abrindo o arquivo pro ponteiro de leitura resetar 
    arq = fopen("customer.txt", "rt");
    if (arq == NULL) 
    {
        printf("Problemas na abertura do arquivo customer.txt\n");
    }
    
    //colocando os recursos que tão no arquivo dentro da matriz maximum
    char virgula;
    int maximum[numberCustomers][numberResources];
  
    for (int i = 0; i < numberCustomers; i++)
    {
        for (int j = 0; j < numberResources; j++)
        {
            fscanf(arq, "%d%c", &maximum[i][j],  &virgula);
        }
        
    }
    
    FILE *com;

    com = fopen("commands.txt", "rt");
    if (com == NULL)
    {
        printf("Problemas na abertura do arquivo commands.txt");
    }


  return 0;
}