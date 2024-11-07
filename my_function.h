#ifndef my_function
#define myfinction
#include<stdio.h>
#include"global_var.h"
int golobal_id=0;
void add_song(){
    struct song song;
    song.id=golobal_id+1;
    printf("%d",song.id);
    printf("enter the new song name");
    scanf("%s",song.title);

    printf("enter the year of releas");
    scanf("%s",song.year);


 

    printf("enter the album ");
    scanf("%d",song.idalbum);



   

    printf("%s %s\n",song.year,song.title,song.idalbum);
    

}

void add_artist(){
    printf("artist\n");
}

void add_album(){
    printf("album\n");
}


#endif