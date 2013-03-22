#include <stdlib.h>
#include <fstream> 
#include <iostream> 
#include <string> 
#include <map> 
#include <vector> 
using namespace std; 

bool start; 

char HSH = '#'; 
char SPACE = ' ';
string LEN = "len:";
int SEG_LEN; 
string ITER = "iter:";
int ITERATIONS;
string ROT = "rot:";
vector<float> ROTATIONS;
string REP = "rep:"; 
string START = "start:";
//"initial turtle string" 
string INIT_STR; 
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

void process_line ( string l ) {
    if (start) { 
        execute(l); 
    } 
    
    string t; //temp
    int d_pos; 
    int d_len; 
    int l_length = l.length( ); 
    cout << "l_length = " << l_length << endl; 
    string l_sub4 = l.substr(0, 4);
    cout << "l_sub4 = " << l_sub4 << endl; 
    if (l[0] == HSH) {
        cout << "comment" << endl; 
        return; //ignore comment
    } else if (l_sub4.compare(LEN) == 0) {
        cout << "length" << endl;
        d_pos = 5;
        d_len = l_length - d_pos;
        t = l.substr(d_pos, d_len); 
        sscanf(t.c_str( ), "%d", &SEG_LEN);
        cout << "SEG_LEN = " <<  SEG_LEN << endl;
        return; 
    } else if (l.substr(0, 5).compare (ITER) == 0) {
        cout << "iter" << endl; 
        d_pos = 6; 
        d_len = l_length - d_pos; 
        t = l.substr(d_pos, d_len); 
        sscanf(t.c_str( ), "%d", &ITERATIONS); 
        cout << "ITERATIONS = " << ITERATIONS << endl; 
        return; 
    } else if (l_sub4.compare (ROT) == 0) { 
        d_pos = 5;
        d_len = l_length - d_pos; 
        t = l.substr(d_pos, d_len);
        int count = 0; 
        double  current; 
        string c = "";
        for (int i = 0; i < t.length(); i++){ 
            if (t[i] == SPACE) {
                current = ::atof(c.c_str( )); 
                cout << "ROT current = " << current << endl; 
                ROTATIONS.push_back(current);
                count = 0;
                c = ""; 
            } else {
                c += t[count++];
            }//if/else
        }//for
        //remove below and turn into while loop for opti 
        current = ::atof(c.c_str( )); 
        cout << "ROT current = " << current << endl; 
        ROTATIONS.push_back(current); 
        return;
    } else if (l_sub4.compare (REP) == 0) { 
        cout << "rep" << endl; 
        return; 
    } else if (l.substr(0, 6).compare (START) == 0 ) {
        d_pos = 7;
        d_len = l_length - d_pos; 
        INIT_STR = l.substr(d_pos, d_len); 
        cout << "INIT_STR = " << INIT_STR << endl; 
        start = true; 
        return; 
    } else { 
        //cout << l[i] << endl;
    }//if/else
}//process_line

int main ( ) {
    string line; 
    string filename = "test/lsys1";
    filename = filename + ".txt"; 
    cout << filename << endl;
    ifstream in (filename.c_str()); 
    if (in.is_open ( ) ) {
        cout << "File is open" << endl;
        start = false; 
        while(in.good ( ) ) {
            getline (in, line); 
            process_line (line); 
        }
    } else { 
        cout << "The file couldn't open" << endl; 
    }
}
