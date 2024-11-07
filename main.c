#include<stdio.h>
#include "my_function.h"


int main(){

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
                add_song();
                
                break;
            case 2:
                add_artist();
                
                break;

            case 3:
                add_album();
                
                break;    
            default:
                printf("exiting");
                x=0;


                break;
            }
    }
    return 0;
}