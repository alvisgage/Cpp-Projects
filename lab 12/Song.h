
/*
 * File:   Song.h
 *
 * Created on September 14, 2012, 1:47 PM
 */



#ifndef SONG_H
#define	SONG_H

#include <iostream>
#include <string>

using namespace std;

enum Genre {CLASSICAL, JAZZ, NEW_AGE, OPERA, POP, ROCK};
enum Format {MP3, WMA, WAV};

class Song
{

public:
    Song();
    Song(string title, string composer, string artist, string path, string album, unsigned int year, Genre genre, Format format);
    Song(Song const &Song);
    ~Song();

    string get_title()const;
    string get_composer()const;
    string get_artist()const;
    string get_path()const;
    string get_album()const;
    unsigned int get_year()const;
    Genre get_genre()const;
    Format get_format()const;
    void set_title(string title);
    void set_composer(string composer);
    void set_artist(string artist);
    void set_path(string path);
    void set_album(string album);
    void set_year(unsigned int year);
    void set_genre(Genre genre);
    void set_format(Format format);

    bool operator==(const Song &obj);


private:
    string title;
    string composer;
    string artist;
    string path;
    string album;
    unsigned int year;
    Genre genre;
    Format format;


};

#endif	/* SONG_H */
