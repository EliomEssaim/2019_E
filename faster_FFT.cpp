#include <cstdio>
#include <cmath>
#include <complex>
#include <iostream>

using namespace std;

const int N = 1000005;

typedef complex <double> cp;

// void init(){
//     const double PI = acos(-1);
//     for(int i = 0; i < n; i++){
//         omg[i] = cp(cos(2 * PI * i / n), sin(2 * PI * i / n));
//         inv[i] = conj(omg[i]);
//     }
// }
    cp omg[N], inv[N];
    cp temp[N];

void fft(cp *data, int size){
    const double PI = acos(-1);
    static int old_size=0;
    if(old_size != size)
        for(int i = 0; i < size; i++){
            omg[i] = cp(cos(2 * PI * i / size), sin(2 * PI * i / size));
            inv[i] = conj(omg[i]);
        }
    old_size = size;
    int lim = 0;
    // lim*2 < n
    while((1 << lim) < size) lim++;
    for(int i = 0; i < size; i++){
        int t = 0;
        for(int j = 0; j < lim; j++)
            if((i >> j) & 1) t |= (1 << (lim - j - 1));
        if(i < t) swap(data[i], data[t]); // i < t limit swap twice.
    }
    for(int l = 2; l <= size; l *= 2){
        int m = l / 2;
    for(cp *p = data; p != data + size; p += l)
        for(int i = 0; i < m; i++){
            cp t = omg[size / l * i] * p[i + m];
            p[i + m] = p[i] - t;
            p[i] += t;
        }
    }
}

int main(){
    // input_size must = 2^n
      
    int n = 1;
    int data[8]={1,2,1,2,1,2,0,0};
    while(n < 8) n *= 2;

    for(int i = 0; i < 6; i++)
        temp[i].real(data[i]);
    // init();

    fft(temp, n);
    for(int i = 0; i < 8; i++)
        std::cout<<temp[i];


    return 0;
}


