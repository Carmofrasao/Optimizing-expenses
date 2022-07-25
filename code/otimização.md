<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>
<center><h1>Otimizando o gasto de uma empresa de energia</h1></center> 

<center><h2>Problema</h2></center>

A rede elétrica de uma cidade é abastecida por uma usina hidrelétrica e uma usina termoelétrica, que é usada apenas quando a hidrelétrica, que tem custo de geração nulo, não consegue atender à demanda. A termoelétrica tem um custo associado a cada MWatt gerado. 
Neste problema, você deve conceber um plano de geração mensal em um período de n meses que minimiza o custo total. Além do custo de geração termoelétrica, há o custo ambiental (convertido em R$) associado à variação do reservatório da hidrelétrica, para mais ou para menos, de um mâs para o seguinte. Os custos de geração de 1 MWatt pela termoelétrica (CT) e da variação de 1 m³ no reservatório (CA) são constantes dadas.


• O reservatório começa com um volume inicial de água (*v_ini*) e tem limites mínimo e máximo (constantes dadas) para o volume de água (m³) e que devem ser respeitados, respectivamente *v_min* e *v_max*.

• A cada mês, o reservatório recebe um volume de água (m³) proveniente de chuvas, afluências, etc. Essas informações foram estimadas para os n meses do planejamento e são constantes dadas, *y1*, *y2*, …, *yn*.

• A única forma do volume de água no reservatório diminuir é turbinando a água para gerar energia. A cada 1m³ de água turbinada, gera-se *k*MWatt de energia, em que *k* é uma constante dada.

• Há uma capacidade máxima de geração mensal da termelétrica, que é uma constante *t_max* dada.

• As demandas mensais da cidade (MWatt) também são constantes *d1*, *d2*, …, *dn* dadas e devem ser atendidas pela geração de energia da hidrelétrica e da termoelétrica. Gerar mais do que a demanda não é um problema (a energia restante vai para outra cidade, por exemplo).

<center><h6>- - -</h6></center>


<center><h2>Como foi modelado</h2></center>

A partir do entendimento dos autores; problemas de otimização, no geral, apresentam dois tipos de variáveis: qualitativas e quantitativas. As quantitativas referem-se às quantidades de recursos que temos, ao passo que as qualitativas indicam o peso das variáveis quantitativas, esse problema pode ser encarado da mesma forma se considerarmos:

#### Variáveis quantitativas

- *v_i*: Quantidade de água no reservatório no mês *i*.
- *y_i*: Quantidade de chuva no mês *i*.
- *var_i*: Variação do volume de água do reservatório no mês *i*.
- *TURBINADO_i*: Quantidade de água turbinada no mês *i*.
- *TERMO_i*: Quantidade de KWatts gerada pela termoelétrica no mês *i*.
- *v_min*: Quantidade mínima de volume do reservatório.
- *v_max*: Quantidade máxima de volume do reservatório.
- *v_ini*: Quantidade inicial de água no reservatório.
- *d_i*: Quantidade, em KWatts, de demanda de energia no mês *i*.
- *t_max*: Quantidade máxima de energia que a termo pode gerar, em KWatts.

#### Variáveis qualitativas

- *CT*: Custo da termoelétrica em por KWatt gerado.
- *CA*: Custa ambiental da variação de 1m³ de água no reservatório.
- *k*: Coeficiente da geração de KWatts a cada m³ de água turbinada pela hidroelétrica.

<center><h6>-</h6></center>

Com essas variáveis definidas podemos pensar em uma forma de relacionar cada qual através de equações e inequações que definirão o comportamento da otimização. Para tanto, é importante lembrar o que queremos otimizar, nossa _função objetiva_, nesse caso, é a **minimização** dos custos mensais de geração de energia ao longo de *n* meses.

Através das nossas variáveis podemos concluir algumas informações relevantes: o custo de produzir energia com a hidroelétrica se dá multiplicando a variação do reservatório de um mês para o outro com o custo ambiental de cada m³ de variação, isto é

$$
CA * var_i
$$

A variação pode ser expressa através da seguinte fórmula

$$
var_i = y_i - TURBINADO_i
$$

Ou seja, a variação é a quantidade de chuva (volume acrescentado ao reservatório) menos a quantidade de água turbinada em dado mês. Percebemos, também, que o volume de água do reservatório varia em função da variação, da seguinte forma

$$
v_i = v_{i-1} + var_i
$$

Podendo ser lida como volume de água atual é igual ao volume de água que sobrou mais a variação atual.

Agora, para a termoelétrica temos que o seguinte deve ocorrer; toda vez que a termo for ligada é porque a hidroelétrica não supriu a demanda energética do mês, e obrigatoriamente a hidro e a termo devem gerar pelo menos a demanda mínima, portanto

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

Porém, sempre que a termoelétrica gera 1 MWatt, temos um custo CT associado, então o custo em um mês da geração de energia pode ser expressa da seguinte forma

$$
custo = CA*|var_i| + CT*TERMO_i
$$

Logo, descobrimos o que queremos minimizar, generalizando para *n* meses temos, portanto, nossa função objetiva:

$$
min: CA\sum_{i=1}^{n}{|var_i|} + CT\sum_{i=1}^{n}{TERMO_i}
$$

É notável a presença de um módulo, afinal a variação do volume do reservatório, para menos ou para mais, é o que efetivamente implica em custo no fim do mês; módulos, contudo, são funções não lineares, e portanto precisamos substituir esse módulo por uma função linear que expresse exatamente o que o módulo expressa, para tanto, basta que quebremos a variação do mês em outras duas variáveis: acréscimo e descréscimo de volume.

$$
var_i = Acr_i - Decr_i
$$

O que implica em

$$
|var_i| = Acr_i + Decr_i
$$

Note também que

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

Portranto também temos

- *Acr_i*: Acréscimo de água do mês *i*.
- *Decr_i*: Decréscimo de água do mês *i*.

Com todas essas informações podemos, finalmente, descrever o problema completo com a função objetivo e nossas restrições.

$$
min: CA\sum_{i=1}^{n}{(Acr_i + Decr_i)} + CT\sum_{i=1}^{n}{TERMO_i}
$$

Sujeito a:

$$
v_0 = v_{ini}
$$

$$
v_i = v_{i-1} + var_i
$$

$$
var_i = y_i - TURBINADO_i
$$

$$
var_i = Acr_i - Decr_i
$$

$$
Acr_i - Decr_i = y_i - TURBINADO_i
$$

$$
k * TURBINADO_i + TERMO_i \ge d_i
$$

$$
TURBINADO_i \ge 0
$$

$$
TERMO_i \ge 0
$$

$$
TERMO_i \le t_{max}
$$

$$
v_i \ge v_{min}
$$

$$
v_i \le v_{max}
$$

$$
i \ge 1
$$

$$
i \le n
$$

$$
Acr_i,Decr_i \ge 0
$$

<center><h6>- - -</h6></center>

<center><h2>Implementação</h2></center>

A implementação trata-se de um código em C que simplesmente lê as entradas do teclado e gera um arquivo de saída pronto para ser passado para o *lp_solve*. 
Devido às restrições do *lp_solve*, o código expande os somatórios e os escreve por extenso, junto com as demais equações e inequações, em *stdout*. A leitura é realizada de acordo com a quantida de meses *n* e demais informações lidas a partir de *stdin*.

<center>- - -</center>

<br>
<br>
<center>Autores</center>

<h5>Anderson Aparecido do Carmo Frasão GRR20204069</h5>
<h5>Richard Fernando Heise Ferreira GRR20191053</h5>

