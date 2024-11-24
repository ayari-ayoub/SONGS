#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H
#include "global_var.h"
#include <stdio.h>


void save_id_counters();
void load_id_counters();
void add_song(struct song *new_song);
int add_album(struct album *new_album);
void add_singer(struct singer *new_singer);
void free_singer(struct singer *singer);
void save_to_file(const void *structure, size_t struct_size, const char *filename);
void print_all_files();

void search_song_by_title();
void search_album_by_name();

void search_singer_by_name();
void search_song_in_album();
void search_albums_by_singer();
int init_audio();
void play_a_song();
//void stop_song()
void cleanup_audio();
#endif 