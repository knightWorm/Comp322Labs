## Lab 1
to build on unix(ubunto)
### Building
```
$ cd comp322Labs/Labs/lab1
$make
```
### Run
```
$cd /Comp322Labs/Labs/Lab1
$ ./time-4-baby-and-me
```
## Log:
 - Directories have been organizd into seperates Directories for different labs.
 - when I was done researching the how to use fork. it turned out that windows did not recognized the fork();
 - I managed to get the subsystem (Ubunto) which supports the fork(); function and also allows me to run theh regular make instead    mingw32-make.
 - Then i fork bombed my laptop... that was fun!
 - finally i was able to the subprocesss running and working as they are supposed to. 
 - the program prints the right information as far as childPId and parent pid are concerned.
 - mot of the program still works fine but i still need to add the last 4 pieces of information. 
 - changed the function's parameters fro pid_t to int so i could pass 0's to the child process handling. 
 - changed time traking system to times() and im using the data structure clocl_t to keep track of individual function time. 
 - reogaized the README.md files for the indivual labs. 
## Summary:
- currrently the system does not display the information for USER, SYS, CUSER, CSYS.
- Everything worlk, except i am not happy for the printing of some of the variables. it returns all 0's istead of the desired values. 
