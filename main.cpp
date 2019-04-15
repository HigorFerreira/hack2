#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include <mpi.h>
//#include<crypt.h>

using namespace std;

//Declaração do protótipo da função
//char *crypt(const char *, const char *);

bool filter(long *gen, int *chars){
    chars[0] = (*gen & (long)0xff);
    chars[1] = (*gen & (long)0xff00)>>8;
    chars[2] = (*gen & (long)0xff0000)>>8*2;
    chars[3] = (*gen & (long)0xff000000)>>8*3;
    chars[4] = (*gen & (long)0xff00000000)>>8*4;

    for(int i = 0; i < 5; i++){
        if(chars[i] > -1 && chars[i] < 0x20)
            return false;

        if(chars[i] > 0x7e)
            return false;
    }

    return true;
}

bool equals(char *hash, char *str){
    char *encripted = crypt((const char *)str, "ab");
    return (*hash == *encripted);
}

//ABSTRAÇÃO DE CÓDIGO PARA O PROCESSAMENTO EM PARALELO
int main(){
    char *senha = crypt("ana123", "ab");

    int *filterArea = new int[8];
    char *str = new char;

    char *a = "ana124";

    cout<<senha<<endl;
    cout<<a<<endl;
    cout<<equals(senha, a)<<endl;

    int size,rank;

    MPI_Init();

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

    //HACK PARA SENHAS DE 5 CARACTERES
    /*
     * Nó de processamento 1
     * Para strings geradas com bits de alta ordem em 00
     */
    for(long gen = 0x2020202020; gen < 0x3fffffffff; gen++){

        if(filter(&gen, filterArea)){
            for(int i = 4, j = 0; j < 5; i--, j++){
                str[j] = (gen>>8*i)&0xff;
            }

            // if(equals(senha, str)){
            //     break;
            // }
        }
    }

    //goto fim;

    /*
     * Nó de processamento 2
     * Para strings geradas com bits de alta ordem em 01
     */
    for(long gen = 0x4020202020; gen < 0x7fffffffff; gen++){

        if(filter(&gen, filterArea)){
            for(int i = 4, j = 0; j < 5; i--, j++){
                str[j] = (gen>>8*i)&0xff;
            }

            // if(equals(senha, str)){
            //     break;
            // }
        }
    }

    /*
     * Nó de processamento 3
     * Para strings geradas com bits de alta ordem em 10
     */
    for(long gen = 0x8020202020; gen < 0xbfffffffff; gen++){

        if(filter(&gen, filterArea)){
            for(int i = 4, j = 0; j < 5; i--, j++){
                str[j] = (gen>>8*i)&0xff;
            }

            // if(equals(senha, str)){
            //     break;
            // }
        }
    }

    /*
     * Nó de processamento 4
     * Para strings geradas com bits de alta ordem em 11
     */
    for(long gen = 0xc020202020; gen < 0xffffffffff; gen++){

        if(filter(&gen, filterArea)){
            for(int i = 4, j = 0; j < 5; i--, j++){
                str[j] = (gen>>8*i)&0xff;
            }

            // if(equals(senha, str)){
            //     break;
            // }
        }
    }

    MPI_Finalize(); 
}
