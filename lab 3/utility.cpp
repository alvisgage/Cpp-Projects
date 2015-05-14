using namespace std;
#include <iostream>
#include "utility.h"

ostream & operator<<(ostream& out, const Song s){
    out << s.get_title()<<',';
    out << s.get_composer()<<',';
    out << s.get_artist()<<',';
    out << s.get_path()<<',';
    out << s.get_album()<<',';
    out << s.get_year()<<',';
    out << s.get_genre()<<',';
    out << s.get_format()<<',';
    return out;
}

// overload >> here for homework 2
