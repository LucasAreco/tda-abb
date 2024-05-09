#include "pa2m.h"
#include "src/abb.h"
#include <stdio.h>

int comparador_enteros(void *numero_1, void *numero_2)
{
	int *comparando_1 = (int *)numero_1;
	int *comparando_2 = (int *)numero_2;

	return *comparando_1 - *comparando_2;
}

bool es_igual(void *elemento, void *contexto)
{
	return !(*(int *)elemento == *(int *)contexto);
}

bool imprimir_recorrido(void *elemento, void *nulo)
{
	printf(" | %i |", *(int *)elemento);
	return true;
}

void crear_abb_crea_abb_vacio()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 1;
	void *elemento_1 = &numero_1;

	pa2m_afirmar(nuevo_abb != NULL,
		     "Crear ABB con un comparador válido, no devuelve NULL.");
	pa2m_afirmar(abb_crear(NULL) == NULL,
		     "Crear ABB con comparador NULL, devuelve NULL.");
	pa2m_afirmar(abb_vacio(nuevo_abb) == true,
		     "Crear ABB vació tiene tamaño 0.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_1) == NULL,
		     "Al crear un ABB vació no encuentra elementos");

	abb_destruir(nuevo_abb);
}

void insertar_elementos_en_el_abb()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 14;
	int numero_2 = 5;
	int numero_3 = 40;
	int numero_5 = 50;
	int numero_6 = 3;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;

	pa2m_afirmar(abb_insertar(nuevo_abb, elemento_1) == nuevo_abb,
		     "Al insertar en un ABB vacío, devuelve el mismo ABB.");
	pa2m_afirmar(
		abb_tamanio(nuevo_abb) == 1,
		"Al insertar en un ABB vacío se actualiza correctamente el tamaño del ABB.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_1) == elemento_1,
		     "El elemento efectivamente está insertado en el ABB.");

	pa2m_afirmar(abb_insertar(nuevo_abb, elemento_2) == nuevo_abb,
		     "Al insertar en un ABB no vacío, devuelve el mismo ABB.");
	pa2m_afirmar(
		abb_tamanio(nuevo_abb) == 2,
		"Al insertar en un ABB no vacío se actualiza correctamente el tamaño del ABB.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_2) == elemento_2,
		     "El elemento efectivamente está insertado en el ABB.");

	abb_insertar(nuevo_abb, elemento_2);
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_2) == elemento_2,
		     "Se puede insertar un elemento duplicado.");

	pa2m_afirmar(
		abb_insertar(nuevo_abb, elemento_3) == nuevo_abb,
		"Al insertar otro elemento en un ABB no vacío, devuelve el mismo ABB.");
	pa2m_afirmar(
		abb_tamanio(nuevo_abb) == 4,
		"Al insertar en un ABB no vacío se actualiza correctamente el tamaño del ABB.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_3) == elemento_3,
		     "El elemento efectivamente está insertado en el ABB.");

	pa2m_afirmar(
		abb_insertar(nuevo_abb, elemento_5) == nuevo_abb,
		"Al insertar otro elemento mayor en un ABB no vacío, devuelve el mismo ABB.");
	pa2m_afirmar(
		abb_tamanio(nuevo_abb) == 5,
		"Al insertar en un ABB no vacío se actualiza correctamente el tamaño del ABB.");
	pa2m_afirmar(
		abb_buscar(nuevo_abb, elemento_5) == elemento_5,
		"El elemento efectivamente está insertado en la derecha del ABB.");

	pa2m_afirmar(
		abb_insertar(nuevo_abb, elemento_6) == nuevo_abb,
		"Al insertar otro elemento menor en un ABB no vacío, devuelve el mismo ABB.");
	pa2m_afirmar(
		abb_tamanio(nuevo_abb) == 6,
		"Al insertar en un ABB no vacío se actualiza correctamente el tamaño del ABB.");
	pa2m_afirmar(
		abb_buscar(nuevo_abb, elemento_6) == elemento_6,
		"El elemento efectivamente está insertado en la izquierda del ABB.");

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"El ABB tiene tamaño correcto al insertar varios elementos.");

	abb_destruir(nuevo_abb);
}

void buscar_elementos_en_el_abb()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 30;
	int numero_2 = 10;
	int numero_3 = 40;
	int numero_4 = 35;
	int numero_5 = 19;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;

	abb_insertar(nuevo_abb, elemento_1);
	abb_insertar(nuevo_abb, elemento_2);
	abb_insertar(nuevo_abb, elemento_3);
	abb_insertar(nuevo_abb, elemento_5);

	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_2) == elemento_2,
		     "Encuentra un elemento que existe en el ABB.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_5) == elemento_5,
		     "Encuentra otro elemento que existe en el ABB.");
	pa2m_afirmar(
		abb_buscar(nuevo_abb, elemento_4) == NULL,
		"Al buscar un elemento que no existe en el ABB, devuelve NULL.");

	abb_quitar(nuevo_abb, elemento_2);

	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_2) == NULL,
		     "Al buscar un elemento recien eliminado, devuelve NULL.");

	abb_insertar(nuevo_abb, elemento_3);

	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_3) == elemento_3,
		     "Encuentra un elemento recien insertado en el ABB.");

	abb_destruir(nuevo_abb);
}

void quitar_elementos_en_el_abb()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 30;
	int numero_2 = 10;
	int numero_3 = 40;
	int numero_4 = 35;
	int numero_5 = 60;
	int numero_6 = 32;
	int numero_7 = 1;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;
	void *elemento_7 = &numero_7;

	abb_insertar(nuevo_abb, elemento_1);
	abb_insertar(nuevo_abb, elemento_2);
	abb_insertar(nuevo_abb, elemento_3);
	abb_insertar(nuevo_abb, elemento_4);
	abb_insertar(nuevo_abb, elemento_5);
	abb_insertar(nuevo_abb, elemento_6);

	pa2m_afirmar(abb_quitar(NULL, elemento_1) == NULL,
		     "Al pasarle un ABB NULL, devuelve NULL");

	abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido, NULL);
	printf("\n");

	abb_quitar(nuevo_abb, elemento_5);
	abb_quitar(nuevo_abb, elemento_6);

	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_5) == NULL,
		     "Elimina correctamente un nodo hoja.");
	pa2m_afirmar(abb_buscar(nuevo_abb, elemento_6) == NULL,
		     "Elimina correctamente otro nodo hoja.");

	pa2m_afirmar(abb_tamanio(nuevo_abb) == 4,
		     "Se actualiza el tamaño correctamente al eliminar.");

	abb_insertar(nuevo_abb, elemento_5);
	abb_insertar(nuevo_abb, elemento_6);
	abb_insertar(nuevo_abb, elemento_7);

	abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido, NULL);
	printf("\n");

	pa2m_afirmar(abb_quitar(nuevo_abb, elemento_4) == elemento_4,
		     "Elimina correctamente un nodo con un nodo hijo.");

	pa2m_afirmar(abb_quitar(nuevo_abb, elemento_2) == elemento_2,
		     "Elimina correctamente otro nodo con un nodo hijo.");

	abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido, NULL);
	printf("\n");

	pa2m_afirmar(abb_quitar(nuevo_abb, elemento_1) == elemento_1,
		     "Elimina correctamente el nodo raiz con dos nodos hijos.");

	abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido, NULL);
	printf("\n");

	abb_quitar(nuevo_abb, elemento_7);
	abb_quitar(nuevo_abb, elemento_3);
	abb_quitar(nuevo_abb, elemento_6);
	abb_quitar(nuevo_abb, elemento_5);

	pa2m_afirmar(abb_vacio(nuevo_abb) == true,
		     "Al quitar todos los elementos, el ABB queda vacío.");

	abb_destruir(nuevo_abb);
}

void abb_tamanio_y_vacio()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 50;
	int numero_2 = 20;
	int numero_3 = 60;
	int numero_4 = 67;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;

	pa2m_afirmar(abb_tamanio(NULL) == 0, "Un ABB nulo tiene tamaño 0.");
	pa2m_afirmar(abb_tamanio(nuevo_abb) == 0,
		     "El tamaño de un ABB vacío es 0.");

	pa2m_afirmar(abb_vacio(NULL) == true, "Un ABB nulo está vacío.");
	pa2m_afirmar(abb_vacio(nuevo_abb) == true, "Un ABB vacío está vacío.");

	abb_insertar(nuevo_abb, elemento_1);
	abb_insertar(nuevo_abb, elemento_2);
	abb_insertar(nuevo_abb, elemento_3);
	abb_insertar(nuevo_abb, elemento_4);

	pa2m_afirmar(abb_tamanio(nuevo_abb) == 4,
		     "Devuelve el tamaño de un ABB no vacío correctamente.");
	pa2m_afirmar(abb_vacio(nuevo_abb) == false,
		     "Un ABB con elementos no está vacío.");

	abb_destruir(nuevo_abb);
}

void abb_con_cada_elemento_recorridos()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	int numero_1 = 30;
	int numero_2 = 10;
	int numero_3 = 40;
	int numero_4 = 35;
	int numero_5 = 60;
	int numero_6 = 32;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;

	abb_insertar(nuevo_abb, elemento_1);
	abb_insertar(nuevo_abb, elemento_2);
	abb_insertar(nuevo_abb, elemento_3);
	abb_insertar(nuevo_abb, elemento_4);
	abb_insertar(nuevo_abb, elemento_5);
	abb_insertar(nuevo_abb, elemento_6);

	pa2m_afirmar(
		abb_con_cada_elemento(NULL, INORDEN, imprimir_recorrido,
				      NULL) == 0,
		"Al pasarle un ABB NULL con un recorrido INORDEN, devuelve 0");

	pa2m_afirmar(
		abb_con_cada_elemento(NULL, PREORDEN, imprimir_recorrido,
				      NULL) == 0,
		"Al pasarle un ABB NULL con un recorrido PREORDEN, devuelve 0");

	pa2m_afirmar(
		abb_con_cada_elemento(NULL, POSTORDEN, imprimir_recorrido,
				      NULL) == 0,
		"Al pasarle un ABB NULL con un recorrido POSTORDEN, devuelve 0");

	pa2m_afirmar(abb_con_cada_elemento(nuevo_abb, INORDEN, NULL, NULL) == 0,
		     "Al pasarle una función NULL, devuelve 0");

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, INORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren todos los elementos en INORDEN y coincide el tamaño del árbol");
	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren todos los elementos en PREORDEN y coincide el tamaño del árbol");
	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, POSTORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren todos los elementos en POSTORDEN y coincide el tamaño del árbol");

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, INORDEN, es_igual,
				      elemento_4) == 4,
		"Se recorren todos los elementos INORDEN hasta la condición de corte.");

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, PREORDEN, es_igual,
				      elemento_4) == 4,
		"Se recorren todos los elementos PREORDEN hasta la condición de corte.");

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, POSTORDEN, es_igual,
				      elemento_4) == 3,
		"Se recorren todos los elementos POSTORDEN hasta la condición de corte.");

	abb_quitar(nuevo_abb, elemento_3);
	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, INORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren todos los elementos luego de eliminar un elemento y coincide el tamaño del árbol");

	abb_quitar(nuevo_abb, elemento_6);
	abb_quitar(nuevo_abb, elemento_2);

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, INORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren todos los elementos luego de eliminar dos elementos y coincide el tamaño del árbol");

	abb_insertar(nuevo_abb, elemento_6);

	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, INORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren INORDER todos los elementos luego de insertar un elemento y coincide el tamaño del árbol");
	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, PREORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren PREORDEN todos los elementos luego de insertar un elemento y coincide el tamaño del árbol");
	pa2m_afirmar(
		abb_con_cada_elemento(nuevo_abb, POSTORDEN, imprimir_recorrido,
				      NULL) == abb_tamanio(nuevo_abb),
		"Se recorren POSTORDEN todos los elementos luego de insertar un elemento y coincide el tamaño del árbol");

	abb_destruir(nuevo_abb);
}

void abb_recorrer_y_completar_vector()
{
	abb_t *nuevo_abb = abb_crear(comparador_enteros);

	size_t max_1 = 7;
	size_t max_2 = 5;

	int *vector_numeros[max_1];
	int *vector_numeros_2[max_2];

	int numero_1 = 50;
	int numero_2 = 20;
	int numero_3 = 60;
	int numero_4 = 67;
	int numero_5 = 43;
	int numero_6 = 30;
	int numero_7 = 10;

	void *elemento_1 = &numero_1;
	void *elemento_2 = &numero_2;
	void *elemento_3 = &numero_3;
	void *elemento_4 = &numero_4;
	void *elemento_5 = &numero_5;
	void *elemento_6 = &numero_6;
	void *elemento_7 = &numero_7;

	abb_insertar(nuevo_abb, elemento_1);
	abb_insertar(nuevo_abb, elemento_2);
	abb_insertar(nuevo_abb, elemento_3);
	abb_insertar(nuevo_abb, elemento_4);
	abb_insertar(nuevo_abb, elemento_5);
	abb_insertar(nuevo_abb, elemento_6);
	abb_insertar(nuevo_abb, elemento_7);

	size_t elementos_recorridos = abb_recorrer(
		nuevo_abb, INORDEN, (void **)vector_numeros, max_1);
	size_t elementos_recorridos_2 = abb_recorrer(
		nuevo_abb, INORDEN, (void **)vector_numeros_2, max_2);

	size_t elementos_abb_null =
		abb_recorrer(NULL, INORDEN, (void **)vector_numeros, max_1);
	size_t elementos_vector_null =
		abb_recorrer(nuevo_abb, INORDEN, NULL, max_1);
	size_t elementos_tamanio_cero =
		abb_recorrer(NULL, INORDEN, (void **)vector_numeros, 0);

	pa2m_afirmar(
		elementos_abb_null == 0,
		"Completar un vector con elementos de un ABB nulo, devuelve 0.");
	pa2m_afirmar(
		elementos_vector_null == 0,
		"Completar un vector nulo con elementos de un ABB, devuelve 0.");
	pa2m_afirmar(
		elementos_tamanio_cero == 0,
		"Completar un vector de tamaño 0 con elementos de un ABB, devuelve 0.");

	pa2m_afirmar(
		elementos_recorridos == abb_tamanio(nuevo_abb),
		"Se completa un vector con todos los elementos del ABB y se llena");

	for (size_t i = 0; i < elementos_recorridos; i++) {
		printf(" %i, ", *vector_numeros[i]);
	}
	printf("\n");

	pa2m_afirmar(
		elementos_recorridos_2 == (abb_tamanio(nuevo_abb) - 2),
		"Se completa un vector con algunos elementos del ABB porque el vector se lleno.");

	for (size_t i = 0; i < elementos_recorridos_2; i++) {
		printf(" %i, ", *vector_numeros_2[i]);
	}

	abb_destruir(nuevo_abb);
}

int main()
{
	pa2m_nuevo_grupo("\nCreación de ABB");
	crear_abb_crea_abb_vacio();

	pa2m_nuevo_grupo("\nInserción de elementos en ABB");
	insertar_elementos_en_el_abb();

	pa2m_nuevo_grupo("\nBusqueda de elementos en ABB");
	buscar_elementos_en_el_abb();

	pa2m_nuevo_grupo("\nEliminar elementos en ABB");
	quitar_elementos_en_el_abb();

	pa2m_nuevo_grupo("\nTamaño y vacío de ABB");
	abb_tamanio_y_vacio();

	pa2m_nuevo_grupo("\nIterador interno en ABB");
	abb_con_cada_elemento_recorridos();

	pa2m_nuevo_grupo("\nRecorrer ABB y llenar vector");
	abb_recorrer_y_completar_vector();

	return pa2m_mostrar_reporte();
}
