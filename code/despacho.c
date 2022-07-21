#include <stdio.h>

// cat teste.txt | ./lp_solve_5.5.2.11_exe_ux64/lp_solve
// exemplo de entrada

int main(void){

    // Variáveis
    int n;  // Quantidade de meses                     
    scanf("%d", &n);                                    
    int d[n];  // Demanda mensal                                         
    int y[n];  // Afluência mensal
    int v_ini, v_min, v_max; // v de volume
    int t_max;  // É a capacidade máxima de geração da termo  
    float k; // É a constante de geração da hidroelétrica a cada 1m³ 
    float CT;  // Custo de geração da termoelétrica  
    float CA;  // Custo ambiental

    // Lendo as entradas
    for (int i = 0; i < n; i++){                        
        scanf("%d", &d[i]);                             
    }                                                   
    for (int i = 0; i < n; i++){                        
        scanf("%d", &y[i]);                             
    }                                                   
    scanf("%d %d %d %F", &v_ini, &v_min, &v_max, &k);   
    scanf("%d %f", &t_max, &CT);                        
    scanf("%f", &CA);                                   

    // fazer o for do min
    printf("min : ");

    printf("%f * (", CT * k);
    for (int i = 0; i < n; i++) {
        printf("%f +", );
    }

    return 1;
}