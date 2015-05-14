
/*
 * File:   Song.cpp
 */

#include "Song.h"

Song::Song() //Default Constructor
{
    title = "Viva La Vida";
    composer = "Coldplay";
    artist = "Coldplay";
    path = "/home/music/song101";
    album = "Viva La Vida";
    year = 2008;
    genre = ROCK;
    format = WMA;
}
//Non-Default Constructor
Song::Song(string title, string composer, string artist, string path, string album, unsigned int year, Genre genre, Format format)
{
    this->title = title;
    this->composer = composer;
    this->artist = artist;
    this->path = path;
    this->album = album;
    this->year = year;
    this->genre = genre;
    this->format = format;

}
//Copy constructor
Song::Song(const Song& Song)
{
    title = Song.title;
    composer = Song.composer;
    artist = Song.artist;
    path = Song.path;
    album = Song.album;
    year = Song.year;
    genre = Song.genre;
    format = Song.format;
}

Song::~Song()
{
}
//All of the Getter functions for the Song class
string Song::get_title() const
{
    return title;
}
string Song::get_composer() const
{
    return composer;
}
string Song::get_artist() const
{
    return artist;
}
string Song::get_path() const
{
    return path;
}
string Song::get_album() const
{
    return album;
}
unsigned int Song::get_year() const
{
    return year;
}
Genre Song::get_genre() const
{
    return genre;
}
Format Song::get_format() const
{
    return format;
}

//All of the setter functions for the song class
void Song::set_title(string title)
{
    this->title = title;
}
void Song::set_composer(string composer)
{
    this->composer = composer;
}
void Song::set_artist(string artist)
{
    this->artist = artist;
}
void Song::set_path(string path)
{
    this->path = path;
}
void Song::set_album(string album)
{
    this->album = album;
}
void Song::set_year(unsigned int year)
{
    this->year = year;
}
void Song::set_genre(Genre genre)
{
    this->genre = genre;
}
void Song::set_format(Format format)
{
    this->format = format;
}

//overloading the == operator to help with checking if a song is equal to another song
bool Song::operator ==(const Song& obj)
{
    bool status;

    if(title == obj.title && artist == obj.artist &&
            composer == obj.composer && path == obj.path &&
            album == obj.album && year == obj.year &&
            genre == obj.genre && format == obj.format)
        status = true;
    else
        status = false;

}