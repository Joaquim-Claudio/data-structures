![Tests](https://github.com/IADE-PA/sort-algorithms/workflows/Tests/badge.svg)

# IADE/UE - Programação e Algoritmos  <!-- omit in toc -->

## Coleção de algoritmos de ordenação <!-- omit in toc -->

- [Contrato](#contrato)
- [Implementações](#implementações)
- [Testes](#testes)
- [Makefile](#makefile)
  - [Cobertura de testes](#cobertura-de-testes)

## Contrato

Um algoritmo de ordenação é definido pelo seguinte contrato, em [`src/sort.h`](src/sort.h):

```C
void sort(comparable collection[], const int size, int (*compare)(comparable, comparable));
```

Onde `comparable` representa um tipo de dados comparável, i.e., que permite estabelecer relações de igualdade (`== < <= > >=`).

```C
typedef void* comparable;
```

As implementações sobre arrays de inteiros seguem o contrato em [`src/sort_int.h`](src/sort_int.h):

```C
void sort(int collection[], const int size);
```

## Implementações

- [BubbleSort para arrays de inteiros](src/bubblesort_int.c)
- [BubbleSort genérico](src/bubblesort_generic.c)
- [QuickSort para arrays de inteiros](src/quicksort_int.c)
- [QuickSort genérico](src/quicksort_generic.c)

## Testes

As duas abordagens (inteiros e genérico) estão testadas recorrendo a testes unitários em [Unity](https://github.com/ThrowTheSwitch/Unity).

- [Testes para arrays de inteiros](tests/test_int.c)
- [Testes para arrays genéricos](tests/test_generic.c)

## Makefile

A compilação pode ser feita com o comando:

```bash
make
```

O resultado compilado é gerado para o diretório `bin` (o make cria o diretório se não existir). É equivalente a:

```bash
gcc -c src/bubblesort_int.c -o bin/bubblesort_int.o
gcc -c tests/unity/unity.c -o tests/bin/unity.o
gcc -c src/bubblesort_generic.c -o bin/bubblesort_generic.o
gcc -c src/quicksort_int.c -o bin/quicksort_int.o
gcc -c src/quicksort_generic.c -o bin/quicksort_generic.o
```

O Makefile inclui as seguintes flags de compilação:

- `-g`: gera código de depuração
- `-Wall`: mostra todos os warnings
- `-Wextra`: mostra warnings extras
- `-Werror`: mostra warnings como erros

Sâo também gerados os programas executáveis para os testes unitários, para o diretório `tests/bin` (o make cria o diretório se não existir):

```bash
gcc tests/test_generic.c bin/bubblesort_generic.o tests/bin/unity.o -o tests/bin/test_bubblesort_generic
gcc tests/test_int.c bin/quicksort_int.o tests/bin/unity.o -o tests/bin/test_quicksort_int
gcc tests/test_int.c bin/bubblesort_int.o tests/bin/unity.o -o tests/bin/test_bubblesort_int
gcc tests/test_generic.c bin/quicksort_generic.o tests/bin/unity.o -o tests/bin/test_quicksort_generic
```

Para gerar todo o código compilado e executar os testes fazer:

```bash
make tests
```

Para apagar todos os ficheiros compilados fazer:

```bash
make clean
```

### Cobertura de testes

A avaliação da cobertura é feita através do [GNU Coverage Toolkit (GCC) - `gcov`](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html). Para funcionar, o código deve ser compilado com as seguintes flags (além das já utilizadas):

```bash
-fprofile-arcs -ftest-coverage
```

Por exemplo, para a implementação do BubbleSort num array de inteiros, a linha de compilação vai ser:

```bash
gcc -c -g -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage src/bubblesort_int.c -o bin/bubblesort_int.o
```

O programa vai gerar estruturas para coleção de estatísticas de cobertura no ficheiro `bin/test_bubblesort_int.gcno`.

Ao executar um teste, ou um programa que utilize `bubblesort_int.o`, o GCC vai colecionar estatísticas de cobertura o ficheiro `bin/test_bubblesort_int.gcda`.

Para interpretar o resultado, é necessário executar o `gcov`, com acesso ao código fonte, e aos ficheiros previamente gerados:

```bash
gcov src/bubblesort_int.c -o bin
```

Vai ser gerado um ficheiro `src/bubblesort_int.c.gcov` com as linhas docódigo fonte anotadas com a quantidade de vezes que foram executadas. Desta forma é possível identificar linhas de código que não são *cobertas* pelos testes.

Existe uma ferramenta que permite obter a coleção de todas as estatísticas recolhidas num determinado diretório - a [gcovr](https://gcovr.com/).

```bash
gcovr .
```

Para compilar todos os algoritmos, executar os testes, e obter a tabela de cobertura, fazer:

```bash
make cov
```

A tabela final deve ser idêntica a:

```bash
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ./src
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
bubblesort_generic.c                           8       8   100%   
bubblesort_int.c                               8       8   100%   
quicksort_generic.c                           25      25   100%   
quicksort_int.c                               25      25   100%   
------------------------------------------------------------------------------
TOTAL                                         66      66   100%
------------------------------------------------------------------------------
```