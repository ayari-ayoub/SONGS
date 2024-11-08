#ifndef my_function
#define myfinction
#include "global_var.h"
#include <stdlib.h>
#include <string.h>

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
void add_album(struct album *new_album) {
    new_album->idalbum = ++global_album_id;

    printf("Enter the album name: ");
    scanf("%49s", new_album->name);

    printf("Enter the number of songs in the album: ");
    scanf("%d", &new_album->nb_song);

    printf("Added album: ID=%d, Name=%s, Number of Songs=%d\n", 
           new_album->idalbum, new_album->name, new_album->nb_song);
    save_id_counters();       
}

// Function to add a new singer
void add_singer(struct singer *new_singer) {
    new_singer->id_singer = ++global_singer_id;

    printf("Enter the singer's name: ");
    scanf("%19s", new_singer->name);

    printf("Enter the number of albums for this singer: ");
    scanf("%d", &new_singer->nb_album);

    // Allocate memory for the albums array
    new_singer->albums = malloc(new_singer->nb_album * sizeof(int));
    if (new_singer->albums == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Fill in the album IDs
    for (int i = 0; i < new_singer->nb_album; i++) {
        printf("Enter album ID %d for this singer: ", i + 1);
        scanf("%d", &new_singer->albums[i]);
    }

    printf("Added singer: ID=%d, Name=%s, Number of Albums=%d\n", 
           new_singer->id_singer, new_singer->name, new_singer->nb_album);
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















#endif

