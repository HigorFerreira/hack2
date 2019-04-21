#include<iostream>
#include<unistd.h>
#include<stdio.h>
// #include <mpi.h>

using namespace std;

#define RANGE_START 0x20
#define RANGE_ENDDD 0X7E
#define DISPERTION "ab"

//Declaração do protótipo da função
// char *crypt(const char *, const char *);

string pass5(int start8, int start7, int start6, int start, string &compare){

    string shot = "";
    string shot6 = "";
    string shot7 = "";
    string shot8 = "";
    
    string cryptShot = "";
    string cryptShot6 = "";
    string cryptShot7 = "";
    string cryptShot8 = "";

    for(int c = start8; c < RANGE_ENDDD; c++){
        for(int b = start7; b < RANGE_ENDDD; b++){
            for(int a = start6; a < RANGE_ENDDD; a++){

                for(int i = start; i < RANGE_ENDDD; i++){
                    for(int j = RANGE_START; j < RANGE_ENDDD; j++){
                        for(int k = RANGE_START; k < RANGE_ENDDD; k++){
                            for(int l = RANGE_START; l < RANGE_ENDDD; l++){
                                for(int m = RANGE_START; m < RANGE_ENDDD; m++){
                                    //Shot 5 characters
                                    shot += i;
                                    shot += j;
                                    shot += k;
                                    shot += l;
                                    shot += m;

                                    //Shot 6 characters
                                    shot6 += a;
                                    shot6 += shot;

                                    //Shot 7 characters
                                    shot7 += b;
                                    shot7 += shot6;

                                    //Shot 8 characters
                                    shot8 += c;
                                    shot8 += shot7;

                                    cryptShot = crypt(shot.c_str(), DISPERTION);
                                    cryptShot6 = crypt(shot6.c_str(), DISPERTION);
                                    cryptShot7 = crypt(shot7.c_str(), DISPERTION);
                                    cryptShot8 = crypt(shot8.c_str(), DISPERTION);
                                    
                                    if(cryptShot == compare) return shot;
                                    if(cryptShot6 == compare) return shot6;
                                    if(cryptShot7 == compare) return shot7;
                                    if(cryptShot8 == compare) return shot8;

                                    // Cleanning shots
                                    shot = "";
                                    shot6 = "";
                                    shot7 = "";
                                    shot8 = "";
                                }
                            }
                        }
                    }
                }

            }
        }
    }
}

//ABSTRAÇÃO DE CÓDIGO PARA O PROCESSAMENTO EM PARALELO
int main(){
    string pass = crypt("     ana", DISPERTION);
    // string pass = "ANA";
    
    int size,rank;

    string adv = pass5(0x20, 0x20, 0x20, 0x20, pass);

    cout<<endl;
    cout<<"Senha: "<<adv<<endl;

    // MPI_Init();

    // MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// MPI_Comm_size(MPI_COMM_WORLD,&size);

    

    // MPI_Finalize(); 
}
