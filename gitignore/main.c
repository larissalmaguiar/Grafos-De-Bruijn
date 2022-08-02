#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "sacak-lcp.h"

void bwt(uint_t *SA, char *T, char *BWT, int n, char *F)
{
    for(int i=0; i<n; i++)
    {
        F[i]=T[SA[i]];
        if(SA[i]==0) BWT[i]='$';
        else BWT[i]=T[SA[i]-1];
    }
}
void c(int *C, char *BWT, int n, int *COUNT, char *F)
{
    for(int i=0; i<128; i++) C[i]=0;
    for(int i=0; i<n; i++) C[(int)BWT[i]]++;
    for(int i=0; i<n; )
    {
        int c=F[i];
        COUNT[c]=i;
        i=i+C[c];
    }
}
void lf(int *COUNT, char *BWT, int n, int *LF)
{
    for(int i=0; i<n; i++)
    {
    int c=BWT[i];
    LF[i]=COUNT[c];
    COUNT[c]++;
    }
}
void decoding(char *S, char *BWT, int *LF, int n)
{
   S[n-1]='$';
   int j=0;
   for(int i=n-2; i>=0; i--) 
   {
       S[i]=BWT[j];
       j=LF[j];
   }
   S[n]='\0';
}
int main(int argc, char *argv[])
{
    
    // DECLARAÇÃO DOS VETORES
    char *T=NULL; //original
    char *BWT = NULL; 
    char *F=NULL; //coluna de inicio 
    char *S=NULL; //decodificada
    uint_t *SA=NULL;
    int *C=NULL;  // conta as ocorrencias
    int *COUNT=NULL; //marca a primeira aparição do caracter 
    int *LF=NULL; //decodificador 
    //ENTRADA PROVISÓRIA
    FILE *ent;
    ent = fopen(argv[1], "r");
    fseek(ent, 0, SEEK_END);
    int n = ftell(ent);

    rewind(ent);

    T = (char *)malloc((n + 1) * sizeof(char));
    fgets(T, n, ent);
    T[n-1]='$';
    T[n] = '\0';
    printf("Text = %s$\n", T);

    //ATRIBUIÇÃO DE ESPAÇO
    SA = (uint_t *)malloc((n + 1) * sizeof(uint_t));
    BWT = (char*)malloc((n + 1) * sizeof(char));
    S = (char*)malloc((n + 1) * sizeof(char));
    F = (char*)malloc((n + 1) * sizeof(char));
    C = (int *)malloc((128) * sizeof(int));
    LF = (int *)malloc((n+1) * sizeof(int));
    COUNT = (int *)malloc((128) * sizeof(int));

    //CHAMADA DE FUNÇÕES 
    sacak((unsigned char *)T, (uint_t *)SA, n);
    bwt(SA, T, BWT, n, F);
    c(C,BWT,n,COUNT,F);
    lf(COUNT, BWT,  n, LF);
    for(int i=0; i<n; i++) printf("LF[%d]=%d\n", i, LF[i]);
    decoding(S,BWT, LF,  n);
    printf("BWT:\t%s\nDECODED:%s\n", BWT, S);
    
    //LIBERAÇÃO DE MEMÓRIA 
    free(T);
    free(SA);
    free(BWT);
    free(F);
    free(C);
    free(COUNT);
    free(S);
    free(LF);
    fclose(ent);
    return 0;
}