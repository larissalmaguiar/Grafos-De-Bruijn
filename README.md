# Grafos-De-Bruijn

## Build requirements

An ANSI C Compiler (e.g. GNU GCC)
## Example

**Compilation:**

```sh
make
```
**Run a test:**

```c
./BOSS dataset/reads.fastq -K 3 -A 2 -p -c
```

**Output:**

```c
T[1,n]: ATTGGGCACAGA$
i	L	NODE  W W-
0	1	ACA   G 1
1	1	GCA   C 1
2	1	AGA   $ 1
3	1	CAC   A 1
4	1	GGC   A 1
5	1	CAG   A 1
6	1	GGG   C 1
7	1	TGG   G 1
8	1	TTG   G 1
9	1	$TT   G 1
OS NÓS SÃO IGUAIS
OS VETORES W SÃO IGUAIS
OS VETORES W_MINUS SÃO IGUAIS
OS VETORES L SÃO IGUAIS


```


