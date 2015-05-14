/* 
 * File:   main.cpp
 * Author: Rage Gage
 *
 * Created on September 29, 2012, 11:01 AM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include<string.h>
#include<ctype.h>
#include<cctype>
#include<vector>

using namespace std;

static string sentence;
static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
int length;
int score,lastScore,copyNum;

char randomChar(){
    return alphabet[rand()%27];
}
void uppCase(){
    for(int i=0;i<sentence.length();i++)
        sentence[i]=toupper(sentence[i]);
}
string genString(){
    string s="";
    for(int i=0;i<length;i++)
        s+=randomChar();
    return s;
}
void getScore(string copy){
    score=0;
    for(int i=0;i<length;i++)
        if(copy[i]==sentence[i])
            score++;
}
string genCopies(string orig,int rate){
    string copy = orig;
    int chance=0;
    for(int i=0;i<length;i++)
    {
        chance=rand()%rate;
        if (chance==0)
            copy[i]=randomChar();
    }
    return copy;
}
void getSentence(){
    cout << "Enter target sentence: ";
    getline(cin,sentence);
    uppCase();
    length=sentence.length();
}

int main() {
    vector<string> parents;
    srand(time(NULL));
    getSentence();
    string s=genString();
    string save,copy;
    int gen=0,count=1,perGen,mutationRate;
    string orig=s;
    char ans;
    cout << "\nEnter the number of copies per generation: ";
    cin >> perGen;
    cout << "\nEnter mutation rate as percentage: ";
    cin >>mutationRate;    
    cout << "\nOriginal string:\n" << s << endl;    
    cout << "\nReady?(y/n): ";
    cin >> ans;
    if(ans=='y')
    while(score!=length)
    {
        gen++;
        copyNum=0;
        cout << "Generation "<<gen <<":\n";        
        for(int x=0;x<perGen;x++)
        {
            copy=genCopies(s,mutationRate);
            getScore(copy);
            if(score>=lastScore)
               {
                save=copy;
                lastScore=score;
                copyNum=count;
               }
            copyNum++;
            count++;
            cout << copy << " Score: " << score << endl;
        }
        cout << save << " Score: " << lastScore << endl;
        s=save;
        parents.push_back(save);
    }
    cout << "\nOriginal String: " << orig;
    cout << "\nGenerations: " << gen;
    cout << "\nCopy Number: " << copyNum;
    cout << "\nMutation Rate: "<< mutationRate;
    cout << "\nCopies per generation: " << perGen << endl;
    
    int p;
    cout << "\nEnter generation number to see parent copy: ";
    cin >> p;    
    while(ans!='q')
    {        
        cout << "\n" << parents[p-1];
        cout << "\nEnter generation number to see parent copy: ";
        cin >> p; 
    }
    
    return 0;
}

