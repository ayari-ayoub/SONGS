#include<stdio.h>
#include "my_function.h"


int main(){
load_id_counters();
int x=1;
    
    
    
    while(x==1){

    
            
            printf("welcom to SONGS\n");
            printf("menu:\n");
            printf("->add song 1\n");
            printf("->add Artist 2\n");
            printf("->add Album 3\n");
            
            //case
            int c=0;
            scanf("%d?",&c);

            switch (c)
            {
            case 1:
                struct song my_song;
                 add_song(&my_song);
                save_to_file(&my_song,sizeof(struct song), "songs.bin");
                
                break;
            case 2:
                struct singer my_singer;
                add_singer(&my_singer);
                save_to_file(&my_singer,sizeof(struct singer), "singer.bin");
                free_singer(&my_singer);
                
                break;

            case 3:
                struct album my_album;
                 add_album(&my_album);
                 save_to_file(&my_album,sizeof(struct album), "album.bin");
                 
                
                break;    
            default:
                printf("exiting");
                x=0;


                break;
            }
    }
    return 0;
}