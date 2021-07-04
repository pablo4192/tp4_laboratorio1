/*
    utest example : Unit test examples.
    Copyright (C) <2018>  <Mauricio Davila>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/main_test.h"
#include "../inc/LinkedList.h"

typedef struct
{
    int legajo;
    char nombre[20];
    int materias;
    float promedio;
} eAlumno;

eAlumno* newAlumnoParam(int legajo, char* nombre, int materias, float promedio);
int alumnoSetLegajo(eAlumno* alumno, int legajo);
int alumnoSetNombre(eAlumno* alumno, char* nombre);
int alumnoSetMaterias(eAlumno* alumno, int materias);
int alumnoSetPromedio(eAlumno* alumno, float promedio);
int destroyAlumno(eAlumno* alumno);
int mostrarAlumnos(LinkedList* lista);
int mostrarAlumno(eAlumno* unAlumno);
int alumnoCmpId(void* a, void* b);



int main(void)
{
    int indice;
    int listaVacia;
    int retornoContains;
    int tam;

    //Creo la variable en estatica (tipo puntero a LL) y locomotora de linkedList, la variable estatica apunta a la locomotora y la misma tiene 2 campos: pElement (que contendra la direccion de memoria de un elemento, estructura) y pFirstNode (que contendra la direccion de memoria del proximo vagon).
    LinkedList* lista = ll_newLinkedList();
    if(lista==NULL)
    {
        printf("Hubo un problema al crear el linkedList\n");
        system("pause");
        exit(1);
    }

    //creo un puntero a linkedList que va a contener la subLista creada.
    LinkedList* subLista=NULL;

    //verifico si el linkedList tiene elementos con ll_isEmpty(); antes del ll_add()
    listaVacia=ll_isEmpty(lista);
    printf("*Retorno de ll_isEmpty: ");
    if(listaVacia)
    {
        printf("La lista esta vacia\n");
    }
    else if(!listaVacia)
    {
        printf("La lista contiene elementos\n");
    }
    else
    {
        printf("La direccion de memoria es NULL\n");
    }

    eAlumno* alumno1=NULL;
    eAlumno* alumno2=NULL;
    eAlumno* alumno3=NULL;
    eAlumno* alumno4=NULL;
    eAlumno* auxAlumno=NULL;


    //Hardcode un alumno y lo agrego al LinkedList
    alumno1=newAlumnoParam(1000, "Pepe", 4, 7);
    if(alumno1!=NULL)
    {
        ll_add(lista, alumno1);
    }

    //En mostrarAlumnos(); uso ll_len() para saber el size del LinkedList y ll_get() para obtener las cargas de los elementos del LinkedList.
    mostrarAlumnos(lista);

    //verifico si el linkedList tiene elementos con ll_isEmpty(); despues del ll_add()
    listaVacia=ll_isEmpty(lista);
    printf("*Retorno de ll_isEmpty: ");
    if(listaVacia)
    {
        printf("La lista esta vacia\n");
    }
    else if(!listaVacia)
    {
        printf("La lista contiene elementos\n");
    }
    else
    {
        printf("La direccion de memoria es NULL\n");
    }

    //Hardcodeo 3 alumnos mas
    alumno2=newAlumnoParam(1001, "Lorena", 3, 9);
    if(alumno2!=NULL)
    {
        ll_add(lista, alumno2);
    }
    alumno3=newAlumnoParam(1002, "Carlos", 6, 5);
    if(alumno3!=NULL)
    {
        ll_add(lista, alumno3);
    }
    alumno4=newAlumnoParam(1003, "Gaston", 2, 8);
    if(alumno4!=NULL)
    {
        ll_add(lista, alumno4);
    }

    mostrarAlumnos(lista);

    //Modifico un elemento de la lista con ll_set(); hago que el pElement de un vagon apunte a la carga pasada por parametro
    ll_set(lista, 0, alumno2);
    mostrarAlumnos(lista);

    //Remuevo un elemento del LinkedList con ll_remove();
    ll_remove(lista, 1);
    mostrarAlumnos(lista);

    //Busco el indice de un elemento con ll_indexOf();
    indice=ll_indexOf(lista, alumno3);
    printf("Indice retornado por indexOf: %d\n\n", indice);

    //Inserto un elemento en la lista con ll_push();
    ll_push(lista, 0, alumno1);
    mostrarAlumnos(lista);

    //Elimino un elemento de la lista, pero antes obtengo su direccion de memoria con ll_pop();
    auxAlumno= (eAlumno*) ll_pop(lista, 2); //casteo el retorno de pop ya que devuelve un puntero a void.
    mostrarAlumnos(lista);
    printf("Alumno eliminado con pop y guardado en una variable auxiliar: \n");
    mostrarAlumno(auxAlumno);

    //Verifico si en la lista esta o no el elemento especificado con ll_contains();
    retornoContains=ll_contains(lista, auxAlumno);
    printf("\n");
    if(retornoContains)
    {
        printf("El elemento esta contenido en la lista\n");
    }
    else if(!retornoContains)
    {
        printf("El elemento no esta contenido en la lista\n");
    }
    else
    {
        printf("La direccion de memoria del elemento especificado es NULL\n");
    }
    printf("\n");

    //Creo una nueva lista desde y hasta los indices especificados con ll_subList();
    subLista=ll_subList(lista, 0, 2);
    printf("SubLista creada con ll_subList: \n");
    mostrarAlumnos(subLista);

    //Verifico que todos los elementos de la subLista esten contenidos en la lista con ll_containAll();
    retornoContains=ll_containsAll(lista, subLista);
    printf("\n");
    if(retornoContains)
    {
        printf("Todos los elementos de subLista estan contenidos en la lista\n");
    }
    else if(!retornoContains)
    {
        printf("Los elementos de subLista no estan contenidos en la lista\n");
    }
    else
    {
        printf("La direccion de memoria del elemento especificado es NULL\n");
    }
    printf("\n");

    //Clono una lista con ll_clone();
    printf("Lista clonada de lista original: \n");
    subLista=ll_clone(lista);
    if(subLista!=NULL)
    {
        mostrarAlumnos(subLista);
    }

    //Ordeno la lista original con ll_sort();
    if(ll_sort(lista, alumnoCmpId, 0)==-1)
    {
        printf("No se pudo ordenar la lista\n");
    }
    printf("Lista ordenada:\n");
    mostrarAlumnos(lista);

    //Elimino todos los elementos de lista y subLista menos la locomotora con ll_clear();
    if(ll_clear(lista)==-1)
    {
        printf("Hubo un problema al eliminar los elementos\n");
    }
    else
    {
        mostrarAlumnos(lista);
        printf("Elementos de lista eliminados con exito!\n");
    }
    if(ll_clear(subLista)==-1)
    {
        printf("Hubo un problema al eliminar los elementos\n");
    }
    else
    {
        mostrarAlumnos(subLista);
        printf("Elementos de subLista eliminados con exito!\n");
    }

    //Elimino la locomotora de lista y subLista con ll_deleteLinkedList(); (tambien podria elminar vagones y locomotora juntas con esta funcion).

    if(!(ll_deleteLinkedList(lista) && ll_deleteLinkedList(subLista)))
    {
        printf("LinkedLists eliminadas!\n");
    }
    else
    {
        printf("Hubo un problema al eliminar las linkedLists\n");
    }

    tam=ll_len(lista);
    printf("ll_len retorna basura ya que linkedList lista se elimino: %d\n", tam);



    //startTesting(1);  // ll_newLinkedList
    // startTesting(2);  // ll_len
    //startTesting(3);  // getNode - test_getNode
    //   startTesting(4);  // addNode - test_addNode
    //startTesting(5);  // ll_add
    //startTesting(6);  // ll_get
    //startTesting(7);  // ll_set
    //startTesting(8);  // ll_remove
    //startTesting(9);  // ll_clear
    //startTesting(10); // ll_deleteLinkedList
    //startTesting(11); // ll_indexOf
    //startTesting(12); // ll_isEmpty
    //startTesting(13); // ll_push
    //startTesting(14); // ll_pop
    //startTesting(15); // ll_contains
    //startTesting(16); // ll_containsAll
    //startTesting(17); // ll_subList
    //startTesting(18); // ll_clone
    // startTesting(19); // ll_sort */

    return 0;
}


//Constructor por parametros
eAlumno* newAlumnoParam(int legajo, char* nombre, int materias, float promedio)
{
    eAlumno* auxAlumno= (eAlumno*) malloc(sizeof(eAlumno));
    if(auxAlumno!=NULL)
    {
        if(!(alumnoSetLegajo(auxAlumno, legajo) &&
                alumnoSetNombre(auxAlumno, nombre) &&
                alumnoSetMaterias(auxAlumno, materias) &&
                alumnoSetPromedio(auxAlumno, promedio)))
        {
            destroyAlumno(auxAlumno);
        }
    }

    return auxAlumno;
}

//Setters..
int alumnoSetLegajo(eAlumno* alumno, int legajo)
{
    int retorno=0;

    if(alumno!=NULL && legajo>0)
    {
        alumno->legajo=legajo;
        retorno=1;
    }

    return retorno;
}

int alumnoSetNombre(eAlumno* alumno, char* nombre)
{
    int retorno=0;

    if(alumno!=NULL && nombre!=NULL && (strlen(nombre)>3 || strlen(nombre)<20))
    {
        strcpy(alumno->nombre, nombre);
        retorno=1;
    }

    return retorno;
}

int alumnoSetMaterias(eAlumno* alumno, int materias)
{
    int retorno=0;

    if(alumno!=NULL && materias>0)
    {
        alumno->materias=materias;
        retorno=1;
    }

    return retorno;
}

int alumnoSetPromedio(eAlumno* alumno, float promedio)
{
    int retorno=0;

    if(alumno!=NULL && promedio>=0)
    {
        alumno->promedio=promedio;
        retorno=1;
    }

    return retorno;
}

//Getters..
int alumnoGetLegajo(eAlumno* alumno, int* legajo)
{
    int retorno=0;

    if(alumno!=NULL && legajo!=NULL)
    {
        *legajo=alumno->legajo;
        retorno=1;
    }

    return retorno;
}

int alumnoGetNombre(eAlumno* alumno, char* nombre)
{
    int retorno=0;

    if(alumno!=NULL && nombre!=NULL)
    {
        strcpy(nombre, alumno->nombre);
        retorno=1;
    }

    return retorno;
}

int alumnoGetMaterias(eAlumno* alumno, int* materias)
{
    int retorno=0;

    if(alumno!=NULL && materias!=NULL)
    {
        *materias=alumno->materias;
        retorno=1;
    }

    return retorno;
}

int alumnoGetPromedio(eAlumno* alumno, float* promedio)
{
    int retorno=0;

    if(alumno!=NULL && promedio!=NULL)
    {
        *promedio=alumno->promedio;
        retorno=1;
    }

    return retorno;
}

//Destructor..
int destroyAlumno(eAlumno* alumno)
{
    int retorno=0;
    if(alumno!=NULL)
    {
        free(alumno);
        retorno=1;
    }
    return retorno;
}
//Listar
int mostrarAlumnos(LinkedList* lista)
{
    int retorno=0;
    int tam;
    if(lista!=NULL)
    {
        //Obtengo el tamaño del LinkedList con la funcion ll_len();
        tam=ll_len(lista);
        printf("Legajo    Nombre Materias Promedio\n");
        for(int i=0; i<tam; i++)
        {
            //Obtengo los campos (carga del vagon) de la estructura con ll_get();
            mostrarAlumno( (eAlumno*) ll_get(lista,i));
            retorno=1;
        }
        printf("\n\n");

    }
    return retorno;
}

int mostrarAlumno(eAlumno* unAlumno)
{
    int retorno=0;
    int legajo;
    char nombre[20];
    int materias;
    float promedio;

    if(unAlumno!=NULL)
    {
        if(alumnoGetLegajo(unAlumno, &legajo) &&
                alumnoGetNombre(unAlumno, nombre) &&
                alumnoGetMaterias(unAlumno, &materias) &&
                alumnoGetPromedio(unAlumno, &promedio))
        {
            printf("  %d%10s        %d     %.2f\n", legajo, nombre, materias, promedio);
            retorno=1;
        }
    }
    return retorno;
}
//Cmp..
int alumnoCmpId(void* a, void* b)
{
    int retorno=0;
    eAlumno* alum1=NULL;
    eAlumno* alum2=NULL;

    if(a!=NULL && b!=NULL) //si la resta es positiva el primero es mayor que el segundo
    {
        alum1= (eAlumno*) a;
        alum2= (eAlumno*) b;
        if(alum1->legajo>alum2->legajo)
        {
            retorno=1;
        }
        else if(alum1->legajo<alum2->legajo) //si la resta da negativa el primero es menor que el segundo
        {
            retorno=-1;
        }

    }

    return retorno;
}































