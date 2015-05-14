using namespace std;
#include <string>
#ifndef SONG_H
#define	SONG_H
enum Genre {CLASSICAL, JAZZ, NEW_AGE, OPERA, POP, ROCK};
    enum Format {MP3, WMA, WAV};

class Song {
public:
    
    Song();
    Song(string title, string composer, string artist, string path, string album,
            unsigned int year, Genre genre, Format format);
    virtual ~Song();

    string get_composer() const;
    void set_composer(string composer);
    string get_title() const;
    void set_title(string title);
    string get_artist() const;
    void set_artist(string artist);
    string get_path() const;
    void set_path(string path);
    string get_album() const;
    void set_album(string album);
    unsigned int get_year() const;
    void set_year(unsigned int year);
    Genre get_genre() const;
    void set_genre(Genre genre);
    Format get_format() const;
    void set_format(Format format);
    bool isEqual(Song s1);


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

