#ifndef BOSS_H
#define BOSS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void node(int m, char *T, char **NODE, int k);
int compare (const void *a, const void *b);
void radix(char **NODE, int k, int n);
void radix_one(char *NODE, int n);
void l(int *L, int m, char **NODE, int k);
void w(char *W, int m, char **NODE);
void wr(char *W, int n, char **NODE, int k, int *L);
void w_minus(bool *W_minus, char **NODE, int m, int k, char *W);
void first(char **NODE, int m, int *F);
void pass_node(char **NODE, int k, int m);
int new_node(char **NODE, int k, char **NNODE, int n);
void print_BOSS(char **NODE, int *L, bool *W_minus, char *W, int m, int k);
void reverse_T(char*T, char *T_i, int n);
bool compare_boss (char **NODE, char **RAD, int n);
bool compare_W (char *NODE, char *RAD, int n);
bool compare_Wminus (bool *NODE, bool *RAD, int n);
int boss_sort(int mm, char *T_i, char **NODE, int **L, char **W, bool **W_minus, int k, int **F);
int boss_radix(int mm, char *T_i, char **RAD, int **Lr, char **Wr, bool **Wr_minus, int k, int **Fr);
int new_noder(char **NODE, int k, char **NNODE, int n, int *L, char *W);
bool compare_L (int *L, int *Lr, int n);
#endif