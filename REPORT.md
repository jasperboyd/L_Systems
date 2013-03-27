#Homework 5: L_Systems
####Jasper Boyd

## Overview 

The task for this assignment was to create an OpenGL program that can read and render L Systems. L System is a parallel rewriting systems that allows computers to model plants and other biological structures. 

## Approach

### The Parser

The first task that needed to be completed was the parser. I made this part of a single function __comp_points( )__ which when called would load, parse, execute the L system saving the generated vertices to a *vector*. __comp_points( )__ loads the file that contains the L System. It then passes the file line by line to __parse_line( )__. The data is saved in a number of different variables all are clearly named. Although I used global variables, if I would have had the time too I would have removed them and replaced them with local equivilants. This would have made other tasks much easier, such as clearing the display to render a new L System. Once the parser has completed reading in all the necessary data from the file __execute( )__ would be called to calculate the actual points that were to be displayed.

### The Turtle

Once I had the parser reading in the file correctly the next step was altering the turtle. To represent the turtle I used a class from the tutorial files __MatrixStack__. This class allowed for the turtles postions to be saved when seeing the __' [ '__ char, which indicates to push the current position onto the stack. The class also provided an interface for performing the rotations. The function __execute( )__ goes through the __PRODUCTION_RULES__ char by char performing operations on the __MatrixStack__ based on the rules dictated by L Systems. 

Whenever a new line was drawn I used the __Top ( )__ function in __MatrixStack__ to save the point that was drawn. I made a seperate function to do this called __add_top( )__. Sometimes because of the way the __GL_LINES__ primitive behaves, it was necessary to push the point onto the vector twice, once to finish the current line, and the second time to begin the next line. By creating a seperate __add_top( )__ function I was able to use a boolean argument to dictate whether or not the point needed to be saved twice. This function also calls __update_min_max( )__, which keeps track of the bounds of X, Y, and Z. This is essential because it is required information for displaying the viewport correctly. 

### OpenGL

Once all the vertices had been saved the function __compOrthoProjectionMatrix()__ which uses the aforemented minimum and maximum values to build projection matrix for the program. The function creates a margin of 1 around the entire object that is being rendered. 

From there the __POSITIONS__ *vector* is bound to the *vertex buffer object* and then drawn. From that point the program looks for keyboard input. On a character 'a' - 'e' test cases 1 - 5 would be loaded. The main trick behind this was clearing the program completely and then restarting the process from the beginning. If the space bar is pressed then the next iteration is calculated and similarly if 'r' is pressed then the iteartion is decremented. This part of the program could definitely be optimized. Due to lack of time I implemented this feature by using the already existing __reload( )__ function. This means that everytime the iteration is advanced the entire L System is parsed and executed. To improve it I would have saved iterations in a vector of vectors and simply swapped vectors when the key is pressed.  

## Tests 

My program correctly renders the first 4 tests (with a few slight errors on 3 and 4 due to the projection matrix). I attempted to find the error with the 5th test. I found that the source of the problem had to do with the way __REPS__ is filled in the parser, as well as the way that execute works. To fix these bugs I would have had to rewrite most of my program, which would not have been feasible by the deadline. 

## Some Notes on Style

The style of the program only partially follows the PPP style guide. I intentionally used names that clearly show what functions and variables do to eliminate the need for most comments. Although I did use all-caps for my global variables this was only to discern them from the many other types of variables in the program. However all block statements are formatted correctly. 