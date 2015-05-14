#ifndef MUSICLIBRARY_H
#define	MUSICLIBRARY_H

#include <vector>
#include "utility.h"

using namespace std;
class MusicLibrary
{
public:
    MusicLibrary();
    MusicLibrary(string filename, string owner);
    ~MusicLibrary();

    bool add(Song s);
    bool remove(Song s);
    bool remove(int index);
    void print()const;
    bool save()const;


private:
    vector<Song> library;
    string owner;
    string filename;

};

#endif	/* MUSICLIBRARY_H */