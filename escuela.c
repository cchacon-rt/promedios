//include tells the compiler to include a library
#include <stdio.h>	//means Standard Input Output
#include <string.h>	//means String manipulation
#include <stdlib.h>	//means Memory and Utilities
#include <ctype.h>	//means Character handling

char	car;			//stores ONE character
char	palabra[50];		//string w max50 characters
char	nombreEscuela[100];	//nombre completo de la escuela
//char	nombreSalon[100];
//char	nombreAlumno[100];

typedef enum {			//creates a custom Boolean type
	TRUE = 1, FALSE = 0	//da valor de T o F segun un 1 o 0
	} 	T_bool;

#define MAX_SALONES 20
	int	numSalones;	//num salones
	char	nombreSalon[MAX_SALONES][100];	//nombres completos de los salones

float 	promedioSalon[MAX_SALONES];

#define MAX_ALUMNOS 30
	int	 numAlumnos [MAX_SALONES];	//el numero de alumnos
	char	 nombreAlumno[MAX_SALONES][MAX_ALUMNOS][100];	//nombres completos de

float	promedioAlumno[MAX_ALUMNOS][MAX_ALUMNOS];

#define MAX_CALIFS 25
	int	numCalifs[MAX_SALONES][MAX_ALUMNOS];	//num calificaciones
	float	califs[MAX_SALONES][MAX_ALUMNOS][MAX_CALIFS];	//calificaciones (float)

#define calificacion(salon,alumno)\
	califs[salon][alumno[salon]][numCalifs[salon][alumno[salon]]]

int s, a, c;
float ap, as, ae;

/******************************************************************/

void			//The function 
adquirirPalabraSiguiente ()	//()Takes no parameters
{
	int i;		//Declares an integer i (entero), like an index for the array (arreglo)
	while (((car == ' ')	//space
			|| (car == '\t')	//tab
			|| (car == '\n')	//newline
			|| (car == '\r')	//carriage return
			&& (car != EOF)))	//end of file
 			car = getchar ();	//reads one character from standard input
//All of this means 'keep reading characters while they are whitespace and not-EOF'
	i = 0;		//initialize the index to start storing characters from the beginning of 'palabra'

	//basically it reads a word from input, a "read next word-loop"
	while (((car != ' ') && (car != '\t') && (car != '\n') && (car != '\r')) && (car != EOF))  //these are the characters we told it to stop when they appear
	{
		palabra[i] = car;	//store the car into the array(arreglo) palabra at position 'i'
		i++;	// i=i+1	move  to the next position in the array
		car = getchar();	//reads ONE char from std input, returns it and store it, read the next char annnnd repeat
	}

	palabra[i]=0x00;	//this is an hexadecimal zero (same as '\0') w/o this it wouldnt be a valid C string
}
//For y While se utilizan para lo mismo
//Also, apparently  we could use: scanf("%s", palabra);


/************************************************************/
//Esta funcion analiza la palabra "palabra" y regresa TRUE si es una cadena que se puede convertir en valor real.
//Regresa FALSE en el caso contrario.

T_bool esUnaCalificacion() 	//this checks if "palabra" represents a valid decimal. Then the T_bool is a function that returs a boolean (TRUE or FALSE)
{
	int i,	//loop index
	len;	//length of the string
 	//could it be int i; int len;


	T_bool puntoEncontrado;		//initialize it
	puntoEncontrado = FALSE;	//bc no decimal point has been seen
	len = strlen (palabra);		//from string.h
	//above counts chars in a string until it finds '\0'
	for (i=0; i<len;i++){	//it checks every char in palabra
		if(palabra[i] == '.'){	//check if current char is a decimal point
		if(puntoEncontrado){	//if we already saw a decimal point before
		fprintf(stderr,"ERROR Hay mas de un '.' en la expresion:%s\n",palabra);}	//prints formatted output annd then a standard error stream
		else	puntoEncontrado = TRUE;}	//if this is the 1st dot, mark we found one, and the next one mark it as ERROR

		else{ if(!isdigit(palabra[i]))		
			return FALSE;
		}	//any char that isnt a digit return false
	}
return TRUE;	//if loops dont retunr false, then the sting is valid:)
}	//all above verifies every char 

void adquirirPrimeraPalabra()	//reads the 1st char from input n calls other funct 2 read the rest of the word
{
	car = getchar();	//store the 1st input char into the global variable car
	adquirirPalabraSiguiente();	//this calls another function
}

void adquirirNombreSalon ()
{
	//Palabra vale: "Salon"
	nombreSalon[numSalones][0]='\0';	//initialize the string empty
	adquirirPalabraSiguiente();	//reads the next word into palabra
	while((strcmp(palabra,"FinSalon")!=0)	//compares two strings, in this case means palabra is NOT equal to "FinSalon"
		&&(strcmp(palabra,"")!=0))	//this checks if palabra is NOT empty
		{	//Procesar palabra
			if(nombreSalon[numSalones][0]!='\0')	//is not empty
			strcat(nombreSalon[numSalones]," ");	//string concatenate, adds space between words
			strcat(nombreSalon[numSalones], palabra);	//str concatenate, appends the current word
			adquirirPalabraSiguiente();	//reads the next word. The loop repeats
			// palabra vale: "FInSalon" oooo " "
		}
	printf("Nombre Salon:%s\n",nombreSalon[numSalones]);	//just to show the result
}

void procesarSalon()	//this clasifica si son calificaciones o No
{
	//El index de salon actual es: numSalones
	numAlumnos[numSalones] = 0;
	adquirirPalabraSiguiente();	//read the word from input
	while((palabra[0]!='\0')&&((!esUnaCalificacion())||(strcmp(palabra,"Salon")!=0))){	//mientras que la palabra no este vacia && no sea una calificacion ||  no sea la palabra Salon

		//revisar si los iguiente si va aqui: 	nombreAlumno[numSalones][numAlumnos[numSalones]][0]='\0';

		while((palabra[0]!='\0')&&(!esUnaCalificacion())){
			printf("NO ES calificacion:%s\n",palabra);	//print formatted, %s means insert or print a string here, then \n new line. Finally palabra replaces %s, meaning palabra is the string to insert
			adquirirPalabraSiguiente();
		}	//Estoy parado en una palabra que es una calificacion
		
		while((palabra[0]!='\0')&&(esUnaCalificacion())){	//mientras que la palabra NO este vacia && SI es una calificacion
			printf("ES calificacion:%s\n",palabra);	//print formattted, %s insert the palabra string, then \n new line
			adquirirPalabraSiguiente();
			//string scanf
			sscanf (palabra,"%f", & calificacion(numSalones,numAlumnos));
			//sscanf(palabra, "%f"; & calificacion[numSalones][numAlumnos[numSalones]][numCalificacion[numSalones][numAlumnos][numSalones]]) = 0,0;
			//printf("Es Calificacion: %f\n",palabra);
			printf("Valor=%2.2f\n",calificacion(numSalones,numAlumnos));
			//es un flotante
			//numAlumnos[numSalones] = numAlumnos[numSalones] + 1;
		}numAlumnos[numSalones]++;
	}
}

void adquirirNombreEscuela()
{
	nombreEscuela[0]='\0';	//inicia string empty
	adquirirPalabraSiguiente();	
	
	while ((strcmp (palabra, "FinEscuela")!=0)&&(strcmp(palabra,"")!=0)){		//procesar la palabra
		if(nombreEscuela[0]!='\0')
		strcat(nombreEscuela," "); //las llaves cuando solo hay una instruccion no son necesarias
		strcat(nombreEscuela, palabra);

		adquirirPalabraSiguiente();
	}	//palabra vale: "FinEscuela" o " "
	printf("Nombre de la Escuela:%s\n",nombreEscuela);
}



void calcularPromedios()
{
    ae = 0.0;
    for(s = 0; s < numSalones; s++) {
        as = 0.0;
        printf("\n--- Salon %d ---\n", s+1);
        for(a = 0; a < numAlumnos[s]; a++) {
            ap = 0.0;
            for(c = 0; c < numCalifs[s][a]; c++) {
                ap = ap + califs[s][a][c];
            }
            promedioAlumno[s][a] = ap / numCalifs[s][a];
            printf("Alumno %d promedio: %.2f\n", a+1, promedioAlumno[s][a]);
            as = as + promedioAlumno[s][a];
        }
        promedioSalon[s] = as / numAlumnos[s];
        printf("Promedio del salon %d: %.2f\n", s+1, promedioSalon[s]);
        ae = ae + promedioSalon[s];
    }
    promedioEscuela = ae / numSalones;
    printf("\nPromedio de toda la escuela: %.2f\n", promedioEscuela);
}




/*la palte impoltaaante del programa
ths is the entry point of the program
*/
int main ()	//this returns an integer to the OS
{
   
int		s, 
		a,
		c;
float	ap, 
		as,
		ae;
   
	ae = 0.0;
	//	int     s, a, c;        //declaro tres variables del tipo int
        //son variables temporales o automaticas

	numSalones = 0;		//inicia el conteo
	adquirirPrimeraPalabra();
	printf ("palabra despues adquirirPrimeraPalabra: %s\n", palabra);	//verifies what was read, ((probb common while debugging?))
	if (strcmp(palabra,"Escuela") !=0) {
		fprintf (stderr, "Error palabra\"Escuela\"no encontrada - Stop!\n");
		exit (1);
	}
	//Palabra vale "Escuela"
	adquirirNombreEscuela();
	adquirirPalabraSiguiente();
	while (strcmp (palabra, "Salon") ==0) {
		adquirirNombreSalon();
		//palabra vale "FinSalon"
		procesarSalon();
		numSalones++;
		//Ya acabamos de adquirir un salon y sus respectivos datos.

		//NO ! adquirirPalabraSiguiente();


		for (s = 0; s < numSalones; s++){
			as = 0.0;
			for (a = 0; a < numAlumnos[s]; a++){
				ap = 0.0;
				for (c = 0; c < numCalifs[s][a]; c++){
					ap = ap + califs[s][a][c];
				}
				promedioAlumno[s][a] = ap / numCalifs[s][a];
				as = as + promedioAlumno[s][a];
			}
			promedioSalon[s] = as / numAlumnos[s];
			ae = ae + promedioSalon[s];
		}
		promedioEscuela = ae / numSalones;
	}
	for (s= 0; s < numSalones; s++) {
		printf("\nSalon %s\n", nombreSalon[s]);
		for (a = 0; a < numAlumnos[s]; a++) {
			printf("	Alumno %s -> Promedio: %.2f\n",
			nombreAlumno[s][a], promedioAlumno[s][a]);
		}
		printf("Promedio del salon: %.2f\n", promedioSalon[s]);
	}

	printf("\nPromedio de la escuela: %.2f\n",
	promedioEscuela);

	/* Despues de leer toda la info

    calcularPromedios();
    imprimirPromedios();

    return 0;*/
}


//	./salon <Escuela.datos 
//	> out 			this 
//	|tee out		this print
//	-o en el compilador means salida (output)
//	ddd (es otra app)
