# Otimizando o gasto de uma empresa de energia

Trabalho 1 da matéria de Otimização, do curso de Ciencia da Computação, da Universidade Federal do Paraná.

Feito por Anderson Frasão e Richard Heise

Objetivo

Modelar um problema de Otimização

Implementação

  A implementação trata-se de um código em C que simplesmente lê as entradas do teclado
e gera um arquivo de saı́da pronto para ser passado para o lp solve. Devido às restrições do
lp solve, o código expande os somatórios e os escreve por extenso, junto com as demais
equações e inequações, em stdout. A leitura é realizada de acordo com a quantida de
meses n e demais informações lidas a partir de stdin.

Execução

Compile com
> make

Rode com
> ./despacho < exemplo.txt | ./lp_solve_5.5.2.11_exe_ux64/lp_solve
