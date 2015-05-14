using namespace std;
#include <string>
#include "MusicLibrary.h"
#include <vector>
#include "Song.h"
#include <iostream>
#include <fstream>


MusicLibrary::MusicLibrary() {
    library.clear();
    owner = "nobody";
    filename="";
}

MusicLibrary::MusicLibrary(string filename,string owner) {
    this->filename = filename;
    this->owner = owner;
}

MusicLibrary::~MusicLibrary() {
}
bool MusicLibrary::add(Song s){
    bool value = true;
    for (int i=0;i<library.size();i++)
    {
        if(s.isEqual(library.at(i)))
        {
            value = false;
            break;
        }            
    }
    if(value)
        library.push_back(s);
    return (value);
}
bool MusicLibrary::remove(Song s){
    bool value = false;
    for (int i=0;i<library.size();i++)
    {
        value=s.isEqual(library.at(i));
        if(value=true)
            library.erase(library.begin() + i);
    }
    if(value = true)
        return true;
    else
        return false;
}
bool MusicLibrary::remove(int index){
    index = index - 1;
    if (library.size() < index)
        return false;
    else
    {
        library.erase(library.begin() + index);
        return true;
    }
}
void MusicLibrary::print() const{
    for (int i=0;i<library.size();i++)
    {
        cout << "Track Number: " << i+1 << endl;
        cout << "Title: " << library.at(i).get_title() << endl;
        cout << "Composer: " << library.at(i).get_composer() << endl;
        cout << "Artist: " << library.at(i).get_artist() << endl;
        cout << "Path: " << library.at(i).get_path() << endl;
        cout << "Album: " << library.at(i).get_album() << endl;
        cout << "Year: " << library.at(i).get_year() << endl;
        cout << "Genre: " << library.at(i).get_genre() << endl;
        cout << "Format: " << library.at(i).get_format() << endl;
        cout << endl << endl;
    }
}
bool MusicLibrary::save() const{
    ofstream myfile;
    bool value;
    myfile.open("My Music Library.txt");
    if (myfile.is_open())
    {
        value = true;
        for (int i=0;i<library.size();i++)
         {
        myfile << library.at(i).get_title() <<"," 
               << library.at(i).get_composer() << ","
               << library.at(i).get_artist() << ","
               << library.at(i).get_path() << ","
               << library.at(i).get_album() << ","
               << library.at(i).get_year() << ","
               << library.at(i).get_genre() << ","
               << library.at(i).get_format() << "\n";
        }
        myfile.close();
    }
    else{
        cout <<"Unable to open file." << endl; 
        value = false;}
    return value;
    
}
