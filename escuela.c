////include tells the compiler to include a library
#include <stdio.h>  //standard Input Output (print, getchar)
#include <string.h>  //String manipulation (strcmp, strcat, strlen)
#include <stdlib.h>  //Memory and Utilities (funciones grales como exit)
#include <ctype.h>  //Character handling (isdigit)

char car;  //guarda un caracter
char palabra[50];  //string w max50 chars
char nombreEscuela[100];  //nombre completo de la escuela
//char	nombreSalon[100];
//char	nombreAlumno[100];

float promedioEscuela;  //guarda el prom gral de la Escuela

typedef enum { TRUE = 1, FALSE = 0 } T_bool;  //da valor de T o F segun un 1 o 0

#define MAX_SALONES 20  //max de salones allowed
int numSalones;  //quan real de salones leidos
char nombreSalon[MAX_SALONES][100];  //name de c/u
float promedioSalon[MAX_SALONES];

#define MAX_ALUMNOS 30  //max alumnos por salon
int numAlumnos[MAX_SALONES];  //quan alumnos por salon
char nombreAlumno[MAX_SALONES][MAX_ALUMNOS][100];  //name c/u
float promedioAlumno[MAX_SALONES][MAX_ALUMNOS];  //promedio individual

#define MAX_CALIFS 25  //max califs por alumno
int numCalifs[MAX_SALONES][MAX_ALUMNOS];  //quan califs de c/alumno
float califs[MAX_SALONES][MAX_ALUMNOS][MAX_CALIFS];  //3dim array que almacena califs x salon x alumno

//declaro 3 variables del tipo integer:
int s,	//index salones
	a,	//index de alumnos
	c;  //index de califs
	// son var globales aqui, son var temporales o automaticas si van en el int main
float ap,	//acumulador prom alumno
	as,		//acumulador prom salon
	ae;  	//acumulador prom escuela

/**********************************************************/

void adquirirPalabraSiguiente()  //la funcion que lee palabra x palabra
{
    int i;
	//mientras que el car no sea igual a espacio, o a tabulador, o a new line, o a carriage return, o sea end of file... keep reading the next char
    while (((car==' ')||(car=='\t')||(car=='\n')||(car=='\r')) && (car!=EOF))
        car=getchar();
//All of this means 'keep reading characters while they are whitespace and not-EOF'

    i=0;  //initialize the index to start storing characters from the beginning of 'palabra'


    while (((car!=' ')&&(car!='\t')&&(car!='\n')&&(car!='\r')) && (car!=EOF))  //these are the characters we told it to stop when they appear
    {
        palabra[i]=car; //guarda el car dentro del array palabra
        i++;  //i=i+1
        car=getchar(); //reads ONE char from std input, returns it and store it, read the next char aaand repeat
    }

    palabra[i]=0x00; //this is an hexadecimal zero (same as '\0') w/o this it wouldnt be a valid C string
}

/**********************************************************/

T_bool esUnaCalificacion()  	//this checks if "palabra" represents a valid decimal. Then the T_bool is a function that returs a boolean (TRUE or FALSE)
{
    int i,len;  //it could be int i; int len;
	//i recorre each char of the word, len stores la longitud de la palabra
    T_bool puntoEncontrado=FALSE;  //bc no decimal point has been seen

    len=strlen(palabra);  //gets the lenght of the current word

    for(i=0;i<len;i++)  //analyze each char 1x1
    {
        if(palabra[i]=='.')  //corroboramos si el car es . decimal
        {
            if(puntoEncontrado)
                return FALSE;  //si ya habia un punto antes, entonces NO es valido
            else
                puntoEncontrado=TRUE;   //marca q ya encontro un . decimal
        }
        else if(!isdigit(palabra[i]))
            return FALSE;  //si no es . ni un num entonces NO es calif
    }

    return TRUE;  //no erro encontrado
}

/**********************************************************/
//esta funcion inicia la lectura del primer car del input y hace un buclesito
void adquirirPrimeraPalabra()
{
    car=getchar();
    adquirirPalabraSiguiente();  //this calls another function
}

/**********************************************************/

void adquirirNombreSalon()
{
	//palabra vale: Salon
    nombreSalon[numSalones][0]='\0';  //starts w the string name empty

    adquirirPalabraSiguiente();
	
	//compares two strings, in this case means palabra is NOT equal to "FinSalon", nor empty
    while((strcmp(palabra,"FinSalon")!=0)&&(strcmp(palabra,"")!=0))  // Continúa leyendo palabras hasta encontrar "FinSalon"
    {
        if(nombreSalon[numSalones][0]!='\0')
        strcat(nombreSalon[numSalones]," ");
        strcat(nombreSalon[numSalones],palabra);

        adquirirPalabraSiguiente(); //reads the next word. The loop repeats
    }
}  // palabra vale: "FInSalon" oooo " "

/**********************************************************/

void procesarSalon()  //this detecta si son nombre, califs, los almacena y contea
{
    numAlumnos[numSalones]=0;  //El index de salon actual es: numSalones

    adquirirPalabraSiguiente();

    //procesa alumnos hasta encontrar Salon o el EOF
    while((palabra[0]!='\0') && (strcmp(palabra,"Salon")!=0))
    {
        nombreAlumno[numSalones][numAlumnos[numSalones]][0]='\0';  //inicia el string donde se almacena el name del alumno

        while((palabra[0]!='\0') &&
              (!esUnaCalificacion()) &&
              (strcmp(palabra,"Salon")!=0))
        {  // Si el nombre ya tiene texto, agrega un espacio antes de la siguiente palabra
            if(nombreAlumno[numSalones][numAlumnos[numSalones]][0]!='\0')
                strcat(nombreAlumno[numSalones][numAlumnos[numSalones]]," ");  //agrega la current word al nombre del alumno

            strcat(nombreAlumno[numSalones][numAlumnos[numSalones]],palabra);

            adquirirPalabraSiguiente();
        }

        if(nombreAlumno[numSalones][numAlumnos[numSalones]][0]=='\0')
            break;
        // Si el nombre ya tiene texto, agrega un espacio antes de la siguiente palabra
        numCalifs[numSalones][numAlumnos[numSalones]]=0;

        while((palabra[0]!='\0') && esUnaCalificacion())  // Mientras la palabra sea una calificación, la guarda
        { 
            sscanf(palabra,"%f", &califs[numSalones][numAlumnos[numSalones]] [numCalifs[numSalones][numAlumnos[numSalones]]]);

            numCalifs[numSalones][numAlumnos[numSalones]]++;

            adquirirPalabraSiguiente();
        }
        numAlumnos[numSalones]++;  // Incrementa el número de calificaciones del alumno
    }
}

/**********************************************************/
// lee el nombre completo de la escuela hasta encontrar FinEscuela
void adquirirNombreEscuela()
{
    nombreEscuela[0]='\0';  //iniciamos la cadena vacia

    adquirirPalabraSiguiente();
    // procesa la palabra, y construimos el nombre hasta FinEscuela
    while((strcmp(palabra,"FinEscuela")!=0)&&(strcmp(palabra,"")!=0))
    {
        if(nombreEscuela[0]!='\0')  // Si ya hay texto en el nombre, agrega un espacio antes de la siguiente palabra
            strcat(nombreEscuela," ");

        strcat(nombreEscuela,palabra);

        adquirirPalabraSiguiente();
    }
}

/**********************************************************/
//este es nuestro void <3 donde hacemos los calculos de promedios y sus reglas para evitar nan
void calcularPromedios()  
{
    ae=0;  // Inicializa el acumulador del promedio de la escuela

    for(s=0;s<numSalones;s++)  //recorremos salon x salon
    {
        as=0;  // Inicializa el acumulador de salon

        for(a=0;a<numAlumnos[s];a++)  //recorremos alumno x alumno
        {
            ap=0;  // Inicializa el acumulador de alumno

            for(c=0;c<numCalifs[s][a];c++)  
                ap+=califs[s][a][c];  //suma todas las califs del alumno

            if(numCalifs[s][a]>0)
                promedioAlumno[s][a]=ap/numCalifs[s][a];
            //calcula el promedio del alumno si es mayor que 0
            // de lo contrario, asignale el valor de 0
            else
                promedioAlumno[s][a]=0;

            as+=promedioAlumno[s][a];  // Agrega el promedio del alumno al acumulador del salon
        }

        if(numAlumnos[s]>0)  // Agrega el promedio del alumno al acumulador del salón
            promedioSalon[s]=as/numAlumnos[s];
        else
            promedioSalon[s]=0;

        ae+=promedioSalon[s];  // Agrega el prom del alumno al acumulador del salon
    }

    if(numSalones>0)
        promedioEscuela=ae/numSalones;  // Agrega el promedio del alumno al acumulador del salón
}

/**********************************************************/
// this is the entry point of the program
int main()  //this returns an integer to the OS
{
    numSalones=0;  //inicia el contador de salones

    adquirirPrimeraPalabra();
    //aca verificamos que el archivo inicie con la palabra Escuela
    if(strcmp(palabra,"Escuela")!=0)
    {   
        fprintf(stderr,"Error palabra Escuela no encontrada\n");    //de lo contrario imprime un error
        exit(1);
    }
    
    adquirirNombreEscuela();  //aqui vamos construyendo el nombre de la Escuela

    adquirirPalabraSiguiente();

    while(strcmp(palabra,"Salon")==0)  //procesamos todos los salones de la escuela
    {
        adquirirNombreSalon();
        procesarSalon();
        numSalones++;
    }

    calcularPromedios();  //aqui mandamos a llamar a nuestro void

    printf("╔═════════════════════════════════════════════╗\n");
    printf("║     RESULTADO DE PROMEDIOS POR ESCUELA      ║\n");
    printf("╚═════════════════════════════════════════════╝\n");
    printf("Escuela: %s\n", nombreEscuela);
    printf("Promedio de la escuela: %.2f\n\n", promedioEscuela);  //imprimimos el nombre de la escuela y su promedio

	for(s=0;s<numSalones;s++)  //aca recorremos salon x salon 
{
    printf("\n---------------- SALON ----------------\n");
    printf("%s\t|  Promedio del salon: %.2f\n\n", nombreSalon[s], promedioSalon[s]);  //imprimimos el nombre del salon y su promedio

    for(a=0;a<numAlumnos[s];a++)  //recorremos alumno x alumno
    {
        printf("\t> %s\n", nombreAlumno[s][a]);  //imprimimos el name del alumno

        printf("\t");
        for(c=0;c<numCalifs[s][a];c++) // imprime las califs individuales del alumno
        {
            printf("%6.2f ", califs[s][a][c]);  
        }   
        printf("\n\tPromedio: %.2f\n\n", promedioAlumno[s][a]);  //imprime el promedio del alumno
    }
}
    //Ya despues de leer toda la info, cerramos
	printf("\n╚══════════════ FIN DE REPORTE ══════════════╝\n");
    return 0;  //finalizamos el programa correctamente:)
}
//	./salon <Escuela.datos 
//	> out 			this 
//	|tee out		this print
//	-o en el compilador means salida (output)
//	ddd (es otra app)