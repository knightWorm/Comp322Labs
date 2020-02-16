# Comp322Labs

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
 ## Summary: 
- the code work almost 100% however, i did not have enough time to pad zero to the right when the data is given  through stdin. but it does work when it comes from a file. 
