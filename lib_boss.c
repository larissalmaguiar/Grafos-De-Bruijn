#include"lib_boss.h"

void node(int m, char *T, char **NODE, int k)
{
    int i;
    for(i=0; i<m-1; i++)
    {   
        strncpy(NODE[i], T+i, k+1);
        NODE[i][k+1]='\0';
    }
    strncpy(NODE[m-1], T+(m-1), k);
    NODE[m-1][k]='$';
    NODE[i][k+1]='\0';
}
int compare (const void *a, const void *b)
{
    if(strcmp(* (char * const *) a+1, * (char * const *) b+1)==0)
        return(strcmp (* (char * const *) a, * (char * const *) b));
    else 
        return (strcmp (* (char * const *) a+1, * (char * const *) b+1));
}
void radix(char **NODE, int k, int n)
{
    int count [256];
    char **aux=NULL; 
    aux = (char**)malloc((n+1)* sizeof(char*));
    for(int i = 0; i <=n ; i++)  aux[i] =(char*) malloc((k+2) * sizeof(char));
    for(int j=k+1; j>0;j--)
    {
        for (int i=0; i<256; i++) count[i]=0;
        for (int i=0; i<n; i++) count[(int)NODE[i][j]+1]++;
        for (int i=0; i<255; i++) count[i+1]+=count[i];
    
        for (int i=0; i<n; i++)
        {
            strcpy(aux[count[(int)NODE[i][j]]], NODE[i]);
            aux[count[(int)NODE[i][j]]][k+1]='\0';
            count[(int)NODE[i][j]]++;
        }
        for (int i=0; i<n; i++) strcpy(NODE[i], aux[i]);
    }
    for(int i = 0; i <=n; i++) free(aux[i]);
    free(aux);
}
void radix_one(char *NODE, int n)
{
    int count [256];
    char *aux=NULL; 
    aux = (char*)malloc((n+1)* sizeof(char));
    for(int i=0; i<256; i++) count[i]=0;
    for (int i=0; i<n; i++) count[(int)NODE[i]+1]++;
    for (int i=0; i<255; i++) count[i+1]+=count[i];  
    for (int i=0; i<n; i++)
    {
        aux[count[(int)NODE[i]]]=NODE[i];
        count[(int)NODE[i]]++;
    }
    for (int i=0; i<n; i++) NODE[i]=aux[i];
    free(aux);
}
void l(int *L, int m, char **NODE, int k)
{
    for(int i=0;i<m-1; i++)
    { 
        int j=1;
        while(NODE[i][j]==NODE[i+1][j] && j<=k)
        {
            j++;
            if(NODE[i][j]!=NODE[i+1][j])
            {
                j--;
                break;
            }
            if(j==k+1) 
            {
                j--;
                break;
            }
        }
        if(j==k) L[i]=0;
        else L[i]=1;
    }
    L[m-1]=1;
}
void w(char *W, int m, char **NODE)
{
    for(int i=0; i<m; i++) W[i]=NODE[i][0];
}

void wr(char *W, int n, char **NODE, int k, int *L)
{
    int m=0, i;
    char *aux=NULL; 
    aux = (char*)malloc((n)* sizeof(char));
    //m é a variavel que anda pelos nós
    //i anda pelos blocos de nós iguais 
    //l guarda a quantidade de 0 no bloco em aux 
    while(m<n)
    {
        
        int l=0;
        i=m;
        if(L[m]==1)
        {
            W[m]=NODE[m][0];
            m++;

        }
        else
        {
            while (L[i]==0)
            {
                aux[l]=NODE[i][0];
                l++;
                i++;
            }
            aux[l]=NODE[i][0];
            radix_one(aux, l+1);
            for(int t=0; t<=l; t++)
            {
                NODE[m][0]=aux[t];
                W[m]=aux[t];
                m++;
            }
        }
    }
    free(aux);
}

void w_minus(bool *W_minus, char **NODE, int m, int k, char *W)
{
    int i, j, t, x;
    int marc[256];
    for(i=0; i<256; i++) marc[i]=0;
    for(i=0; i<m; i++)W_minus[i]=1;

    i=0;
    while(i<m-1)
    {
        marc[(int)W[i]]++;
        t=i+1;
        if(t>=m) break; 
        x=0;
        while (strncmp(NODE[i], NODE[t], k-1)==0)
        {
            if(marc[(int)W[t]]==0) marc[(int)W[t]]++;
            else W_minus[t]=0;
            t++;
            if(t>=m) break; 
            x=1;
        }
        marc[(int)W[i]]=0;
        i=t;
        if(i>m-1) break;
        if(x==1) for(j=0; j<256; j++) marc[j]=0;
       
    }
}
void first(char **NODE, int m, int *F)
{
    int *cont=NULL, i=0;
    cont=(int *)malloc((256) * sizeof(int));
    for(int i=0; i<256; i++) cont[i]=0;
    for(int i=0; i<m; i++) cont[(int)NODE[i][1]]++;
    while(i<m)
    {
        F[(int)NODE[i][1]]=i;
        i=i+cont[(int)NODE[i][1]];
    }
}
void pass_node(char **NODE, int k, int m)
{
    for(int i=0; i<m; i++)
    {
        for(int j=1; j<k+1; j++)
        {
            NODE[i][j-1]=NODE[i][j];
        }
        NODE[i][k]='\0';
    }
}
int new_noder(char **NODE, int k, char **NNODE, int n, int *L, char *W)
{
    int j=0; 
    for(int i=0; i<n; i++)
    {
        if(strncmp(NODE[i], NODE[i+1], k+1)!=0)
        {
            strcpy(NNODE[j], NODE[i]);
            W[j]=NODE[i][0];
            L[j]=L[i];
            j++;
            if(i+1==n-1)
            {
              strcpy(NNODE[j], NODE[i+1]);
              W[j]=NODE[i+1][0];
              L[j]=L[i+1];
            }
        }
    }
    return j; 
}

int new_node(char **NODE, int k, char **NNODE, int n)
{
    int j=0; 
    for(int i=0; i<n; i++)
    {
        if(strncmp(NODE[i], NODE[i+1], k+1)!=0)
        {
            strcpy(NNODE[j], NODE[i]);
            j++;
            if(i+1==n-1)
            {
              strcpy(NNODE[j], NODE[i+1]);   
            }
        }
    }
    return j; 
}

void print_BOSS(char **NODE, int *L, bool *W_minus, char *W, int m, int k)
{
    printf("i\tL\tNODE\tW\tW-\n");
    for(int i=0; i<m; i++)
    {
        printf("%d\t%d\t", i,L[i]);
        for(int j=k-1; j>=0; j--)
            printf("%c", NODE[i][j]);
        printf("\t%c\t%d\n", W[i], W_minus[i]);
    }
        
}
void reverse_T(char*T, char *T_i, int n)
{
    int j=0;
    for(int i=n-1; i>=0;i--)
    {
       T_i[j]=T[i];
       j++;
    }
    T_i[n-1]='\0';
}
bool compare_boss (char **NODE, char **RAD, int n)
{
    for(int i=0; i<n; i++)
    {
        if(strcmp(NODE[i], RAD[i])!=0)
        {
            printf("%s:%s", NODE[i], RAD[i]);
            return false;
        }
    }
    return true; 
}
bool compare_W (char *NODE, char *RAD, int n)
{
    for(int i=0; i<n; i++)
    {
        if(NODE[i]!=RAD[i])
        {
            printf("%d",i);
            printf("%c:%c", NODE[i], RAD[i]);
            return false;
        }
    }
    return true; 
}
bool compare_Wminus (bool *NODE, bool *RAD, int n)
{
    for(int i=0; i<n; i++)
    {
        if(NODE[i]!=RAD[i])
            return false;
    }
    return true; 
}
bool compare_L (int *L, int *Lr, int n)
{
    for(int i=0; i<n; i++)
    {
        if(L[i]!=Lr[i])
            return false;
    }
    return true; 
}

int boss_sort(int mm, char *T_i, char **NODE, int **L, char **W, bool **W_minus, int k, int **F)
{
    //Nó auxiliar para ter a ordem de todos os gerados 
    char **NNODE = NULL;
    NNODE = (char**)malloc((mm+1)* sizeof(char*));
    for(int i = 0; i <=mm ; i++)  NNODE[i] =(char*) malloc((k+2) * sizeof(char));
    node(mm, T_i, NNODE, k); 
    qsort(NNODE, mm, sizeof(char*), compare);
    //exclusão dos nós iguais 
    int m=new_node(NNODE, k, NODE, mm);
    //exclui o nó auxiliar 
    for(int i = 0; i <=mm; i++) free(NNODE[i]);
    free(NNODE);
    //criação das estruturas
    *L= (int *)malloc((m+1) * sizeof(int));
    *W= (char *)malloc((m+1) * sizeof(char));
    *W_minus= (bool *)malloc((m+1) * sizeof(bool));
    *F= (int *)malloc((256) * sizeof(int));
    first(NODE,m,*F);
    l(*L,m,NODE, k);
    w(*W,m,NODE);
    pass_node(NODE, k, m);
    w_minus(*W_minus,NODE,m,k,*W);
    return m;
}

int boss_radix(int mm, char *T_i, char **RAD, int **Lr, char **Wr, bool **Wr_minus, int k, int **Fr)
{
    //Nó auxiliar para ter a ordem de todos os gerados 
    char **RADD = NULL;
    RADD = (char**)malloc((mm+1)* sizeof(char*));
    for(int i = 0; i <=mm ; i++)  RADD[i] =(char*) malloc((k+2) * sizeof(char));
    node(mm, T_i, RADD, k); 
    radix(RADD, k, mm);
    *Wr= (char *)malloc((mm+1) * sizeof(char));
    *Lr= (int *)malloc((mm+1) * sizeof(int));
    l(*Lr,mm,RADD, k);
    wr(*Wr,mm,RADD, k, *Lr);
    int m=new_noder(RADD, k, RAD, mm, *Lr, *Wr);
    //exclui o nó auxiliar 
    for(int i = 0; i <=mm; i++) free(RADD[i]);
    free(RADD);
    //criação das estruturas
    *Wr_minus= (bool *)malloc((m+1) * sizeof(bool));
    *Fr= (int *)malloc((256) * sizeof(int));
    first(RAD,m,*Fr);
    pass_node(RAD, k, m);
    w_minus(*Wr_minus,RAD,m,k,*Wr);
    return m;
}