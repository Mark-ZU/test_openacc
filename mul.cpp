#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>

const int N = 500;

void matrix_multiply (float r[N][N], const float a[N][N], const float b[N][N]){
    #pragma acc data copyin(a[0:N][0:N], b[0:N][0:N]) copyout(r[0:N][0:N])
    {
        #pragma acc kernels loop gang, vector(8) independent
        for (int j = 0; j < N; j++){
            #pragma acc loop independent
            for (int i = 0; i < N; i++){
                float sum = 0;
                // #pragma acc loop reduction(+:sum)
                #pragma acc loop seq
                for (int k = 0; k < N ; k++)
                    sum += a[i][k] * b[k][j];
                r[i][j] = sum;
            }
        }
    }
}

float r[N][N],a[N][N],b[N][N];

int main(){
    std::srand(static_cast <unsigned> (std::time(0)));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            a[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            b[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    matrix_multiply(r,a,b);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}