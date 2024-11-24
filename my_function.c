//hey as i mentioned before that i had some problems using GUI(GTK)
//this is  conosol part the basic services that will be provided by this programme
//some search function are messing some fixing but the relations are standing perfectly
//the gui i will add in the last submission and i plan to make it play the songs 
//i hope that you advise me and give me youre opinion and i will be happy if you
//suggest any changes or improvments




#include "global_var.h"
#include <stdlib.h>
#include <string.h>
#include "my_function.h"

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>

// Global variable for generating unique IDs
// Global counters for IDs in global_var.h  
int global_song_id;
int global_album_id;
int global_singer_id;

//keep count 
void save_id_counters() {
    FILE *file = fopen("id_counters.bin", "wb");
    if (file) {
        fwrite(&global_song_id, sizeof(int), 1, file);
        fwrite(&global_album_id, sizeof(int), 1, file);
        fwrite(&global_singer_id, sizeof(int), 1, file);
        fclose(file);
    } else {
        perror("Error saving ID counters");
    }
}


// Function to add a new song
void add_song(struct song *new_song) {
    new_song->id = ++global_song_id;

    printf("Enter the song title: ");
    scanf("%49s", new_song->title);

    printf("Enter the year of release: ");
    scanf("%49s", new_song->year);

    printf("Enter the singer's name: ");
    scanf("%19s", new_song->singer);

    printf("Enter the album name: ");
    scanf("%49s", new_song->nom_album);

    printf("Added song: ID=%d, Title=%s, Year=%s, Singer=%s, Album=%s\n", 
           new_song->id, new_song->title, new_song->year, new_song->singer, new_song->nom_album);
    save_id_counters();       
}


// Function to add a new album
int add_album(struct album *new_album) {
    
    new_album->idalbum = ++global_album_id;
    
    
    printf("Enter the album name: ");
    scanf("%49s", new_album->name);  

    
    printf("Enter the number of songs in the album: ");
    scanf("%d", &new_album->nb_song);

   
    new_album->song_ids = malloc(sizeof(int) * new_album->nb_song);  // Allocate memory for song IDs

    
    if (new_album->song_ids == NULL) {
        printf("Error allocating memory for song IDs.\n");
        return 0;
    }

    
    FILE *file = fopen("songs.bin", "rb");
    if (!file) {
        printf("Error opening songs file.\n");
        free(new_album->song_ids);  
        return 0;
    }

    struct song current_song;
    int song_count = 0;

    
    while (fread(&current_song, sizeof(struct song), 1, file) == 1) {
        if (strcasecmp(current_song.nom_album, new_album->name) == 0) {

            if (song_count < new_album->nb_song) {
                new_album->song_ids[song_count++] = current_song.id;
            }
        }
    }

    fclose(file);

    
    if (song_count < new_album->nb_song) {
        printf("!!!!Found only %d songs for album!!! '%s'.\n", song_count, new_album->name);
    }

    
    printf("Added album: ID=%d, Name=%s, Number of Songs=%d\n", 
           new_album->idalbum, new_album->name, song_count);

    
    save_id_counters();

    
    free(new_album->song_ids);
    return new_album->idalbum;
}


int is_valid_album_id(int album_id) {
    struct album current_album;
    FILE *album_file = fopen("album.bin", "rb");
    if (!album_file) {
        perror("Error opening album file");
        return 0;
    }

    while (fread(&current_album, sizeof(struct album), 1, album_file) == 1) {
        if (current_album.idalbum == album_id) {
            fclose(album_file);
            return 1; // Found
        }
    }

    fclose(album_file);
    return 0; // Not found
}


// Function to add a new singer
void add_singer(struct singer *new_singer) {
    // Increment global singer ID counter and assign it
    new_singer->id_singer = ++global_singer_id;

    // Get the singer's name
    printf("Enter the singer's name: ");
    scanf("%19s", new_singer->name);

    // Get the number of albums and validate
    printf("Enter the number of albums for this singer: ");
    scanf("%d", &new_singer->nb_album);

    if (new_singer->nb_album <= 0) {
        printf("Number of albums must be positive!\n");
        return;
    }

    // Allocate memory for the albums array
    new_singer->albums = malloc(new_singer->nb_album * sizeof(int));
    if (new_singer->albums == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Fill in the album IDs, with validation
    int i = 0;
    while ( i < new_singer->nb_album) {
        int album_id;
        printf("Enter album ID %d for this singer (or -1 to create a new album): ", i + 1);
        scanf("%d", &album_id);

        if (album_id == -1) {
            struct album my_album;
            // Call a function to add a new album and get its ID
            album_id = add_album(&my_album);
        } else {
            // Validate the album ID exists
            if (is_valid_album_id(album_id)==0) { // Implement this function
                printf("Invalid album ID %d! Please re-enter.\n", album_id);
                i--; // Retry this index
                continue;
            }
        }

        // Save the album ID to the singer's list
        new_singer->albums[i] = album_id;
        i++;
    }

    // Display added singer details
    printf("Added singer: ID=%d, Name=%s, Number of Albums=%d\n",
           new_singer->id_singer, new_singer->name, new_singer->nb_album);

   
   

    // Save updated ID counters
    save_id_counters();
}

// Cleanup function for a singer
void free_singer(struct singer *singer) {
    if (singer->albums) {
        free(singer->albums);
        singer->albums = NULL;
    }
}

//save to file function

void save_to_file(const void *structure, size_t struct_size, const char *filename) {
    FILE *file = fopen(filename, "ab");  // Open file in append binary mode
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the structure to the file
    if (fwrite(structure, struct_size, 1, file) != 1) {
        perror("Error writing to file");
    } else {
        printf("Structure saved to %s successfully.\n", filename);
    }

    fclose(file);

}

void load_id_counters() {
    FILE *file = fopen("id_counters.bin", "rb");
    if (file) {
        fread(&global_song_id, sizeof(int), 1, file);
        fread(&global_album_id, sizeof(int), 1, file);
        fread(&global_singer_id, sizeof(int), 1, file);
        fclose(file);
    } else {
        // File may not exist on first run; initialize counters
        global_song_id = 0;
        global_album_id = 0;
        global_singer_id = 0;
    }
}


//search functions
void search_song_by_title() {
    char search_title[50];
    struct song current_song;
    FILE *file = fopen("songs.bin", "rb");

    if (!file) {
        perror("Error opening songs file");
        return;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Clear the buffer

    printf("Enter the song title to search for: ");
    fgets(search_title, sizeof(search_title), stdin);
    search_title[strcspn(search_title, "\n")] = '\0'; // Remove trailing newline

    int found = 0;
    while (fread(&current_song, sizeof(struct song), 1, file) == 1) {
        current_song.title[strcspn(current_song.title, "\n")] = '\0'; // Remove newline
        printf("Checking song: '%s'\n", current_song.title); // Debug print
        if (strcasecmp(current_song.title, search_title) == 0) { // Case-insensitive match
            printf("Song found: ID=%d, Title=%s, Year=%s, Singer=%s, Album=%s\n",
                   current_song.id, current_song.title, current_song.year, current_song.singer, current_song.nom_album);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No song with title '%s' found.\n", search_title);
    }

    fclose(file);
}


void search_album_by_name() {
    char search_name[50];
    struct album current_album;
    struct song current_song;

    // Open the album file
    FILE *album_file = fopen("album.bin", "rb");
    if (!album_file) {
        perror("Error opening albums file");
        return;
    }

    // Ask for the album name to search
    printf("Enter the album name to search for: ");
    scanf("%49s", search_name);
    while (getchar() != '\n');  // Clear the input buffer

    // Remove any trailing newline or spaces from the input
    search_name[strcspn(search_name, "\n")] = '\0';

    int found = 0;
    while (fread(&current_album, sizeof(struct album), 1, album_file) == 1) {
        // Trim any trailing spaces or newlines from album name in the file
        for (int i = strlen(current_album.name) - 1; i >= 0; i--) {
            if (current_album.name[i] == ' ' || current_album.name[i] == '\n') {
                current_album.name[i] = '\0';
            } else {
                break;
            }
        }

        // Debug: Print the current album being checked
        printf("Checking album: %s\n", current_album.name);

        // Case-insensitive comparison
        if (strcasecmp(current_album.name, search_name) == 0) {
            printf("Album found: ID=%d, Name=%s, Singer=%s, Number of Songs=%d\n",
                   current_album.idalbum, current_album.name, current_album.singer, current_album.nb_song);

            // Now, search for songs in the corresponding album
            FILE *song_file = fopen("songs.bin", "rb");
            if (!song_file) {
                perror("Error opening songs file");
                fclose(album_file);  // Close the album file before returning
                return;
            }

            int song_found = 0;
            // Loop through songs to find those belonging to this album
            while (fread(&current_song, sizeof(struct song), 1, song_file) == 1) {
                if (current_song.nom_album == current_album.name) {  // Match the album names
                    printf("\tSong ID=%d, Title=%s, Singer=%s\n", 
                           current_song.id, current_song.title, current_song.singer);
                    song_found = 1;
                }
            }

            if (!song_found) {
                printf("\tNo songs found for this album.\n");
            }

            fclose(song_file);  // Close the song file after processing
            found = 1;
            break;  // Exit loop once the album is found
        }
    }

    if (!found) {
        printf("No album with name '%s' found.\n", search_name);
    }

    fclose(album_file);  // Close the album file
}
void search_song_in_album() {
    char album_name[50];
    struct song current_song;
    FILE *file = fopen("songs.bin", "rb");

    if (!file) {
        perror("Error opening songs file");
        return;
    }

    printf("Enter the album name to list its songs: ");
    scanf("%49s", album_name);

    int found = 0;
    while (fread(&current_song, sizeof(struct song), 1, file) == 1) {
        if (strcmp(current_song.nom_album, album_name) == 0) {
            printf("Song: ID=%d, Title=%s, Year=%s, Singer=%s\n",
                   current_song.id, current_song.title, current_song.year, current_song.singer);
            found = 1;
        }
    }

    if (!found) {
        printf("No songs found in album '%s'.\n", album_name);
    }

    fclose(file);
}

void search_albums_by_singer() {
    char singer_name[20];
    struct singer current_singer;
    struct album current_album;
    FILE *singer_file = fopen("singer.bin", "rb");
    FILE *album_file = fopen("album.bin", "rb");

    if (!singer_file || !album_file) {
        perror("Error opening singers or albums file");
        return;
    }

    printf("Enter the singer's name to list their albums: ");
    scanf("%19s", singer_name);

    int found_singer = 0;
    int album_found = 0;
    while (fread(&current_singer, sizeof(struct singer), 1, singer_file) == 1) {
        if (strcmp(current_singer.name, singer_name) == 0) {
            found_singer = 1;
            printf("Albums by %s:\n", singer_name);

            // for each album ID in the singer's albums, find and print the album details
            for (int i = 0; i < current_singer.nb_album; i++) {
                
                rewind(album_file); 
                printf("this is working \n");
                while (fread(&current_album, sizeof(struct album), 1, album_file) == 1) {
                    if (current_album.idalbum == current_singer.albums[i]) {
                        printf("Album ID=%d, Name=%s, Number of Songs=%d\n",
                               current_album.idalbum, current_album.name, current_album.nb_song);
                        album_found = 1;
                        break;
                    }
                }
            }
            break;
        }
    }

    if (!found_singer) {
        printf("No singer with name '%s' found.\n", singer_name);
    } else if (!album_found) {
        printf("No albums found for singer '%s'.\n", singer_name);
    }

    fclose(singer_file);
    fclose(album_file);
}

void search_singer_by_name() {
    struct singer current_singer;
    FILE *singer_file = fopen("singer.bin", "rb");

    if (!singer_file) {
        perror("Error opening singers file");
        return;
    }

    char search_name[20];
    int found = 0;

    printf("Enter the singer's name to search: ");
    scanf("%19s", search_name);

    while (fread(&current_singer, sizeof(struct singer), 1, singer_file) == 1) {
        printf("%s\n",current_singer.name);
        if (strcmp(current_singer.name, search_name) == 0) {
            found = 1;
            printf("%s",current_singer.name);
            break;
        }
    }

    if (!found) {
        printf("Singer '%s' not found in the database.\n", search_name);
    }
    
}

void print_all_files() {
    struct song current_song;
    struct album current_album;
    struct singer current_singer;

    // Open and print songs
    FILE *song_file = fopen("songs.bin", "rb");
    if (!song_file) {
        perror("Error opening songs file");
    } else {
        printf("Songs:\n");
        while (fread(&current_song, sizeof(struct song), 1, song_file) == 1) {
            printf("ID=%d, Title=%s, Year=%s, Singer=%s, Album Name=%s, Album ID=%d, Path=%s\n",
                   current_song.id, current_song.title, current_song.year,
                   current_song.singer, current_song.nom_album, current_song.idalbum,
                   current_song.song_path);
        }
        fclose(song_file);
    }

    // Open and print albums
    FILE *album_file = fopen("album.bin", "rb");
    if (!album_file) {
        perror("Error opening albums file");
    } else {
        printf("\nAlbums:\n");
        while (fread(&current_album, sizeof(struct album), 1, album_file) == 1) {
            printf("ID=%d, Name=%s, Singer=%s, Number of Songs=%d\n",
                   current_album.idalbum, current_album.name, current_album.singer, current_album.nb_song);

            if (current_album.nb_song > 0) {
                // Allocate memory for song IDs
                current_album.song_ids = (int *)malloc(current_album.nb_song * sizeof(int));
                if (!current_album.song_ids) {
                    perror("Memory allocation failed for song IDs");
                    continue;
                }

                // Read song IDs from file (mockup since they aren't in binary file in this case)
                for (int i = 0; i < current_album.nb_song; i++) {
                    current_album.song_ids[i] = i + 1; // Replace with actual logic to read song IDs
                    printf("\tSong ID=%d\n", current_album.song_ids[i]);
                }

                // Free memory after use
                free(current_album.song_ids);
            }
        }
        fclose(album_file);
    }

    // Open and print singers
    FILE *singer_file = fopen("singer.bin", "rb");
    if (!singer_file) {
        perror("Error opening singers file");
    } else {
        printf("\nSingers:\n");
        while (fread(&current_singer, sizeof(struct singer), 1, singer_file) == 1) {
            printf("ID=%d, Name=%s, Number of Albums=%d\n",
                   current_singer.id_singer, current_singer.name, current_singer.nb_album);
        }
        fclose(singer_file);
    }

    // Open and print ID counters
    FILE *id_counters_file = fopen("id_counters.txt", "r");
    if (!id_counters_file) {
        perror("Error opening ID counters file");
    } else {
        printf("\nID Counters:\n");
        char line[100];
        while (fgets(line, sizeof(line), id_counters_file)) {
            printf("%s", line);
        }
        fclose(id_counters_file);
    }
}
int init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        fprintf(stderr, "Mix_OpenAudio error: %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    return 0;
}

// Function to play the selected song (without parameters)
void play_a_song() {



    // Ask for the song path inside the function
    char song_path[100];
    printf("Enter the path to the song (e.g., music/song.mp3): ");
    scanf("%s", song_path);

    // Load and play the song
    Mix_Music *music = Mix_LoadMUS(song_path);
    if (music == NULL) {
        fprintf(stderr, "Mix_LoadMUS error: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(music, 1) == -1) {
        fprintf(stderr, "Mix_PlayMusic error: %s\n", Mix_GetError());
    }

    // Wait for the music to finish
    while (Mix_PlayingMusic()) {
        SDL_Delay(100);  // Wait 100 ms
    }

    Mix_FreeMusic(music);
}
void cleanup_audio() {
    Mix_CloseAudio();
    SDL_Quit();
}




















