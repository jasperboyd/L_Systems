#include <stdlib.h>
#include <fstream> 
#include <iostream> 
#include <string>
#include <sstream> 
#include <map> 
#include <vector> 
using namespace std; 

bool start; 
char SPACE = ' ';
string LEN = "len:";
int SEG_LEN;
string ITER = "iter:";
int ITERATIONS;
string ROT = "rot:";
vector<float> ROTATIONS;
string REP = "rep:"; 
map<char, char> REPS; 
string START = "start:";
char INIT_C; 
map<char, string> PRODUCTION_RULES; 
map<char, bool> in_RULES; 

class Turtle_Pos { 
    float H, L, U; 
    public: 
        Turtle_Pos ( float, float, float );
        turn ( float ); 
        pitch ( float ); 
};

Turtle_Pos::Turtle_Pos ( ) {
    H = 0; 
    L = 0; 
    U = 0; 
}

Turtle_Pos::Turtle_Pos (float h, float, l, float u) {
    H = h; 
    L = l; 
    U = u;
}

Turtle_Pos::turn ( float theta ) {

}

Turtle_Pos::pitch ( float theta ) { 

}

void execute_char ( char c ) { 
    if (c == INIT_C) { 
        //extend my SEG_LEN
    } else if (c == '[') { 
		//push current postion onto stack
    } else if (c == ']') { 
		//pop position from the stack
    } else if (c == '+') {
        // +(theta) turn left by angle theta 
    } else if (c == '-') { 
        // -(theta) turn right by angle theta
    } else if (c == '&') { 
        // &(theta) pitch down by angle theta
    } else if (c == '^') { 
        // ^(theta) pitch up by angle theta 
    } else if (c == '/') { 
        // /(theta) roll left by angle theta
    } else if (c == '\\') { 
        // \(theta) roll right by angle theta
    } else if (c == '|') { 
        // | is equivalent to +(180) -(180) 
    }//if/else
}//process_char

void execute_line ( string l ) {
    for ( int i = 0; i < l.length ( ); i++ ) {
        execute_char ( l[i] );
    }
}

string process_char ( char c ) { 
	//assume correct input
    stringstream ss; 
    string a;
    ss << c; 
    ss >> a;
	if ( in_RULES.at ( c ) ) { 
		return PRODUCTION_RULES.at ( c ); 
	} else { 
		return a; 
	}
}

string next_iter ( string l ) { 
	cout << "next_iter ( " << l << " )" << endl;
    int l_l = l.length ( ); 
	string answer = ""; 
	for ( int i = 0; i < l_l; i++ ) {
	    answer += process_char ( l[i] ); 
	}
	return answer; 
}

void execute ( ) { 
    cout << "execute ( )" << endl;
    string current_str = PRODUCTION_RULES.at (INIT_C);
    for (int i = 0; i < ITERATIONS; i++) { 
        cout << "Beginning Iteration: " << i << endl;
        execute_line( current_str ); 
        next_iter ( current_str ); 
    }//for
}//execute

void process_line ( string l ) {
    cout << "process_line ( " << l << " )" << endl;
    string t; //temp
    int l_l = l.length( ); 
    if ( l_l == 0){
        return; 
    }
    string l_sub4 = l.substr(0, 4);
    if (l[0] == '#') {
        cout << "comment" << endl; 
        return; //ignore comment
    } else if (l_sub4.compare(LEN) == 0) {
        cout << "length" << endl;
        t = l.substr ( 5, l_l - 5 ); 
        sscanf(t.c_str( ), "%d", &SEG_LEN);
        cout << "SEG_LEN = " <<  SEG_LEN << endl;
        return; 
    } else if (l.substr(0, 5).compare (ITER) == 0) {
        cout << "iter" << endl; 
        t = l.substr(6, l_l - 6); 
        sscanf(t.c_str( ), "%d", &ITERATIONS); 
        cout << "ITERATIONS = " << ITERATIONS << endl; 
        return; 
    } else if (l_sub4.compare (ROT) == 0) { 
        t = l.substr(5, l_l - 5);
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
        char a = l[5]; 
        char b = l[7]; 
        cout << "a = " << a << " and b = " << b;
        REPS.insert (pair<char, char> (a,b) ); 
        return; 
    } else if (l.substr(0, 6).compare (START) == 0 ) {
        t = l.substr(7, l_l - 7);
        INIT_C = t[0]; 
        cout << "INIT_STR = " << INIT_C << endl; 
    } else {//production rules
        char F = l[0]; 
        t = l.substr(3, l_l - 3); 
        cout << "F = " << F << " t = " << t << endl;
        PRODUCTION_RULES.insert (pair<char, string> ( F, t ) );
        in_RULES.insert (pair<char, bool> ( F, true ) );
        cout << "here" << endl;
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
        cout << "now here" << endl;
        execute ( ); 
    } else { 
        cout << "The file couldn't open" << endl; 
    }
}
