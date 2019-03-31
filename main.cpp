#include<iostream>
#include<omp.h>

using namespace std;

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

int main(){
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        int *filterArea = new int[8];
        //Starts with string ---> "     "
        //long gen = 0x2020202020;
        char *str = new char;

        #pragma omp for
        for(long gen = 0x2020202020; gen < 0xffffffffff; gen++){

            if(filter(&gen, filterArea)){
                for(int i = 4, j = 0; j < 5; i--, j++){
                    str[j] = (gen>>8*i)&0xff;
                }

                cout<<str<<endl;
            }

        //gen++;
        }
    }
}
