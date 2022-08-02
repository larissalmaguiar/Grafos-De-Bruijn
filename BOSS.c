/*
 * BOSS
 *
 * Authors: Larissa M. Aguiar and Felipe A. Louza
 * contact: louza@ufu.br
 * 11/07/2022
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <zlib.h>
#include "external/kseq.h"
#include "lib_boss.h"

KSEQ_INIT(gzFile, gzread);

int main(int argc, char *argv[])
{
    char **NODE = NULL;
    char **RAD = NULL;
    char *T = NULL;
    char *T_i = NULL;
    char *W = NULL;
    char *Wr = NULL;
    int *L = NULL;
    int *Lr = NULL;
    int *F = NULL;
    bool *W_minus = NULL;
    bool *Wr_minus = NULL;

    int c, comp = 0, pri = 0, k = 0, alg = 0, m, nn;
    extern char *optarg;
    while ((c = getopt(argc, argv, "K:kA:apc")) != -1)
    {
        switch (c)
        {
        case 'K':
            k = (int)atoi(optarg);
            break;
        case 'A':
            alg = (int)atoi(optarg);
            break;
        case 'p':
            pri = 1;
            break;
        case 'c':
            comp = 1;
            break;
        default:
            break;
        }
    }
    free(optarg);

    gzFile fp;
    kseq_t *seq;
    int l, n=0;
    fp = gzopen(argv[argc-1], "r"); // STEP 2: open the file handler
    seq = kseq_init(fp);       // STEP 3: initialize seq
    while ((l = kseq_read(seq)) >= 0)
    { // STEP 4: read sequence
        n+=seq->seq.l;
    }
	gzclose(fp);
    fp = gzopen(argv[argc-1], "r"); // STEP 2: open the file handler
    seq = kseq_init(fp); 
    T = (char *)malloc((n+2) * sizeof(char));
    while ((l = kseq_read(seq)) >= 0) strcat(T, seq->seq.s); 
    kseq_destroy(seq);
	gzclose(fp);
    T_i = (char *)malloc((n+2) * sizeof(char));
    T[n-1]='$';
    T[n]='\0';
    printf("Tamanho n: %d\n", n);
    reverse_T(T, T_i, n);
    int mm = n - k; //
    printf("Tamanho m: %d\n", mm);

    FILE *arq;

    if ((arq = fopen("resultados/T.txt", "w")) != NULL)
    {
            for (int i = 0; i < n; i++)
                fprintf(arq, "%c", T[i]);
    }
    if (alg == 1 || comp == 1)
    {
        NODE = (char **)malloc((mm + 1) * sizeof(char *));
        for (int i = 0; i <= mm; i++)NODE[i] = (char *)malloc((k + 2) * sizeof(char));
        m = boss_sort(mm, T_i, NODE, &L, &W, &W_minus, k, &F);

        printf("m = %d\n", m);

        if ((arq = fopen("resultados/W1.txt", "w")) != NULL)
        {
            for (int i = 0; i < m; i++)fprintf(arq, "%c", W[i]);
        }
        fclose(arq);
        if ((arq = fopen("resultados/W_minus1.txt", "w")) != NULL)
        {
            for (int i = 0; i < m; i++)
                fprintf(arq, "%d", W_minus[i]);
        }
        fclose(arq);
        if ((arq = fopen("resultados/last1.txt", "w")) != NULL)
        {
            for (int i = 0; i < m; i++)
                fprintf(arq, "%d", L[i]);
        }
        fclose(arq);
    }

    if (alg == 2 || comp == 1)
    {

        RAD = (char **)malloc((mm + 1) * sizeof(char *));
        for (int i = 0; i <= mm; i++) RAD[i] = (char *)malloc((k + 2) * sizeof(char));
        nn = boss_radix(mm, T_i, RAD, &Lr, &Wr, &Wr_minus, k, &F);

        printf("nn = %d\n", nn);
        if ((arq = fopen("resultados/W2.txt", "w")) != NULL)
        {
            for (int i = 0; i < nn; i++)
                fprintf(arq, "%c", Wr[i]);
        }
        fclose(arq);
        if ((arq = fopen("resultados/W_minus2.txt", "w")) != NULL)
        {
            for (int i = 0; i < nn; i++)
                fprintf(arq, "%d", Wr_minus[i]);
        }
        fclose(arq);
        if ((arq = fopen("resultados/last2.txt", "w")) != NULL)
        {
            for (int i = 0; i < nn; i++)
                fprintf(arq, "%d", Lr[i]);
        }
        fclose(arq);
    }

    if (pri == 1 && alg == 1)
    {
        printf("$:%d\nA:%d\nC:%d\nG:%d\nT:%d\n", F['$'], F['A'], F['C'], F['G'], F['T']);
        print_BOSS(NODE, L, W_minus, W, m, k);
    }
    else if (pri == 1 && alg == 2)
    {
        printf("$:%d\nA:%d\nC:%d\nG:%d\nT:%d\n", F['$'], F['A'], F['C'], F['G'], F['T']);
        print_BOSS(RAD, Lr, Wr_minus, Wr, nn, k);
    }
    if (comp == 1)
    {
        // if(alg==1) nn=boss_radix(mm, T_i,RAD, &Lr, &Wr, &Wr_minus, k, &Fr);
        if(alg==2)m=nn;
        if (compare_boss(NODE, RAD, m))
            printf("OS NÓS SÃO IGUAIS\n");
        else
            printf("OS NÓS SÃO DIFERENTE\n");
        if (compare_W(W, Wr, m))
            printf("OS VETORES W SÃO IGUAIS\n");
        else
            printf("OS VETORES W SÃO DIFERENTES\n");

        if (compare_Wminus(W_minus, Wr_minus, m))
            printf("OS VETORES W_MINUS SÃO IGUAIS\n");
        else
            printf("OS VETORES W_MINUS SÃO DIFERENTES\n");
        if (compare_L(L, Lr, m))
            printf("OS VETORES Last SÃO IGUAIS\n");
        else
            printf("OS VETORES Last SÃO DIFERENTES\n");
    }

    // LIBERAÇÃO DE MEMORIA

    free(T);
    free(T_i);
    free(F);
    free(L);
    if (alg == 1 || comp == 1)
    {

        free(W);
        free(W_minus);
        for (int i = 0; i < m; i++)
            free(NODE[i]);
        free(NODE);
    }
    if (alg == 2 || comp == 1)
    {
        free(Wr);
        free(Wr_minus);
        for (int i = 0; i < m; i++)
            free(RAD[i]);
        free(RAD);
    }
}