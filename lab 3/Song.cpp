#include "Song.h"
#include <string>
Song::Song() {
    title = "Viva La Vida";
    composer = "Coldplay";
    artist = "Coldplay";
    path = "/home/music/song101";
    album = "Viva La Vida";
    year = 2008;
    genre = ROCK;
    format = WMA;
}
Song::Song(string title, string composer, string artist, string path, string album,
            unsigned int year, Genre genre, Format format) {
    this->title = title;
    this->composer = composer;
    this->artist = artist;
    this->path = path;
    this->album = album;
    this->year = year;
    this->genre = genre;
    this->format = format;
}
Song::~Song() {
}
string Song::get_composer() const{
    return composer;
}
string Song::get_album() const{
    return album;
}
string Song::get_artist() const{
    return artist;
}
string Song::get_title() const{
    return title;
}
string Song::get_path() const{
    return path;
}
unsigned int Song::get_year() const{
    return year;
}
Genre Song::get_genre() const{
    return genre;
}
Format Song::get_format() const{
    return format;
}
void Song::set_album(string album){
    this->album = album;
}
void Song::set_composer(string composer){
    this->composer = composer;
}
void Song::set_artist(string artist){
    this->artist = artist;
}
void Song::set_title(string title){
    this->title = title;
}
void Song::set_year(unsigned int year){
    this->year = year;
}
void Song::set_path(string path){
    this->path = path;
}
void Song::set_genre(Genre genre){
    this->genre = genre;
}
void Song::set_format(Format format){
    this->format = format;
}
bool Song::isEqual(Song s1){
    bool value = false;
    if (album == s1.album) 
            if (artist == s1.artist) 
                if (composer == s1.composer) 
                    if (format = s1.format) 
                        if (genre = s1.genre) 
                            if (path == s1.path) 
                                if (title == s1.title) 
                                    if (year = s1.year)
                                                value =true;
    else
        value = false;                               
  return value;                                
}