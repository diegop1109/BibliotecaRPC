/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "GestorBiblioteca.h"
#define MAX_FILENAME_LENGTH 100

TLibro *Biblioteca = NULL; // Vector dinámico de libros
int NumLibros = 0;		   // Número de libros almacenados en el vector dinámico.
int Tama = 0;			   // Tamaño del vector dinámico. El incremento será por bloques de 4 libros.
int IdAdmin = -1;		   // Copia del Identificador de Administración enviado al usuario.
Cadena NomFichero = "";	   // Copia del nombre del último fichero binario que se ha cargado en memoria.
int CampoOrdenacion = 0;   // Copia del último campo de ordenación realizado

int *conexion_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	if (*argp != 1234)
	{
		result = -2;
	}
	else if (IdAdmin != -1) // no hay sesiones de administrador iniciadas en este momento
	{
		result = -1;
	}
	else
	{
		IdAdmin = 1 + rand() % RAND_MAX;
		result = IdAdmin;
	}
	return &result;
}

bool_t *
desconexion_1_svc(int *argp, struct svc_req *rqstp)
{
	static bool_t result;
	if (*argp != IdAdmin)
	{
		result = FALSE;
	}
	else
	{
		result = TRUE;
		IdAdmin = -1; // resetear la variable ahora que no hay ningun admin conectado
	}

	return &result;
}

int *cargardatos_1_svc(TConsulta *argp, struct svc_req *rqstp)
{
	printf("se estan cargando los datos de biblioteca\n");
	static int result = 1;
	strcpy(NomFichero, argp->Datos); //(*argp).Datos
	FILE *fDatos = NULL;

	if (argp->Ida != IdAdmin)
	{
		result = -1;
	}
	else
	{
		fDatos = fopen("Biblioteca.cdat", "rb");
		if (fDatos == NULL)
		{
			result = 0;
		}
		else
		{
			fread(&NumLibros, sizeof(NumLibros), 1, fDatos);
			//TLibro repo;//[NumLibros];

			Biblioteca = (TLibro *)malloc(sizeof(TLibro) * NumLibros);
			printf("cuantos libros hay: %d\n", NumLibros);
			if (Biblioteca == NULL)
			{
				printf("No hay libros para leer en el fichero\n");
			}
			else
			{
				printf("se han cargado los datos de biblioteca\n");
				fread(Biblioteca, sizeof(TLibro) * NumLibros, NumLibros, fDatos);
				#define repo Biblioteca[i]
				for (size_t i = 0; i < NumLibros; i++)
				{

				//	repo = Biblioteca[i];
					printf("imprimir> %ld\n", i);
					printf("%d %s %s ", repo.Anio, repo.Autor, repo.Idioma);
					printf("%s %d %d %s %s\n", repo.Isbn, repo.NoLibros, repo.NoPrestados, repo.Pais, repo.Titulo);
				}
			    #undef repo	
			}
			fclose(fDatos);
		}
	}

	return &result;
}

bool_t *
guardardatos_1_svc(int *argp, struct svc_req *rqstp)
{
	static bool_t result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *nuevolibro_1_svc(TNuevo *argp, struct svc_req *rqstp)
{
	static int result;

	if (argp->Ida != IdAdmin)
	{
		result = -1;
	}
	else
	{
		result = 0;
		printf("datos del nuevo libro-> Isbn:%s Autor:%s Titulo:%s Anho:%d Pais:%s Idioma:%s\n",
			   argp->Libro.Isbn, argp->Libro.Autor, argp->Libro.Titulo,
			   argp->Libro.Anio, argp->Libro.Pais, argp->Libro.Idioma);
		NumLibros = NumLibros + 1;
		Biblioteca = (TLibro *)realloc(Biblioteca, sizeof(TLibro) * NumLibros);
		Biblioteca[NumLibros-1] = argp->Libro; //error
		int i = NumLibros-1;
		printf("imprimir> %d\n", i);
		printf("%d %s %s ", Biblioteca[i].Anio, Biblioteca[i].Autor, Biblioteca[i].Idioma);
		printf("%s %d %d %s %s\n", Biblioteca[i].Isbn, Biblioteca[i].NoLibros, Biblioteca[i].NoPrestados, Biblioteca[i].Pais, Biblioteca[i].Titulo);
	}

	return &result;
}

int *comprar_1_svc(TComRet *argp, struct svc_req *rqstp)
{
	static int result;

	if (argp->Ida != IdAdmin)
	{
		result = -1;
	}else
	{
		result = 0;
		for (size_t i = 0; i < NumLibros; i++)
		{
			if (strstr(Biblioteca[i].Isbn, argp->Isbn))
			{
				Biblioteca[i].NoLibros = Biblioteca[i].NoLibros + argp->NoLibros;
				result = 1;
				break;
			}
			
		}
		
	}
	

	return &result;
}

int *retirar_1_svc(TComRet *argp, struct svc_req *rqstp)
{
	static int result;

	
	if (argp->Ida != IdAdmin)
	{
		result = -1;
	}else
	{
		result = 0;
		for (size_t i = 0; i < NumLibros; i++)
		{
			if (strstr(Biblioteca[i].Isbn, argp->Isbn))
			{
				if (Biblioteca[i].NoLibros - argp->NoLibros >= 0)
				{
					Biblioteca[i].NoLibros = Biblioteca[i].NoLibros - argp->NoLibros;
				} else 
				{
					Biblioteca[i].NoLibros = 0;
				}
				
				result = 1;
				break;
			}
			
		}
		
	}

	return &result;
}

bool_t *
ordenar_1_svc(TOrdenacion *argp, struct svc_req *rqstp)
{
	static bool_t result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *nlibros_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	if (*argp != IdAdmin)
	{
		result = -1;
	} else 
	{
		result = NumLibros;
	}
	

	return &result;
}

int *buscar_1_svc(TConsulta *argp, struct svc_req *rqstp)
{
	static int result;

	/*
	 * insert server code here
	 */

	return &result;
}

TLibro *
descargar_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static TLibro result;

	if (argp->Ida != IdAdmin)
	{
		return NULL;
	} else 
	{
		result = Biblioteca[argp->Pos];	
	}
	

	return &result;
}

int *prestar_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static int result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *devolver_1_svc(TPosicion *argp, struct svc_req *rqstp)
{
	static int result;

	/*
	 * insert server code here
	 */

	return &result;
}
