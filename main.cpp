#include<iostream>
#include<unistd.h>
#include<stdio.h>
// #include <mpi.h>

using namespace std;

#define RANGE_START 0x20
#define RANGE_ENDDD 0X7E

//Declaração do protótipo da função
// char *crypt(const char *, const char *);

string pass5(int start, int end, string &compare){

    string kicker = "";
    string cryptKick = "";

    for(int i = start; i < end; i++){
        for(int j = RANGE_START; j < RANGE_ENDDD; j++){
            for(int k = RANGE_START; k < RANGE_ENDDD; k++){
                for(int l = RANGE_START; l < RANGE_ENDDD; l++){
                    for(int m = RANGE_START; m < RANGE_ENDDD; m++){
                        kicker += i;
                        kicker += j;
                        kicker += k;
                        kicker += l;
                        kicker += m;

                        cout<<kicker<<endl;

                        cryptKick = crypt(kicker.c_str(), "ab");
                        
                        if(cryptKick == compare) return kicker;

                        // Cleanning kicker
                        kicker = "";
                    }
                }
            }
        }
    }
}

//ABSTRAÇÃO DE CÓDIGO PARA O PROCESSAMENTO EM PARALELO
int main(){
    string pass = crypt("  Gac", "ab");
    // string pass = "ANA";
    
    int size,rank;

    cout<<endl<<"Senha: "<<pass5(0x20, 0x21, pass)<<endl;

    // MPI_Init();

    // MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// MPI_Comm_size(MPI_COMM_WORLD,&size);

    

    // MPI_Finalize(); 
}
