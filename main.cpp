#include <iostream>

using namespace std;

void row_div(double *matrix,
			 int size)
{
	double div=0;
	for(int j=0; j<2*size; j++){
		if(div==0){
			if(*(matrix+j)!=0){
				div=*(matrix+j);
			}
		}
		if(div!=0){
			*(matrix+j)=*(matrix+j)/div;
		}
	}
}

void row_sub(double *matrix,
			 int size,
			 int row1,
			 int row2,
			 double mult)
{
	for(int j=0; j<2*size; j++){
		*(matrix+2*size*row1+j)-=*(matrix+2*size*row2+j)*mult;
	}
}

int main()
{
	const int size=6;
	double matrix[size][size];
	double aug_matrix[size][2*size];
	double inv_matrix[size][size];

	matrix[0][0]=8;  matrix[0][1]=-5; matrix[0][2]=10;  matrix[0][3]=0;   matrix[0][4]=-7; matrix[0][5]=5;
	matrix[1][0]=5;  matrix[1][1]=-9; matrix[1][2]=-10; matrix[1][3]=5;   matrix[1][4]=-2; matrix[1][5]=9;
	matrix[2][0]=9;  matrix[2][1]=1;  matrix[2][2]=6;   matrix[2][3]=-9;  matrix[2][4]=7;  matrix[2][5]=0;
	matrix[3][0]=-8; matrix[3][1]=-2; matrix[3][2]=-6;  matrix[3][3]=-10; matrix[3][4]=-2; matrix[3][5]=2;
	matrix[4][0]=-8; matrix[4][1]=-5; matrix[4][2]=-1;  matrix[4][3]=0;   matrix[4][4]=5;  matrix[4][5]=-1;
	matrix[5][0]=1;  matrix[5][1]=-9; matrix[5][2]=0;   matrix[5][3]=-9;  matrix[5][4]=-4; matrix[5][5]=2;

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			aug_matrix[i][j]=matrix[i][j];
			if(i==j){
				aug_matrix[i][j+size]=1;
			}
			else{
				aug_matrix[i][j+size]=0;
			}
		}
	}

	for(int k=0; k<size; k++){
		row_div(&aug_matrix[k][0], size);
		for(int i=k+1; i<size; i++){
			row_sub(&aug_matrix[0][0], size, i, k, aug_matrix[i][k]);
		}
	}

	for(int k=1; k<size; k++){
		for(int i=0; i<k; i++){
			row_sub(&aug_matrix[0][0], size, i, k, aug_matrix[i][k]);
		}
	}

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			inv_matrix[i][j]=aug_matrix[i][j+size];
		}
	}

	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout.width(12); cout<<inv_matrix[i][j];
		}
		cout<<endl;
	}
	return 0;
}
