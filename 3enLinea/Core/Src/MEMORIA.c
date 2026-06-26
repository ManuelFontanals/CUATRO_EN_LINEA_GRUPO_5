#include "LEDS.h"

void llenarmemoria(char M[8][4], char Teclado_Accionado, char jugada){
	volatile uint32_t j0 = 7;
	volatile uint32_t j1 = 7;
	volatile uint32_t j2 = 7;
	volatile uint32_t j3 = 7;
	switch (Teclado_Accionado){
	case 0:{ if (j0<7 || M[0][j0]==0){
				M[0][j0]=1;
				j0--;
				jugada= 1;
	}
			else
				jugada = 2;
	break;
			}
	case 1:{ if (j1<7 || M[0][j0]==0){
			    M[1][j1]=1;
			    j1--;
			    jugada= 1;
}
			else
				jugada = 2;
	break;
	}
	case 2:{ if (j2<7 || M[0][j0]==0){
				M[2][j2]=1;
				j2--;
				jugada= 1;
}
			else
				jugada = 2;
	break;
}
	case 3:{ if (j3<7 || M[0][j0]==0){
				M[3][j3]=1;
				j3--;
				jugada= 1;
}
			else
				jugada = 2;
	break;
}
}
}

void detectarvictoria(char M[8][4], char ganaj1, char ganaj2){
	for (int i=0;i<=0;i++)
		for (int j=7;j>=0;j--)
			if (M[i][j] ==1 || M[i][j]==2){
				if (i+2<=3 && M[i+2][j]==1 && M[i+1][j]==1){
					ganaj1=1;}
				else if (i+2<=3 && M[i+2][j]==2 && M[i+1][j]==2){
					ganaj2=1;}

				if (j-2>=0 && M[i][j-2]==1 && M[i][j-1]==1){
					ganaj1=1;}
				else if (j-2>=0 && M[i][j-2]==2 && M[i][j-1]==2){
					ganaj2=1;
							}
				if (i+2<=3 && j-2>=0 && M[i+2][j-2]==1 && M[i+1][j-1]==1){
					ganaj1=1;}
				else if (i+2<=3 && j-2>=0 && M[i+2][j-2]==2 && M[i+1][j-1]==2){
					ganaj2=1;
							}
				if (i+2<=3 && j<=0 && j+2<=7 && M[i+2][j+2]==1 && M[i+1][j+1]==1){
					ganaj1=1;}
				else if (i+2<=3 && j>=0 && M[i+2][j+2]==2 && M[i+1][j+1]==2){
					ganaj2=1;}
}
}
