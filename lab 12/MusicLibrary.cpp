
/*
 * File:   MusicLibrary.cpp
 */

#include "MusicLibrary.h"

//The default constructor of the library
MusicLibrary::MusicLibrary()
{
    library.clear();
    owner = "nobody";
    filename;
}

//The funtion for adding a song to the library
bool MusicLibrary::add(Song s)
{
    int size = library.size();

    if(size==0)
    {
        library.push_back(s);
        return 1;
    }
    else
    {
        for(int j = 0; j < size; j++)
        {
            if(s == library.at(j))
            {
                cout << "ERROR: Song already in library not added." << endl;
                return 0;
            }
        }
        library.push_back(s);
        return 1;
    }
}
bool MusicLibrary::remove(int index)
{
    int size = library.size();
    if(index < 0 || index > (size-1))
        return 0;
    else
    {
        library.erase(library.begin()+(index-1));
        return 1;
    }

}
void MusicLibrary::print() const
{
    int size = library.size();

    for( int i = 0; i < size; i++)
    {
        cout << library.at(i) << endl;
    }
    cout << endl;
}
MusicLibrary::~MusicLibrary()
{
}

