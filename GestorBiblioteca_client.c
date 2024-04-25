/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "GestorBiblioteca.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define Cls system("clear")
#define Pause system("read -p \"Pulsa la tecla return para continuar..... \" a")
#define MostrarAviso(Texto) \
	{                       \
		printf(Texto);      \
		Pause;              \
	}

int menuPrincipal();
int menuAdministracion();

void Formatea(char *Salida, const char *p, int ancho, char Caracter)
{
	Cadena vacia;
	int len = ancho - strlen(p);
	int l = 0, c = 0;

	while (p[l] != '\0')
	{
		if ((unsigned char)p[l] > 128)
			c++;
		l++;
	}
	len += c / 2;

	if (len < 0)
		len = 0;
	for (int i = 0; i < len; i++)
		vacia[i] = Caracter;
	vacia[len] = '\0';

	sprintf(Salida, "%s%s", p, vacia);
}

void MostrarLibro(TLibro *L, int Pos, bool_t Cabecera)
{
	Cadena T, A, B, PI;
	if (Cabecera == TRUE)
	{
		printf("%-*s%-*s%-*s%*s%*s%*s\n", 5, "POS", 58, "TITULO", 18, "ISBN", 4, "DIS", 4, "PRE", 4, "RES");
		printf("     %-*s%-*s%-*s\n", 30, "AUTOR", 28, "PAIS (IDIOMA)", 12, "AÑO");
		Formatea(B, "*", 93, '*');
		printf("%s\n", B);
	}
	Formatea(T, L->Titulo, 58, ' ');
	Formatea(A, L->Autor, 30, ' ');
	strcpy(B, L->Pais);
	strcat(B, " (");
	strcat(B, L->Idioma);
	strcat(B, ")");
	Formatea(PI, B, 28, ' ');
	printf("%-5d%s%-*s%*d%*d%*d\n", Pos + 1, T, 18, L->Isbn, 4, L->NoLibros, 4, L->NoPrestados, 4, L->NoListaEspera);
	printf("     %s%s%-*d\n", A, PI, 12, L->Anio);
}
void gestorbiblioteca_1(char *host)
{
	CLIENT *clnt;
	int *result_1;
	int conexion_1_arg;
	bool_t *result_2;
	int desconexion_1_arg;
	int *result_3;
	TConsulta cargardatos_1_arg;
	bool_t *result_4;
	int guardardatos_1_arg;
	int *result_5;
	TNuevo nuevolibro_1_arg;
	int *result_6;
	TComRet comprar_1_arg;
	int *result_7;
	TComRet retirar_1_arg;
	bool_t *result_8;
	TOrdenacion ordenar_1_arg;
	int *result_9;
	int nlibros_1_arg;
	int *result_10;
	TConsulta buscar_1_arg;
	TLibro *result_11;
	TPosicion descargar_1_arg;
	int *result_12;
	TPosicion prestar_1_arg;
	int *result_13;
	TPosicion devolver_1_arg;

#ifndef DEBUG
	clnt = clnt_create(host, GESTORBIBLIOTECA, GESTORBIBLIOTECA_VER, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */
	int cual = menuPrincipal();
	int contrasenha = 0;
	int idAdm = 0;
	Cadena nFichero = "";

	switch (cual)
	{
	case 0:
	{
		printf("<<<<<<hasta pronto desde el menu usuario>>>>>>>\n");
		exit(2);
		break;
	}
	case 1:
	{
		printf("Por favor inserte la contraseña de Administracion:\n");
		scanf("%d", &contrasenha);
		conexion_1_arg = contrasenha;
		result_1 = conexion_1(&conexion_1_arg, clnt);
		if (result_1 == (int *)NULL)
		{
			clnt_perror(clnt, "call failed");
		}
		else
		{
			switch (*result_1)
			{
			case -1:
			{
				printf("ERROR-1: ADMINISTRADOR DENTRO DEL SISTEMA\n");
				break;
			}
			case -2:
			{
				printf("ERROR-2: CONTRASENNA INCORRECTA\n");
				break;
			}

			default:
				idAdm = *result_1; // guardamos el id del admin
				printf("		INICIO DE SESION ADMIN...\n");
				Pause;
				do
				{
					cual = menuAdministracion();
					// llamado a las opciones del menu admin
					switch (cual)
					{
					case 0: // logoff
						result_2 = desconexion_1(&idAdm, clnt);
						if (result_2 == (bool_t *)NULL)
						{
							clnt_perror(clnt, "call failed");
						}
						else
						{
							switch (*result_2)
							{
							case FALSE:
								printf("FALSE ERROR: IDAdmin no coincide con los parametros\n");
								break;

							case TRUE:
								printf("cerrando sesion de administrador...\n");
								break;
							}
						}

						break;
					case 1: // cargar datos
					{
						printf("Introduce el nombre del fichero de datos:\n");
						scanf("%s", nFichero);
						strcpy(cargardatos_1_arg.Datos, nFichero);
						cargardatos_1_arg.Ida = *result_1;
						result_3 = cargardatos_1(&cargardatos_1_arg, clnt);
						if (*result_3 == -1)
						{
							printf("ERROR: FALLO EN AUTENTICACION DE USUARIO ADMIN\n");
						}
						else if (*result_3 == 0)
						{
							printf("ERROR: NO HAY LIBROS EN EL FICHERO\n");
						}
						else
						{
							printf("SE LAN SUBIDO LOS LIBROS EXITOSAMENTE\n");
						}
						Pause;
						break;
					}
					case 2: // opcion guardar datos
					{
						printf("Guardar datos...\n");
						Pause;
						break;
					}
					case 3: // nuevo libro
					{

						// variables para los datos del libro
						Cadena nuevoIsbn = "";
						Cadena nuevoAutor = "";
						Cadena nuevoTitulo = "";
						int nuevoAnho = 0;
						Cadena nuevoPais = "";
						Cadena nuevoIdioma = "";

						// idadmin
						nuevolibro_1_arg.Ida = idAdm;
						// escaner
						printf("introducir datos de nuevo libro....\n");
						printf("introducir ISBN: \n");
						scanf("%s", nuevoIsbn);
						printf("introducir el autor: \n");
						scanf("%s", nuevoAutor);
						printf("introducir titulo: \n");
						scanf("%s", nuevoTitulo);
						printf("introducir anho: \n");
						scanf("%d", &nuevoAnho);
						printf("introducir pais: \n");
						scanf("%s", nuevoPais);
						printf("introducir idioma: \n");
						scanf("%s", nuevoIdioma);

						// settear datos en el nuevo libro
						strcpy(nuevolibro_1_arg.Libro.Isbn, nuevoIsbn);
						strcpy(nuevolibro_1_arg.Libro.Autor, nuevoAutor);
						strcpy(nuevolibro_1_arg.Libro.Titulo, nuevoTitulo);
						nuevolibro_1_arg.Libro.Anio = nuevoAnho;
						strcpy(nuevolibro_1_arg.Libro.Pais, nuevoPais);
						strcpy(nuevolibro_1_arg.Libro.Idioma, nuevoIdioma);
						nuevolibro_1_arg.Libro.NoLibros = 0;
						nuevolibro_1_arg.Libro.NoListaEspera = 0;
						nuevolibro_1_arg.Libro.NoPrestados = 0;
						// probando imprimir por terminal
						printf("datos del nuevo libro-> Isbn:%s Autor:%s Titulo:%s Anho:%d Pais:%s Idioma:%s\n",
							   nuevolibro_1_arg.Libro.Isbn, nuevolibro_1_arg.Libro.Autor, nuevolibro_1_arg.Libro.Titulo,
							   nuevolibro_1_arg.Libro.Anio, nuevolibro_1_arg.Libro.Pais, nuevolibro_1_arg.Libro.Idioma);

						// cargamos los datos al servidor
						result_3 = nuevolibro_1(&nuevolibro_1_arg, clnt);
						if (result_3 == (int *)NULL)
						{
							clnt_perror(clnt, "call failed\n");
						}
						else if (*result_3 == -1)
						{
							printf("id del administrador no coincide\n");
						}
						else if (*result_3 == 0)
						{
							printf("se cargo el nuevo libro exitosamente\n");
						}
						Pause;
						break;
					}
					case 4: // comprar libros
					{
						Cadena nIsbn = "";
						printf("Indique el ISBN del libro a comprar...\n");
						scanf("%s", nIsbn);
						comprar_1_arg.Ida = idAdm;
						strcpy(comprar_1_arg.Isbn, nIsbn);
						result_6 = comprar_1(&comprar_1_arg, clnt);
						// llamar a descargar
						descargar_1_arg.Ida = idAdm;
						descargar_1_arg.Pos = 0;
						result_11 = descargar_1(&descargar_1_arg, clnt);
						MostrarLibro(result_11, 0, TRUE);
					}
					case 5: // retirar libro
					{
						printf("Indique el ISBN del libro que desea retirar de la biblioteca...\n");
					}
					case 6: // ordenar libros
					{
						printf("Indique el criterio para ordenar los libros de la biblioteca...\n");
					}
					case 7: // buscar libros
					{
						printf("INdique un criterio para buscar libros en la biblioteca....\n");
					}
					case 8: // listar libros
					{
						printf("Mostrando listado de libros...\n");
						nlibros_1_arg = idAdm;
						result_9 = nlibros_1(&nlibros_1_arg, clnt);
						if (result_9 == (int *)NULL)
						{
							clnt_perror(clnt, "call failed");
						}
						else if (*result_9 == -1)
						{
							printf("no se han encontrado libros para listar\n");
						}
						else
						{
							descargar_1_arg.Ida = idAdm;
							descargar_1_arg.Pos = 0;
							result_11 = descargar_1(&descargar_1_arg, clnt);
							MostrarLibro(result_11, 0, TRUE);
							do
							{
								result_11 = descargar_1(&descargar_1_arg, clnt);
								MostrarLibro(result_11, descargar_1_arg.Pos, FALSE);
								descargar_1_arg.Pos = descargar_1_arg.Pos + 1;
							} while (descargar_1_arg.Pos < *result_9);
						}
						Pause;
						break;
					}
					}
				} while (TRUE);
			}
		}
		break;
	}
	}
	/*result_1 = conexion_1(&conexion_1_arg, clnt);
	if (result_1 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_2 = desconexion_1(&desconexion_1_arg, clnt);
	if (result_2 == (bool_t *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_3 = cargardatos_1(&cargardatos_1_arg, clnt);
	if (result_3 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_4 = guardardatos_1(&guardardatos_1_arg, clnt);
	if (result_4 == (bool_t *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_5 = nuevolibro_1(&nuevolibro_1_arg, clnt);
	if (result_5 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_6 = comprar_1(&comprar_1_arg, clnt);
	if (result_6 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_7 = retirar_1(&retirar_1_arg, clnt);
	if (result_7 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_8 = ordenar_1(&ordenar_1_arg, clnt);
	if (result_8 == (bool_t *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_9 = nlibros_1(&nlibros_1_arg, clnt);
	if (result_9 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_10 = buscar_1(&buscar_1_arg, clnt);
	if (result_10 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_11 = descargar_1(&descargar_1_arg, clnt);
	if (result_11 == (TLibro *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_12 = prestar_1(&prestar_1_arg, clnt);
	if (result_12 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
	result_13 = devolver_1(&devolver_1_arg, clnt);
	if (result_13 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}*/
#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int menuPrincipal()
{
	int opcionElegida = 0;
	do
	{
		Cls;
		printf("GESTOR BIBLIOTECARIO 1.0 (M. PRINCIPAL)\n");
		printf("***************************************\n");
		printf("\t1.- M. Administración\n");
		printf("\t2.- Consulta de libros\n");
		printf("\t3.- Préstamo de libros\n");
		printf("\t4.- Devolución de libros\n");
		printf("\t0.- Salir\n");
		printf("\n");
		printf("  Elige opción:\n");
		scanf("%d", &opcionElegida);
	} while (opcionElegida < 0 || opcionElegida > 4);
	return opcionElegida;
}

int menuAdministracion()
{
	int opcionElegida = 0;
	do
	{
		Cls;
		printf("GESTOR BIBLIOTECARIO 1.0 (M. ADMINISTRACION)\n");
		printf("********************************************\n");
		printf("\t1.- Cargar datos Biblioteca\n");
		printf("\t2.- Guardar datos Biblioteca\n");
		printf("\t3.- Nuevo libro\n");
		printf("\t4.- Comprar libros\n");
		printf("\t5.- Retirar libros\n");
		printf("\t6.- Ordenar libros\n");
		printf("\t7.- Buscar libros\n");
		printf("\t8.- Listar libros\n");
		printf("\t0.- Salir\n");
		printf("  Elige opción:\n");
		scanf("%d", &opcionElegida);
	} while (opcionElegida < 0 || opcionElegida > 8);
	return opcionElegida;
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	gestorbiblioteca_1(host);
	exit(0);
}
