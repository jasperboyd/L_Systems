#include <fstream> 
#include <iostream> 
#include <string> 
#include <map> 
#include <vector> 
using namespace std; 

// +(theta) turn left by angle theta 
// -(theta) turn right by angle theta
// &(theta) pitch down by angle theta
// ^(theta) pitch up by angle theta 
// /(theta) roll left by angle theta
// \(theta) roll right by angle theta
// | is equivalent to +(180) -(180) 
void process_line ( string l ) { 
       
}

int main ( ) {
    string line; 
    string filename = "test/lsys1";
    filename = filename + ".txt"; 
    cout << filename << endl;
    ifstream in (filename.c_str()); 
    if (in.is_open ( ) ) {
        cout << "A OKAY" << endl;
        while(in.good ( ) ) {
            getline (in, line); 

        }
    } else { 
        cout << "There was a problem" << endl; 
    }
}
