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

    printf("/*função objetivo:*/\n");
    printf("min : ");

    for (int i = 1; i <= n; i++) {
        printf("CA Ci_%d + CA Cd_%d + ", i, i);
    }
    for (int i = 1; i <= n; i++) {
        if(i != n)
            printf("CT gera_t_%d + ", i);
        else
            printf("CT gera_t_%d;\n", i);
    }
    printf("/*sujeito a:*/\n");
    printf("/*Constantes:*/\n");
    printf("CT = %f;\n", CT);
    printf("CA = %f;\n", CA);
    printf("v_max = %d;\n", v_max);
    printf("v_min = %d;\n", v_min);
    printf("v_ini = %d;\n", v_ini);
    for(int i = 1; i <= n; i++){
        printf("d_%d = %d;\n", i, d[i-1]);
    }
    printf("k = %f;\n", k);
    for(int i = 1; i <= n; i++){
        printf("y_%d = %d;\n", i, y[i-1]);
    }
    printf("t_max = %d;\n", t_max);
    printf("/*Inequações:*/\n");
    for(int i = 1; i <= n; i++){
        printf("k gera_h_%d + gera_t_%d >= d_%d;\n", i, i, i);
    }
    for (int i = 1; i <= n; i++){
        printf("gera_h_%d >= 0;\n", i);
    }
    for (int i = 1; i <= n; i++){
        printf("gera_t_%d >= 0;\n", i);
    }
    for (int i = 1; i <= n; i++){
        printf("gera_t_%d <= t_max;\n", i);
    }
    printf("v_0 = v_ini;\n");
    for (int i = 1; i <= n; i++){
        printf("v_%d = v_%d + C_%d;\n", i, i-1, i);
    }
    for (int i = 1; i <= n; i++){
        printf("v_%d >= v_min;\n", i);
    }
    for (int i = 1; i <= n; i++){
        printf("v_%d <= v_max;\n", i);
    }
    // trecho duvidoso
    for (int i = 1; i <= n; i++){
        printf("Ci_%d - Cd_%d = y_%d - gera_h_%d;\n", i, i, i, i);
    }
    for (int i = 1; i <= n; i++){
        printf("C_%d = Ci_%d - Cd_%d;\n", i, i, i);
    }
    for (int i = 1; i <= n; i++){
        // for mais duvidoso ainda, em "C_%d" era para ser "|C_%d|", 
        // mas como representa ||?
        printf("C_%d = Ci_%d + Cd_%d;\n", i, i, i);
    }
    for (int i = 1; i <= n; i++){
        printf("Ci_%d >= 0;\n", i);
    }
    for (int i = 1; i <= n; i++){
        printf("Cd_%d >= 0;\n", i);
    }
    
    return 1;
}