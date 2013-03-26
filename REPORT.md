#Homework 5: L_Systems

__Jasper Boyd__

## Overview 

The task for this assignment was to create an opengl program that can read and render L Systems. 

## Approach

The first task that needed to be completed was the parser. This was fairly straightforward and required only if statements and a single loop parsing the text file line by line.

Once I had the parser reading in the file correctly the next step was altering the turtle. To represent the turtle I used a class from the tutorial files __MatrixStack__. This class allowed for the turtles postions to be saved when seeing the __' [ '__ char. It also allowed for the rotations to be applied to the position. 

From the __MatrixStack__ I was able to retrieve the current postion by using the __Top ( )__ function. This was then handed off to the *vector* of __vec4__ objects. Which is then bound into a *vertex buffer object*. 

## Tests 

Test cases for this project were supplied as part of the project file. 