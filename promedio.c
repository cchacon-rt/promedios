#include<stdio.h>
#include<stdlib.h>

//Guillermo
float main()
{
    int NUM_CAL = 5;
    float cal[NUM_CAL];

    cal[0] = 5;
    cal[1] = 5.4;
    cal[2] = 8;
    cal[3] = 3.2;
    cal[4] = 0;

    int i;
    float sum = 0;
    for(i=0;i<NUM_CAL;i++)
    {
        sum = sum + cal[i];
    }
    float prom = sum/NUM_CAL;
    printf("%.2f\n",prom);
    return prom;
}

//Dominique
float promedioEscuela;
float promedioSalon[MAX_SALONES];
float promedioAlumno[MAX_SALONES][MAX_ALUMNOS];

int s, a, c;
float ap, as, ae;
ae = 0.0;	
 for(s=0; s<numSalones;s++) {
	as= 0.0;

	for(a=0;a<numAlumnos[numSalones];a++){
	ap = 0.0;
    //k=0.0;
		for(c=0;c<numCalifs[numSalones][numAlumnos[numSalones]];c++){
            // k = k+calificacion(_)(_)
			ap = ap + califs[s][a][c];	//ap es la suma de las calificaciones de a
		}	//promedio alumnos
	}	promedioAlumnos[s][a] = ap/numCalifs[s][a]; //promedio salon
    //= k / numCalifs[][];
   as = as+promedioAlumno[s][a];
    promedioSalon[s]=as/numAlumnos[s];
    //k=k+promedios[s][a]
//} promedio[s]=k/numAlumnos[s];
 }		//promedio escuela
promedioEscuela=ae/numSalones;
ae=ae+promedioSalon[s];


//Domi II


 int     a, s, e;        //declaro tres variables del tipo int
     //son variables temporales o automaticas

 float pa, ps, pe;	//promedio alumno, salon, escuela
 
  for(s=0; s < numSalones; s++) {
         as= 0.0;
	printf(); 

         for(a=0;a<numAlumnos[s];a++){
         ap = 0.0;
                 for(c=0;c<numCalifs[s][a];c++){
                 
                 
                 ap = ap + califs[s][a][c];      //ap es la suma de las calificaciones de a
                 }       //promedio alumnos
         }       promedioAlumnos[s][a] =         //promedio salon
 }      ap/noCalifs[s][a];      //promedio escuela
