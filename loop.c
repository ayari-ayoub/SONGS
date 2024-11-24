#include <stdio.h>
#include "loop.h"
#include "my_function.h"


#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>

void display_menu() {
    printf("\n===== Music Library Menu =====\n");
    printf("1. Add Song\n");
    printf("2. Add Singer\n");
    printf("3. Add Album\n");
    printf("4. Search Song by Title\n");
    printf("5. Search Album by Name\n");
    printf("6. Search Singer by Name\n");
    printf("7. Search Song in Album\n");
    printf("8. Search Albums by Singer\n");
    printf("9. Play Song\n");
    printf("10. Exit\n");
    printf("Select an option: ");
}
void main_loop() {
    int choice;
    char input[50];
    int id;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                struct song my_song;
                add_song(&my_song);
                save_to_file(&my_song,sizeof(struct song), "songs.bin");
                //print_all_files();
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
            case 4:
                search_song_by_title();
                break;
            case 5:
                search_album_by_name();
                break;
            case 6:
                 search_singer_by_name();
                break;
            case 7:
                search_song_in_album();
                

                break;
            case 8:
                search_albums_by_singer();
                break;

            case 9:
                init_audio();
                play_a_song();
    
                break;
            case 10:
                cleanup_audio();
                return;    
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
