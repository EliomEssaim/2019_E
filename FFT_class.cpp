#include <cstring>
#include <complex>

typedef complex <double> cp;

class FFT
{
    public:
        const int N = 1000005;
        cp data[N], omg[N], inv[N];
        void init(){
            const double PI = acos(-1);
            for(int i = 0; i < n; i++){
                omg[i] = cp(cos(2 * PI * i / n), sin(2 * PI * i / n));
                inv[i] = conj(omg[i]);
            }
        }
        void fft(cp *data, int n){
            int lim = 0;
            while((1 << lim) < n) lim++;
            for(int i = 0; i < n; i++){
                int t = 0;
                for(int j = 0; j < lim; j++)
                    if((i >> j) & 1) t |= (1 << (lim - j - 1));
                if(i < t) swap(data[i], data[t]); // i < t limit swap twice.
            }
            for(int l = 2; l <= n; l *= 2){
                int m = l / 2;
            for(cp *p = data; p != data + n; p += l)
                for(int i = 0; i < m; i++){
                    cp t = omg[n / l * i] * p[i + m];
                    p[i + m] = p[i] - t;
                    p[i] += t;
                }
            }
        }

};

#include <iostream>

int main(){
    
    int data[8]={1,2,1,2,1,2,1,2};
    cp temp[8];
    for(int i = 0; i < 8; i++)
        temp[i].real(data[i]);
    FFT test;
    test.init();
    test.fft(data, 4);

    using namespace std;    
    for(int j = 0; j < 8; j++)
        std::cout<<temp[j];

    return 0;
}