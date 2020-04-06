#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    //leer comando desde entrada
    //primero necesitamos un puntero que guarde las lineas
    //de entrada
    char *line = NULL;
    size_t bufsize = 32;
    int position = 0; //variable para recorrer los argumentos
    //segundo un array de punteros donde guarde los
    //argumentos
    char **args = malloc(bufsize * sizeof(char *)); //asignamos memoria par no quedarnos cortos
    char *token;                                    //para guardar un solo argumento
    //tercero un status se usa en wait(&status) para suspender
    //la ejecución del proceso actual hasta que uno de sus hijos finaliza
    pid_t child_pid;
    int status, i = 0;
    line = malloc(bufsize * sizeof(char));
    if (line == NULL)
    {
        perror("No hay espacio para la linea de entrada");
    }

    while (1)
    {
        printf("%s ", "cisfun$");

        getline(&line, &bufsize, stdin);
        //args = dividiendo_args();
        // if (!args)
        // {
        //     fprintf(stderr, "no se pudo guardar argumentos");
        // }
        token = strtok(line, "\n");
        while (token != NULL)
        {
            args[position] = token;
            position++;

            token = strtok(NULL, "\n");
        }
        args[position] = NULL;
        args = args;
        //status = ejecutar_args();
        if (line && strcmp(line, "\n"))
        {
            child_pid = fork();
            if (child_pid == 0)
            {
                //args[0] = line;
                if (execve(args[0], args, NULL) == -1)
                {
                    perror("Error:");
                }
                else
                {
                    wait(&status);
                }
            }else
            {
                break;
            }
            
        }
        //printf("estas son tus entradas: %s %s", args[0], args[1]);
    }
    //dividir los argumentos
    while (args[position] != NULL)
    {
        free(args[i]);
        position++;
    }

    free(line);
    free(args);
    //ejecutar los comandos analizados
    return (0);
}