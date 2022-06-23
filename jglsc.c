#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    int j, i = 0;
    int cliente;
    char c, linha = '\n';
    int numberCustomers = 0; 
    int numberResources = 0; 
    
    numberResources = argc - 1;

    FILE *arq;

    arq = fopen("customer.txt", "rt");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo customer.txt\n");
    }

    while (fread(&c, sizeof(char), 1, arq))
    {
        if (c == linha)
        {
            numberCustomers++;
        }
    }

    fclose(arq);

    arq = fopen("customer.txt", "rt");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo customer.txt\n");
    }

    int allocation[numberCustomers][numberResources];
    for (int i = 0; i < numberCustomers; i++)
    {
        for (int j = 0; j < numberResources; j++)
        {
            allocation[i][j] = 0;
        }
    }

    char caracter;
    int maximum[numberCustomers][numberResources];

    for (int i = 0; i < numberCustomers; i++)
    {
        for (int j = 0; j < numberResources; j++)
        {
            fscanf(arq, "%d%c", &maximum[i][j], &caracter);
        }
    }

    fclose(arq);

    FILE *result;

    result = fopen("result.txt", "w");
    if (result == NULL)
    {
        fprintf(result, "Problemas na abertura do arquivo result.txt\n");
    }



    int available[numberResources];
    int end;
    
    for (int i = 0; i < argc - 1; i++)
    {
        end = atoi(argv[i + 1]);
        available[i] = end;
    }

    int need[numberCustomers][numberResources];

    for (int i = 0; i < numberCustomers; i++)
    {
        for (int j = 0; j < numberResources; j++)
        {
            need[i][j] = maximum[i][j];
        }
    }

    FILE *com;

    com = fopen("commands.txt", "rt");
    if (com == NULL)
    {
        fprintf(result, "Problemas na abertura do arquivo commands.txt");
    }

    char str[2];
    int num;
    int request[numberResources];
    
    for (int i = 0; i < numberResources; i++)
    {
        request[i] = 0;
    }
    
    int release[numberResources];

    for (int i = 0; i < numberResources; i++)
    {
        release[i] = 0;
    }
    

    int finish[numberCustomers];

    while (fscanf(com, "%s ", str) != EOF)
    {

        if (str[0] == 'R' && str[1] == 'Q')
        {
            int flag = 0;
            int work[numberResources];
            for (int i = 0; i < numberResources; i++)
            {
                work[i] = available[i];
            }

            int finish[numberCustomers];
            for (int i = 0; i < numberCustomers; i++)
            {
                finish[i] = 0;
            }

            fscanf(com, "%d", &num);
            cliente = num;
            for (int i = 0; i < numberResources; i++)
            {
                fscanf(com, "%d", &num);
                request[i] = num;
            }

            for (int i = 0; i < numberResources; i++)
            {
                if (request[i] > need[cliente][i])
                {
                    flag = 1;
                }    
            }
            
            if (flag == 1)
                {
                    fprintf(result, "The customer %d request ", cliente); 
                    for (int i = 0; i < numberResources; i++)
                    {
                        fprintf(result, "%d ", request[i]);
                    }
                    fprintf(result, " was denied because exceed its maximum allocation");
                    fprintf(result, "\n");
                
                }

            if (flag == 0)
            {
                for (int i = 0; i < numberResources; i++)
                {
                    if (request[i] > available[i])
                    {
                        flag = 1;
                    }
                }

                if (flag == 1)
                {
                    fprintf(result, "The resources ");
                    for (int i = 0; i < numberResources; i++)
                    {
                        fprintf(result, "%d ", available[i]);
                    }
                    fprintf(result, "are not enough to customer %d request ", cliente);
                    for (int i = 0; i < numberResources; i++)
                    {
                        fprintf(result, "%d ", request[i]);
                    }
                    fprintf(result, "\n");
                }
                
                if (flag == 0)
                {
                    for (int i = 0; i < numberResources; i++)
                    {
                        available[i] = available[i] - request[i];
                    }

                    for (int i = 0; i < numberResources; i++)
                    {
                        allocation[cliente][i] = allocation[cliente][i] + request[i];
                    }

                    for (int i = 0; i < numberResources; i++)
                    {
                        need[cliente][i] = need[cliente][i] - request[i];
                    }
                }
            }
            if (flag == 0)
            {
                for (int i = 0; i < numberCustomers; i++)
                {
                    if (finish[i] == 0)
                    {
                        for (int j = 0; j < numberResources; j++)
                        {
                            if (need[cliente][j] <= work[j])
                            {
                                work[j] = work[j] + allocation[cliente][j];
                                finish[i] = 1;
                            }
                            else
                            {
                                finish[i] = 0;
                            }
                        }
                    }
                }
                flag = 2;
                for (int i = 0; i < numberCustomers; i++)
                {
                    if (finish[i] == 0)
                    {
                        flag = 1;
                    }
                }

                if (flag == 1)
                {
                    fprintf(result, "The customer %d request ", cliente); 
                    for (int i = 0; i < numberResources; i++)
                    {
                        fprintf(result, "%d ", request[i]);
                    }
                    fprintf(result, " was denied because result in an unsafe state");
                    fprintf(result, "\n");
                
                    for (int i = 0; i < numberResources; i++)
                    {
                        available[i] = available[i] + request[i];
                    }

                    for (int i = 0; i < numberResources; i++)
                    {
                        allocation[cliente][i] = allocation[cliente][i] - request[i];
                    }

                    for (int i = 0; i < numberResources; i++)
                    {
                        need[cliente][i] = need[cliente][i] + request[i];
                    }
                }
            }
            if (flag == 2)
            {
                fprintf(result, "Allocate to customer %d the resources ", cliente); 
                for (int i = 0; i < numberResources; i++)
                {
                    fprintf(result, "%d ", request[i]);
                }
                fprintf(result, "\n");
            }
            
        }

        if (str[0] == 'R' && str[1] == 'L')
        {
            fscanf(com, "%d", &num);
            cliente = num;
            for (int i = 0; i < numberResources; i++)
            {
                fscanf(com, "%d", &num);
                release[i] = num;
            }

            for (int i = 0; i < numberResources; i++)
            {
                available[i] = available[i] + release[i];
            }

            for (int i = 0; i < numberResources; i++)
            {
                allocation[cliente][i] = allocation[cliente][i] - release[i];
            }

            for (int i = 0; i < numberResources; i++)
            {
                need[cliente][i] = need[cliente][i] + release[i];
            }

            fprintf(result, "Release from customer %d the resources ", cliente);
            for (int i = 0; i < numberResources; i++)
            {
                fprintf(result, "%d ", release[i]);
            }
            fprintf(result, "\n");
        }

        if (str[0] == '*')
        {
            fprintf(result, "MAXIMUM | ALLOCATION | NEED\n");

            for (int i = 0; i < numberCustomers; i++)
            {
                for (int j = 0; j < numberResources; j++)
                {
                    fprintf(result, "%d ", maximum[i][j]);
                }
                fprintf(result, " ");
                fprintf(result, " | ");
                for (int j = 0; j < numberResources; j++)
                {
                    fprintf(result, "%d ", allocation[i][j]);
                }
                fprintf(result, "    ");
                fprintf(result, " | ");
                for (int j = 0; j < numberResources; j++)
                {
                    fprintf(result, "%d ", need[i][j]);
                }
                fprintf(result, "\n");
            }

            fprintf(result, "AVAILABLE ");
            for (int i = 0; i < numberResources; i++)
            {
                fprintf(result, "%d ", available[i]);
            }
            fprintf(result, "\n");
        }
    }

return 0;
}