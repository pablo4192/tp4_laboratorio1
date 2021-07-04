#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)              //valido !=NULL
    {
        this->pFirstNode=NULL;  //el nodo de la locomotora apunta a NULL cuando no tiene vagones
        this->size=0;           //cantidad de nodos que posee el linked list
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux=this->size;
    }


    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* auxNode=NULL;                                      //apunto a NULL el puntero a nodo creado para guardar en cada iteracion el campo pNext node cuyo valor es la direccion de memoria del proximo vagon.

    //el indice que me pasan es menor al size del linkedList
    if(this!=NULL && nodeIndex>-1 && nodeIndex<ll_len(this))
    {
        auxNode=this->pFirstNode;                           //guardo en aux la direccion del primer vagon

        for(int i=1; i<=nodeIndex; i++)                     //itero hasta que i sea <= al indice que me pasaron por parametro
        {
            auxNode=auxNode->pNextNode;                     //copio la direccion de memoria del proximo vagon
        }                                                   //i=1 por que si nodeIndex es 0 ya firstNode es la direccion del vagon 0
    }

    /* otra forma
       while(nodeIndex>0)                                   //usa el nodeIndex que viene por parametro como condicion
       {
           auxNode=auxNode->pNextNode;                      //auxNode tiene la direccion de memoria del primer vagon por eso puedo acceder a su campo nextNode, que es la direccion de memoria del vagon siguiente
           nodeIndex--;
       }*/

    return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)    //ESTE NO SE PROGRAMA
{

    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* auxNodo=NULL;                                     //creo dos variables puntero a estructura tipo Node
    Node* nodoAnterior=NULL;
    //por si quiere agregar un vagon a lo ultimo del linked
    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
    {
        auxNodo=(Node*) malloc(sizeof(Node));               //creo en dinamica estructura tipo Node* a agregar al linked
        if(auxNodo!=NULL)
        {
            auxNodo->pElement=pElement;                     //le asigno la carga que llego por parametro, que es el puntero a la direccion de memoria de un elemento
            auxNodo->pNextNode=getNode(this, nodeIndex);    //obtengo direccion de memoria del vagon que voy a suplantar (el del indice que me pasaron) y la guardo en mi campo nextNode

            if(nodeIndex==0)                                //si nodeIndex es 0
            {
                this->pFirstNode=auxNodo;                    //engancho el vagon nuevo al pFirstNode de la locomotora y no hace falta enganchar nada atras
            }
            else                                            //si ya hay otros vagones
            {
                nodoAnterior=getNode(this, nodeIndex-1);    //obtengo la direccion de memoria del vagon que tengo delante
                nodoAnterior->pNextNode=auxNodo;            //y le copio en su campo nextNode mi direccion de memoria (vagon agregado)
            }
            this->size++;                                   //una vez que agregue tengo que incrementar en 1 el size de la locomotora (tamaño del linked)
            returnAux=0;                                    //retorno valor que me indica que esta todoOk

        }
    }


    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    //int indice;           //puedo no declararla

    if(this!=NULL)
    {
        returnAux=addNode(this, ll_len(this), pElement); //si addNode retorna 0 esta todo bien

        //indice=ll_len(this);
        //addNode(this, indice, pElement);
        //returnAux=0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index) //retorna el pElement (puntero a direccion de memoria del siguiente vagon) de un nodo (carga de un vagon)
{
    void* returnAux = NULL;
    Node* auxNode=NULL;
    //que el indice recibido por parametro sea menor al tamaño del linked (tamaño: 4, vagones: 0,1,2,3)
    if(this!=NULL && index>=0 && index<ll_len(this)) //Esta validacion la puedo evitar ya que get Node la hace previamente
    {
        auxNode=getNode(this, index); //el nodo que me retorna  getNode lo guardo en la variable puntero a nodo aux
        if(auxNode!=NULL)
        {
            returnAux=auxNode->pElement; //guardo en el retorno el nodo (direccion de memoria del vagon que tiene pElement y nextNode)
        }
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode=NULL;
    //se puede sacar esta validacion ya que get node ya valida en su codigo
    if(this!=NULL && index>=0 && index<ll_len(this)) //indice sea menor al size del linked
    {
        auxNode= getNode(this, index);    //guardo el nodo retornado en variable puntero a nodoaux
        if(auxNode!=NULL)
        {
            auxNode->pElement=pElement;   //guardo en pElement del nodo que me retorno el getNode el pElement que me pasaron por parametro
            returnAux=0;
        }

    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{

    int returnAux = -1;
    Node* anteriorNode=NULL;
    Node* aux=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
        //actualNode=getNode(this, index); //con la linea 252 no haria falta declarar el nodo actual
        if(index==0)                                            //en este se quiere eliminar el vagon 0, si es asi tengo que enganchar el vagon 1 a la locomotora
        {
            aux=this->pFirstNode;           //aux->pNextNode;   //this->pFirstNode=actualNode->pNextNode; //la locomotora apunta al nextNode del vagon 0, que es la direccion de memoria del vagon 1 (lo enganche)
            this->pFirstNode = (this->pFirstNode)->pNextNode;   //(this->pFirstNode): representa a la direccion de memoria del vagon 0, y accedo a su campo pNextNode que es la direccion de memoria del vagon 1 (lo enganche)
        }
        else
        {
            anteriorNode=getNode(this, index-1);                //me retorna un puntero al vagon de adelante (el anterior)
            if(anteriorNode!=NULL)
            {
                aux=anteriorNode->pNextNode;                 //aux->pNextNode;
                anteriorNode->pNextNode= (anteriorNode->pNextNode)->pNextNode; //(anteriorNode->pNextNode): representa a la direccion de memoria del vagon actual, con ->pNextNode puedo acceder a la direccion de memoria del siguiente vagon
            }                                                                  //engancho al anterior (index -1) al siguiente del indice que me pasaron para eliminar (index+1)
        }
        free(aux);                                              //libero la direccion de memoria del indice que me pasaron
        this->size--;                                           //resto 1 al size del linked
        returnAux=0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)  //elimina todos los vagones menos la locomotora
{
    int returnAux = -1;

    if(this!=NULL)
    {
        //tamaño -1 = ultimo indice
        for(int i=ll_len(this)-1; i>=0; i--)    //hago el recorrido de atras para adelante, si lo hago de adelante para atras me quedan desenganchados algunos vagones
        {
            ll_remove(this, i);
            returnAux=0;
        }
    }
    /*    !ll_isEmpty(this) mientras no este vacio
    while(ll_len(this)!=0) //mientras tengo elementos borro el primero
    {
        ll_remove(this, 0); //borro el primero (remove se encarga de enganchar)
    }
    */
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)  //tambien: if(!clear(this)) //si clear devuelve 0 es que esta todo bien
    {
        ll_clear(this);
        free(this); //free de la locomotora
        returnAux=0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            if(ll_get(this, i)==pElement)
            {
                returnAux=i;        //retorno el indice donde encontro la igualdad la direccion de memoria que retorno ll_get con la direcciion de memoria que me pasaron por parametro (pElement)
                break;
            }

        }
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;     //si es NULL

    if(this!=NULL)
    {
        returnAux=1;        //si no tiene elementos
        if(ll_len(this)>0)  //si el size es mayor a 0
        {
            returnAux=0;
        }
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement);  //todas las validaciones las tiene addNode
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    returnAux=ll_get(this, index);              //no lo valido por la bajada de linea (pero si habria que)           //consigo la direccion de memoria del elemento en el indice pasado por parametro
    if(ll_remove(this, index))                   //elimino el elemento y remove se encarga de enlazar los vagones de los costados
    {
        returnAux=NULL;                         //aca valido si remove funciono bien
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;                     //si no entra al if
    if(this!=NULL)
    {
        returnAux=0;       //tambien !=-1
        if(ll_indexOf(this, pElement)>=0)   //devuelve -1 si el puntero a la lista es NULL y si no lo encuentra tambien, y el indice si lo encontro.
        {
            returnAux=1;                    //si indexOf encontro igualdad
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int tam;
    if(this!=NULL && this2!=NULL)
    {
        tam=ll_len(this2);                           //necesito el tamaño del segundo
        returnAux=1;                                 //precargo la variable de retorno
        for(int i=0; i<tam; i++)
        {
            if(!ll_contains(this, ll_get(this2, i)))  //comparo cargas del this2 con this
            {
                //si falla una vez entra y corta
                returnAux=0;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL && from>=0 && to>=from && to<=ll_len(this))
    {
        cloneArray=ll_newLinkedList();
        if(cloneArray!=NULL)
        {
            for(int i=from; i<to; i++)
            {
                if(ll_add(cloneArray, ll_get(this, i))==-1)
                {
                    ll_deleteLinkedList(cloneArray);
                    cloneArray=NULL;
                    break;
                }
            }
        }

    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    return ll_subList(this, 0, ll_len(this));  //te hace un clon desde 0 hasta el size de this
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int tam;
    void* auxI=NULL;
    void* auxJ=NULL;
    if(this!=NULL && pFunc!=NULL && (order==0 || order==1))
    {
        tam=ll_len(this);
        for(int i=0; i<tam-1; i++)
        {
            for(int j=i+1; j<tam; j++)
            {
                auxI=ll_get(this, i);  //me traigo el contenido
                auxJ=ll_get(this, j);
                if( (pFunc(auxI, auxJ)<0 && !order) || (pFunc(auxI, auxJ)>0 && order)) //
                {
                    ll_set(this, i, auxJ);
                    ll_set(this, j, auxI);
                }

            }
        }
        returnAux=0;
    }




    return returnAux;

}












