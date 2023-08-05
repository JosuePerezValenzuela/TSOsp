#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constant N of array size
#define MEMORY_SIZE 32
#define ENDED_PROCESS_LENGTH 100

struct Proceso
{
  int nro;
  int tam;
};

typedef struct Proceso proceso;

// Global variables
int idxProcesosMuertos = 0;
int numeroProcesoAct = 1;

void lanzarProceso(int tamanio, int memoria[]);
void verMemoria(int memoria[]);
void terminarProceso(int nroProceso, int memoria[], struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH]);
void compactarMemoria(int memoria[]);
void imprimirProcesosMuertos(struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH]);
void imprimirTablaProcesos(int memoria[], struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH]);

// gcc practica.c -o practica -std=c99

int main()
{
  srand(time(NULL));

  // Array de memoria
  int memoria[MEMORY_SIZE];

  // Inicializar memoria
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    memoria[i] = 0;
  }

  // Array de procesos finalizados
  struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH];

  // 1) Lanzar Proceso
  // 2) Terminar Proceso
  // 3) Compactar Memoria
  // 4) Ver Memoria
  // 5) Ver Tabla de Procesos

  while (1)
  {
    // Imprimir menu
    int opcion = 0;
    printf("Ingrese un numero\n");
    printf("1 -> para lanzar un proceso\n");
    printf("2 -> Para terminar un proceso\n");
    printf("3 -> Para compactar memoria\n");
    printf("4 -> Para ver memoria\n");
    printf("5 -> Para ver tabla de procesos\n");
    printf("6 -> Salir\n");
    printf("Opcion (1,2,3,4,5,6): ");
    // Leer opcion
    scanf("%d", &opcion);
    // Segun opcion do something
    switch (opcion)
    {
    case 1:
      // Lanzar proceso
      printf(">>>>>>> Lanzar proceso\n");
      // Genenerar un numero entre 1 y 32
      int tamanio = rand() % 5 + 1;
      printf("Tamanio del proceso: %d\n", tamanio);
      lanzarProceso(tamanio, memoria);
      break;
    case 2:
      // Terminar proceso
      printf(">>>>>>> Terminar proceso\n");
      printf("Ingrese el numero del proceso a matar\n");
      int nroProceso;
      scanf("%d", &nroProceso);
      terminarProceso(nroProceso, memoria, procesosMuertos);

      break;
    case 3:
      // Compactar memoria
      printf(">>>>>>> Compactar memoria\n");
      compactarMemoria(memoria);
      break;
    case 4:
      // Ver memoria
      printf(">>>>>>> Ver memoria\n");
      verMemoria(memoria);
      imprimirProcesosMuertos(procesosMuertos);
      break;
    case 5:
      // Ver tabla de procesos
      printf(">>>>>>> Ver tabla de procesos\n");
      imprimirTablaProcesos(memoria, procesosMuertos);
      break;
    case 6:
      // Salir
      return 0;
    default:
      printf(">>>>>>> Opcion no valida\n");
      continue;
    }
  }

  return 0;
}

// Lanzar Proceso
// tamanio = random(n)
// n = constante
void lanzarProceso(int tamanio, int memoria[])
{
  // Search for free space
  int pos = -1;
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    if (memoria[i] == 0 && i + tamanio <= MEMORY_SIZE)
    {
      int encontrado = 1;
      for (int j = i; j < i + tamanio; j++)
      {
        if (memoria[j] != 0)
        {
          encontrado = 0;
          break;
        }
      }

      if (encontrado)
      {
        pos = i;
        break;
      }
    }
  }
  // Si hay espacio suficiente ponemos proceso
  if (pos != -1)
  {
    for (int i = pos; i < pos + tamanio; i++)
    {
      memoria[i] = numeroProcesoAct;
    }
    printf("Proceso %d lanzado en memoria\n", numeroProcesoAct);
    numeroProcesoAct++;
  }
  else
  {
    // Si no hay espacio suficiente, no ponemos proceso y lanzamos que no se pudo
    // No hay espacio suficiente
    printf("No hay espacio suficiente\n");
  }
}

// Terminar Proceso (nroProceso, memoria, procesosMuertos)
// eliminar proceso dentro de array de procesos
// procesos muer
void terminarProceso(int nroProceso, int memoria[], struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH])
{
  // Buscar proceso en memoria si existe y calcular su espacio
  int espacio = 0;
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    if (memoria[i] == nroProceso)
    {
      memoria[i] = 0;
      espacio++;
    }
  }

  // Si existe, eliminarlo
  if (espacio != 0)
  {
    procesosMuertos[idxProcesosMuertos].nro = nroProceso;
    procesosMuertos[idxProcesosMuertos].tam = espacio;
    idxProcesosMuertos++;

    // impirmir proceso eliminado correctamente
    printf("Proceso %d eliminado correctamente\n", nroProceso);
  }
  else
  {
    // Si no existe, lanzar error
    printf("El proceso %d no existe\n", nroProceso);
  }
}

// Compactar Memoria
// Quitar espacios vacios

void compactarMemoria(int memoria[])
{
  // 0  1  0  0  2  0  0  3
  int bandera = 1;
  int i = 0;

  while (bandera)
  {
    bandera = 0;

    if (memoria[i] == 0)
    {
      int aux = i;
      for (int j = aux + 1; j < MEMORY_SIZE; j++)
      {
        memoria[i] = memoria[j];
        i++;
      }
      i = aux;
      memoria[MEMORY_SIZE - 1] = 0;
      if (memoria[i] == 0)
      {
        i--;
      }
    }

    for (int k = i + 1; k < MEMORY_SIZE; k++)
    {
      if (memoria[k] != 0)
      {
        bandera = 1;
        break;
      }
    }
    i++;
  }
}

// Ver memoria
// Imprimir array de memoria
void verMemoria(int memoria[])
{
  for (int i = 0; i < MEMORY_SIZE; i++)
  {
    printf("%d ", memoria[i]);
  }
  printf("\n");
}

void imprimirProcesosMuertos(struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH])
{
  for (int i = 0; i < idxProcesosMuertos; i++)
  {
    printf("Proceso %d, tamanio %d\n", procesosMuertos[i].nro, procesosMuertos[i].tam);
  }
}

void imprimirTablaProcesos(int memoria[], struct Proceso procesosMuertos[ENDED_PROCESS_LENGTH])
{
  printf("id\t| nombre | requerimiento | estado    | direccion de memoria|\n");
  printf("====================================================================\n");
  // Imprimir procesos activos agrupados por id y direccion de memoria
  int i = 0;
  while (i < MEMORY_SIZE)
  {
    int aux = -1;
    int tam_proceso = 0;

    if (memoria[i] != 0)
    {
      aux = memoria[i];
      int j = i;
      while (memoria[j] == aux)
      {
        tam_proceso++;
        j++;
      }
      if (aux != -1)
      {
        printf("%d\t| p%d\t | %d\t\t | activo\t | %d\n", aux, aux, tam_proceso, i);
      }

      i += tam_proceso;
    }
    else
    {
      i++;
    }
  }

  for (int i = 0; i < idxProcesosMuertos; i++)
  {
    printf("%d\t| p%d\t | %d\t\t | terminado\t | %d\n", procesosMuertos[i].nro, procesosMuertos[i].nro, procesosMuertos[i].tam, -1);
  }
}