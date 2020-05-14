## Lab 0
to build on Windows

### Building
```
$ cd Labs/zero
$ mingw32-make
```
to build on Unix: 
```
$ cd Labs/zero
$ make 
```
### Run

You can pass binary through stdin 
``` 
$ cd Labs/zero
$ run 11111111 00000000 11111111
``` 

Or pass in a file
```
$ cd Labs/zero
$ run - data.txt
```
## Log:
- i tried several methods but most of them did not work properly or were poorly coded. 
- i had to learned how to properly indent my programs
- My code had to be optimized, so there was a lot of research, mostly just to get started. 
- one of my  goals was to keep it under 125 lines of code. after fixing the indentations and restructure my code. that goal was out of the window.
 - i had trouble with the valid input. 
 - there is an option called access(); which will have check if the provided infofrmation is a file. i decided to create my own function for that. however, for that i had to use fopen(); which i was not aloow to use in order to hanle the file. howevver, i used it to check if the given data was a file name. 
 - i also had to learn to use git from the command line. 
 i wanted to go back and run the code for one finla check before submission, and my pow function in the binarytoInt fuction did not work. after some research i figured out that the linker was not recognizing the function. so i had to change the Makefile to: gcc -o cat lab0.c -lm
 also i notices that the makefile did not have the right name as an output: i cahnged that from ron to cat.
 ## Summary: 
- the code work almost 100% however, i did not have enough time to pad zero to the right when the data is given  through stdin. but it does work when it comes from a file. 
