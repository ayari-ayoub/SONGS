#ifndef global_var
#define global_var
#include<stdio.h>

struct song{
    int id;
    char title[50];
    char year[50];
    char singer[20];
    int id_singer;
    char nom_album[20];
    int idalbum;
    char song_path[100];


};
struct album {
    int idalbum;       
    char name[50];     
    char singer[20];   
    int nb_song;       
    int *song_ids;     
    int id_singer;     
};
struct  singer{
    int id_singer;
    char name[20];
    int nb_album;
    int *albums;


};







#endif