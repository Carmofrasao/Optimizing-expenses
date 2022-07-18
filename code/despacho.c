#include <stdio.h>

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
    printf("min : ", );

    printf("x_1 > 0;");
    printf("x_2 - x_3 > 0;");
    printf("x_4 >= 0;");
    printf("x_5 >= 0;");
    printf("x_6 >= 0;");
    printf("x_7 >= 0;");
    printf("x_8 >= 0;");
    printf("x_9 >= 0;");
    printf("x_10 >= 0;");

    return 1;
}