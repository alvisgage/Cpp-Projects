//lab 3



#include <cstdlib>
#include <iostream>
#include <string>
#include "Song.h"
#include "utility.h"
#include "MusicLibrary.h"
#include <vector>
        
using namespace std;

/*
 *
 */
int main(int argc, char** argv) {

        MusicLibrary lib;
	Song s1;
        cout << s1 << endl << endl;

	Song s2("Can't Smile Without you", "Chris Arnold", "Barry Manilow", "/home/music/song102", "Even Now", 1978, CLASSICAL, MP3);
        cout << s1 << endl << s2 << endl << endl;

        Song s3("Something Stupid", "Carson Parks", "Frank Sinatra", "/home/music/song103", "The World we Knew", 1967, POP, WMA);
        cout << s1 << endl << s2 << endl << s3 << endl << endl;

	Song s4("Billie Jean", "Michael Jackson", "Michael Jackson", "/home/music/song104", "Thriller", 1983, POP, WAV);
        cout << s1 << endl << s2 << endl << s3 << endl << s4 << endl << endl;

        lib.add(s1);
        lib.add(s2);
	lib.add(s3);
	lib.add(s4);

	lib.print();
        lib.save();
        
	if (lib.remove(1))
            lib.print();
	if (lib.remove(4))
            lib.print();
        else
            cout << "Can't carry out lib.remove(4)" << endl;
        
        if (lib.remove(s2))
            lib.print();
        else
            cout << "Can't remove song 2." << endl;


    return 0;
}
