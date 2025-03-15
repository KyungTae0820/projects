## GDB to the rescue

Whenever you get a segmentation fault (which will be a lot in your CS career), you can use GDB to find the line of code causing it. Open the executable in `gdb`:
```
gdb stringdemo
```
At the gdb prompt just type the following to run the program in the debugger. 
```
run
```

When it crashes in gdb, type
```
backtrace
```

This will show you the function calls (and line numbers). You should see that the last function that you recognize (i.e. you wrote) is `main()` at `stringdemo.cpp:14`. 

```
... in main () at stringdemo.cpp:14
```

This means `main()` called some other function at line 14 and that other function triggered the error. So this can always be used to tell you where your segmentation fault is.

**Note:** If you didn’t get a line number, maybe you forgot the `-g` when calling `g++`. That option turns on the debugging information and line number tracking. Compile again with `g++ -g`)

So let's now comment out line 14:
```
// strncpy(astring, mystring, 80);
```

quit GDB, recompile and run the code
