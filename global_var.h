#ifndef global_var
#define global_var
#include<stdio.h>

struct song{
    int id;
    char title[50];
    char year[50];
    int id_singer;
    int idalbum;
};
struct album{
    int idalbum;
    char name[50];
    int nb_song;
};
struct  singer{
    int id_singer;
    char name[20];
    int nb_album;
    int *albums;


};







#endif