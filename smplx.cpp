#include <stdio.h>
#include <math.h>

#define CMAX  10  //max. number of variables in function
#define VMAX  10  //max. number of constraints

 //NC: number of constraints
 //NV: number of varibale 
 //NOPTIMAL: boolean if false continue the iteration
 //P1: row number of pivot
 //P2: column number of pivot
 //TS: array/table of size NC+1 * NV+1 
  
  int NC, NV, NOPTIMAL,P1,P2,XERR;
  double TS[CMAX][VMAX];

  void Data() {
    //R1: 1 for MAXIMIZE problem
    //    -1 for MINIMIZE problem 
    //R2: for inputing coefficient of varibales in Z  
    double R1,R2;
    // Y for MAXIMIZE
    // N for MINIMIZE
    char R;
    int I,J;
    printf("\n Simplex Method...\n\n");
    printf(" MAXIMIZE (Y/N) ? "); scanf("%c", &R);
    printf("\n NUMBER OF VARIABLES in Z: "); scanf("%d", &NV);
    printf("\n NUMBER OF CONSTRAINTS:  "); scanf("%d", &NC);
    if (R == 'Y' || R=='y')
      R1 = 1.0;
    else
      R1 = -1.0;
    printf("\n INPUT COEFFICIENTS OF X(i)th VARIABLE in Z :\n");
    for (J = 1; J<=NV; J++) {
      printf("       #%d ? ", J); scanf("%lf", &R2);
      TS[1][J+1] = R2 * R1;
    }
    printf("       RHS:  "); scanf("%lf", &R2);
    TS[1][1] = R2 * R1;
    for (I = 1; I<=NC; I++) {
      printf("\n CONSTRAINT #%d:\n", I);
      for (J = 1; J<=NV; J++) {
        printf("       #%d ? ", J); scanf("%lf", &R2);
        TS[I + 1][J + 1] = -R2;
      }
      printf("       RHS: "); scanf("%lf", &TS[I+1][1]);
    }
    printf("\n\n WHERE:\n\n");
    for(J=1; J<=NV; J++)  TS[0][J+1] = J;
    for(I=NV+1; I<=NV+NC; I++)  TS[I-NV+1][0] = I;
  }
  //function to find PIVOT 
  void Pivot();
  //function for storing the row9P1) and the column(P2) number of pivot 
  void Formula();
  //function 
  void Optimize();

  void Simplex() {
    //till NOPTIMAL is 'false' continue the iteration 
    //e10: 10 iteration
e10: Pivot();
     Formula();
     Optimize();
     if (NOPTIMAL == 1) goto e10;
  }
  //find pivot by searching least element row and column 
  void Pivot() {

    //RAP: hold least ration
    //XMAX: hold greatest coefficient in function
    double RAP,V,XMAX;
    int I,J;

    XMAX = 0.0;
    for(J=2; J<=NV+1; J++) {
	if (TS[1][J] > 0.0 && TS[1][J] > XMAX) {
        XMAX = TS[1][J];
        P2 = J;
      }
    }
    RAP = 999999.0;
    for (I=2; I<=NC+1; I++) {
      if (TS[I][P2] >= 0.0) goto e10;
      V = fabs(TS[I][1] / TS[I][P2]);
      if (V < RAP) {
        RAP = V;
        P1 = I;
      }
e10:;}
    V = TS[0][P2]; TS[0][P2] = TS[P1][0]; TS[P1][0] = V;
  }
  //store the row number and the column number where the pivot is there
  void Formula() {;
    //Labels: e60,e70,e100,e110;
    int I,J;

    for (I=1; I<=NC+1; I++) {
      if (I == P1) goto e70;
      for (J=1; J<=NV+1; J++) {
        if (J == P2) goto e60;
        TS[I][J] -= TS[P1][J] * TS[I][P2] / TS[P1][P2];
e60:;}
e70:;}
    TS[P1][P2] = 1.0 / TS[P1][P2];
    for (J=1; J<=NV+1; J++) {
      if (J == P2) goto e100;
      TS[P1][J] *= fabs(TS[P1][P2]);
e100:;}
    for (I=1; I<=NC+1; I++) {
      if (I == P1) goto e110;
      TS[I][P2] *= TS[P1][P2];
e110:;}
  }   
 //if there is the solution of function then find its optimal solution doing
 //numbers of iteration if it is not then terminate by saying 'no solution'
  void Optimize() {
    int I,J;
    for (I=2; I<=NC+1; I++)
      if (TS[I][1] < 0.0)  XERR = 1;
    NOPTIMAL = 0;//false boolean value for continuing iterations
    if (XERR == 1)  return; //XERR if true there is no solution
    for (J=2; J<=NV+1; J++)
      if (TS[1][J] > 0.0)  NOPTIMAL = 1;//true boolean value for terminating iteration
  }
  //till will not get optimal solution do iteration and then print it 
  void Results() {
    //Labels: e30,e70,e100;
    int I,J;
    
    if (XERR == 0) goto e30;
    printf(" NO SOLUTION.\n"); goto e100;
e30:for (I=1; I<=NV; I++)
    for (J=2; J<=NC+1; J++) {
      if (TS[J][0] != 1.0*I) goto e70;
      printf("       X%d: %f\n", I, TS[J][1]);
e70:  ;}
    printf("\n       OPTIMAL SOLUTION: %f\n", TS[1][1]);
e100:printf("\n");
  }

int main()  {
  //calling all the functions in main
  Data();
  Simplex();
  Results();
  return 0;

}