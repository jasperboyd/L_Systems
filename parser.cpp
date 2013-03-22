#include <stdlib.h>
#include <fstream> 
#include <iostream> 
#include <string> 
#include <map> 
#include <vector> 
using namespace std; 

char HSH = '#';   
string LEN = "len:";
int SEG_LEN; 
string ITER = "iter:";
string ROT = "rot:";
string REP = "rep:"; 
string START = "start:";
// +(theta) turn left by angle theta 
char PLS = '+'; 
// -(theta) turn right by angle theta
char MIN = '-'; 
// &(theta) pitch down by angle theta
char AMP = '&'; 
// ^(theta) pitch up by angle theta 
char NCH = '^';
// /(theta) roll left by angle theta
char FSL = '/'; 
// \(theta) roll right by angle theta
char BSL = '\\';
// | is equivalent to +(180) -(180) 
char VER = '|'; 

//couldn't get atoi or stoi to work for me
int ctoi (char c) { 
    int i; 
    if (c == '1'){
        i = 1; 
    } else if (c == '2') { 
        i = 2; 
    } else if (c == '3') { 
        i = 3;
    } else if (c == '4') {
        i = 4; 
    } else if (c == '5') { 
        i = 5; 
    } else if (c == '6') {
        i = 6; 
    } else if (c == '7') { 
        i = 7; 
    } else if (c == '8') { 
        i = 8; 
    } else if (c == '9') { 
        i = 9; 
    } else {
        i = -1; //not an int
    }
    return i; 
}

void process_line ( string l ) {
    string t; //temp
    int d_pos; 
    int d_len; 
    int l_length = l.length(); 
    cout << "l_length = " << l_length << endl; 
    string l_sub4 = l.substr(0, 4);
    cout << "l_sub4 = " << l_sub4 << endl; 
    if (l[0] == HSH) {
        cout << "comment" << endl; 
        return; //ignore comment
    } else if (l_sub4.compare (LEN) == 0) {
        cout << "length" << endl;
        d_pos = 5;
        d_len = l_length - d_pos;
        cout << "d_len = " << d_len << endl;
        if (d_len == 1){
            SEG_LEN = ctoi(l[d_pos]);
        }
        cout << "SEG_LEN = " << SEG_LEN << endl;
        return; 
    } else if (l.substr(0, 5).compare (ITER) == 0) {
        cout << "iter" << endl; 
        return; 
    } else if (l_sub4.compare (ROT) == 0) { 
        cout << "rot" << endl; 
        return;
    } else if (l_sub4.compare (REP) == 0) { 
        cout << "rep" << endl; 
        return; 
    } else if (l.substr(0, 6).compare (START) == 0 ) {
        cout << "start" << endl; 
        return; 
    } else { 
        //cout << l[i] << endl;
    }
}//process_line

int main ( ) {
    string line; 
    string filename = "test/lsys1";
    filename = filename + ".txt"; 
    cout << filename << endl;
    ifstream in (filename.c_str()); 
    if (in.is_open ( ) ) {
        cout << "File is open" << endl;
        while(in.good ( ) ) {
            getline (in, line); 
            process_line (line); 
        }
    } else { 
        cout << "The file couldn't open" << endl; 
    }
}
