# lineCount

The scope for this task is to create a small programm which counts all non enmpty lines of file(s) recursivly in a project folder and prints a pretty overview of the different programming languages used an the amount of lines per language.

Therefore will be called from the command line and gets one or multiple folders as argument:
```bash
$ linecount home/user/project1/ ~/project2/ 
```
A possible print can look like this:
```bash
$ linecount home/user/project1/

******** Line Count Project 1 ********
Language:   %:      Lines:      Files:
html        10%     1000        5
css         5%      500         15
JavaScript  30%     3000        29
C           5%      500         1
C++         50%     5000        50

Sum         100%    10000       100
**************************************
```
The programm should return the following:
-   Sum of the all non empty lines and files.
-   List of all found languages their percentage, line count and file count.

LineCount should support the usual programming languages such as: C, C++, HTML, CSS, JavaScript, TypeScript, Rust, PHP, Python, Java and C#. Feel free to add additional support. The differentiation can be done by the file extension.

The programm should always check for potential errors wherever reasonable and return with an error code and when applicable error print.

Helpful functions:
```C
perror(), chdir(), opendir(), readdir()
```