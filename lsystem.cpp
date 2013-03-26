#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"

// include glm for vec and mat related data structures and computation
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))


GLuint theProgram; //the handle to the shade program
GLuint offsetLocation, elapsedTimeUniform;

char SPACE = ' ';
char INIT_C;

std::string LEN = "len:";
std::string ITER = "iter:";

std::string ROT = "rot:";
std::string REP = "rep:";
std::string START = "start:";

std::map<char, std::string> PRODUCTION_RULES;
std::map<char, char> REPS;
std::map<char, bool> in_RULES;

std::vector<float> ROTATIONS;
std::vector<vec4> ITER_COPY; 
std::vector<vec4> POSITIONS; 


int ITERATIONS;
int POINTS_COUNT = 0;
float SEG_LEN;
float XMIN = 0; 
float YMIN = 0; 
float ZMin = 0; 
float XMAX = 0; 
float YMAX = 0; 
float ZMAX = 0; 

vec3 T_MAT;

inline float DegToRad(float fAngDeg)
{
    const float fDegToRad = 3.14159f * 2.0f / 360.0f;
    return fAngDeg * fDegToRad;
}

glm::mat3 RotateX(float fAngDeg)
{
    float fAngRad = DegToRad(fAngDeg);
    float fCos = cosf(fAngRad);
    float fSin = sinf(fAngRad);

    glm::mat3 theMat(1.0f);
    theMat[1].y = fCos; theMat[2].y = -fSin;
    theMat[1].z = fSin; theMat[2].z = fCos;
    return theMat;
}

glm::mat3 RotateY(float fAngDeg)
{
    float fAngRad = DegToRad(fAngDeg);
    float fCos = cosf(fAngRad);
    float fSin = sinf(fAngRad);

    glm::mat3 theMat(1.0f);
    theMat[0].x = fCos; theMat[2].x = fSin;
    theMat[0].z = -fSin; theMat[2].z = fCos;
    return theMat;
}

glm::mat3 RotateZ(float fAngDeg)
{
    float fAngRad = DegToRad(fAngDeg);
    float fCos = cosf(fAngRad);
    float fSin = sinf(fAngRad);

    glm::mat3 theMat(1.0f);
    theMat[0].x = fCos; theMat[1].x = -fSin;
    theMat[0].y = fSin; theMat[1].y = fCos;
    return theMat;
}

class MatrixStack
{
    public:
        MatrixStack( )
            : m_currMat(1.0f)
        {
        }

        const glm::mat4 &Top()
        {
            return m_currMat;
        }

        void RotateX(float fAngDeg)
        {
            m_currMat = m_currMat * glm::mat4(::RotateX(fAngDeg));
        }

        void RotateY(float fAngDeg)
        {
            m_currMat = m_currMat * glm::mat4(::RotateY(fAngDeg));
        }

        void RotateZ(float fAngDeg)
        {
            m_currMat = m_currMat * glm::mat4(::RotateZ(fAngDeg));
        }

        void Scale(const glm::vec3 &scaleVec)
        {
            glm::mat4 scaleMat(1.0f);
            scaleMat[0].x = scaleVec.x;
            scaleMat[1].y = scaleVec.y;
            scaleMat[2].z = scaleVec.z;

            m_currMat = m_currMat * scaleMat;
        }

        void Translate(const glm::vec3 &offsetVec)
        {
            glm::mat4 translateMat(1.0f);
            translateMat[3] = glm::vec4(offsetVec, 1.0f);

            m_currMat = m_currMat * translateMat;
        }

        void Push( )
        {
            m_matrices.push(m_currMat);
        }

        void Pop( )
        {
            m_currMat = m_matrices.top();
            m_matrices.pop();
        }

        void Print( )
        {
            std::cout << "adding: " << " X = " << m_currMat[3][0]
                << " Y = " << m_currMat[3][1]
                << " Z = " << m_currMat[3][2]  
                << std::endl;
        }

    private:
        glm::mat4 m_currMat;
        std::stack<glm::mat4> m_matrices;
};

MatrixStack turtle;

void execute_char ( char c ) {
    if (c == INIT_C) {
        turtle.Translate(T_MAT);
        turtle.Print( );
        mat4 temp = turtle.Top( );
        vec4 to_add = vec4 (temp[3][0], temp[3][1], temp[3][2], 1.0f);
        POSITIONS.push_back(to_add);
    } else if (c == '[') {
        turtle.Push();
    } else if (c == ']') {
        turtle.Pop();
        mat4 temp = turtle.Top( );
        vec4 to_add = vec4 (temp[3][0], temp[3][1], temp[3][2], 1.0f);
        POSITIONS.push_back(to_add); 
    } else if (c == '+') {
        turtle.RotateZ(ROTATIONS[2]);
    } else if (c == '-') {
        turtle.RotateZ(-ROTATIONS[2]);
    } else if (c == '&') {
        turtle.RotateY(ROTATIONS[1]);
    } else if (c == '^') {
        turtle.RotateY(-ROTATIONS[1]);
    } else if (c == '/') {
        turtle.RotateX(ROTATIONS[0]);
    } else if (c == '\\') {
        turtle.RotateX(-ROTATIONS[0]);
    } else if (c == '|') {
        turtle.RotateX( 180.0f );
    }//if/else
}//process_char

void execute_line ( std::string l ) {
    std::cout << "execute_line ( )" << std::endl;
    int l_l = l.length( );
    
    for ( int i = 0; i < l_l; i++ ) {
        execute_char ( l[i] );
    }
}//execute_line

std::string process_char ( char c ) {
    //assume correct input
    std::cout << "proccessing char " << c << std::endl;
    std::stringstream ss;
    std::string a;
    ss << c;
    ss >> a;
    if ( c == INIT_C) {
        return PRODUCTION_RULES.at ( c );
    } else {
        return a;
    }
}//process_char

std::string next_iter ( std::string l ) {
    std::cout << "next_iter ( " << l << " )" << std::endl;
    int l_l = l.length ( );
    std::string answer = "";
    for ( int i = 0; i < l_l; i++ ) {
        answer += process_char ( l[i] );
    }
    std::cout << "answer " << answer << std::endl;
    return answer;
}//next_iter

void execute ( ) {
    std::cout << "execute ( )" << std::endl;
    std::string current_str = PRODUCTION_RULES.at(INIT_C);
    for (int i = 0; i < ITERATIONS; i++) {
        std::cout << "Beginning Iteration: " << i << std::endl;
        execute_line( current_str );
        current_str = next_iter ( current_str );
    }//for
}//execute

void process_line ( std::string l ) {
    std::cout << "process_line ( )" << std::endl;
    std::string t; 
    
    int l_l = l.length( );
    if ( l_l == 0){
        return;
    }
    
    std::string l_sub4 = l.substr(0, 4);
    
    if (l[0] == '#') {
        return; //ignore comment
    } else if ( l_sub4.compare ( LEN ) == 0 ) {
        std::cout << "length" << std::endl;
        t = l.substr ( 5, l_l - 5 );
        sscanf( t.c_str ( ), "%d", &SEG_LEN );
        //T_MAT = vec3 (0.0f, SEG_LEN, 0.0f);
        T_MAT = vec3 (0.0f, 0.05f, 0.0f);
        return;
    } else if (l.substr(0, 5).compare (ITER) == 0) {
        std::cout << "iter" << std::endl;
        t = l.substr(6, l_l - 6);
        sscanf(t.c_str( ), "%d", &ITERATIONS);
        std::cout << "ITERATIONS = " << ITERATIONS << std::endl;
        return;
    } else if (l_sub4.compare (ROT) == 0) {
        t = l.substr(5, l_l - 5);
        int count = 0;
        float current;
        std::string c = "";
        int t_l = t.length( );
        for (int i = 0; i < t_l; i++){
            if (t[i] == SPACE) {
                current = (float) ::atof(c.c_str( ));
                std::cout << "ROT current = " << current << std::endl;
                ROTATIONS.push_back(current);
                count = 0;
                c = "";
            } else {
                c += t[count++];
            }//if/else
        }//for
        //remove below and turn into while loop for opti
        current = (float) ::atof(c.c_str( ));
        std::cout << "ROT current = " << current << std::endl;
        ROTATIONS.push_back(current);
        return;
    } else if (l_sub4.compare (REP) == 0) {
        std::cout << "rep" << std::endl;
        char a = l[5];
        char b = l[7];
        std::cout << "a = " << a << " and b = " << b;
        REPS.insert (std::pair<char, char> (a,b) );
        return;
    } else if (l.substr(0, 6).compare (START) == 0 ) {
        t = l.substr(7, l_l - 7);
        INIT_C = t[0];
        std::cout << "INIT_STR = " << INIT_C << std::endl;
    } else {//production rules
        char F = l[0];
        t = l.substr(3, l_l - 3);
        std::cout << "F = " << F << " t = " << t << std::endl;
        PRODUCTION_RULES.insert (std::pair<char, std::string> ( F, t ) );
        in_RULES.insert (std::pair<char, bool> ( F, true ) );
        std::cout << "here" << std::endl;
    }//if/else
}//process_line

void compPoints()
{
    std::string line;
    std::string filename = "test/lsys2";
    filename = filename + ".txt";
    std::cout << filename << std::endl;
    std::ifstream in (filename.c_str());
    if (in.is_open ( ) ) {
        std::cout << "File is open" << std::endl;
        start = false;
        POSITIONS.push_back( vec4(0.0f, 0.0f, 0.0f, 1.0f) );
        ITER_COPY.push_back( vec4(0.0f, 0.0f, 0.0f, 1.0f) ); 
        while(in.good ( ) ) {
            getline (in, line);
            process_line (line);
        }
        execute ( );
    } else {
        std::cout << "The file couldn't open" << std::endl;
    }
}

//initialize the shader program
void InitializeProgram()
{
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "DirectPoints.vert"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "WhiteColor.frag"));

    theProgram = Framework::CreateProgram(shaderList);

    elapsedTimeUniform = glGetUniformLocation(theProgram, "time");

    GLuint loopDurationUnf = glGetUniformLocation(theProgram, "loopDuration");
    glUseProgram(theProgram);
    glUniform1f(loopDurationUnf, 5.0f);
    glUseProgram(0);

}

/*
   create and initialize and VBO for Gasket point coordinates
   */
GLuint  POSITIONSVBO; // VBOs for point positional data
void InitializeVertexBuffer()
{
    glGenBuffers(1, &POSITIONSVBO);

    glBindBuffer(GL_ARRAY_BUFFER, POSITIONSVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(POSITIONS), POSITIONS, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint vao;
void init()
{
    InitializeProgram(); 

    compPoints();

    InitializeVertexBuffer(); 

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(theProgram);

    glUniform1f(elapsedTimeUniform, glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

    glBindBuffer(GL_ARRAY_BUFFER, POSITIONSVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,       	
            4,       	
            GL_FLOAT,	
            GL_FALSE,	
            0,       	
            (void*)0 	
            );

    glDrawArrays(GL_LINES, 0, NUM_OF_POINTS); 

    glDisableVertexAttribArray(0);
    glUseProgram(0);

    //request the drawing in the window and thus make "new" framebuffer content appear
    glutSwapBuffers();
    glutPostRedisplay();
}

/* This is the reshape callback function.
   It uses the whole window area as the viewport and
   does not preserve the aspect ratio.
   */
void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


/* This is the keyboard callback function.
   It allows the program to be terminated by the escape key (ASCII value 27).
   */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            glutLeaveMainLoop();
            return;
    }
}

//used by framework.cpp
unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}


