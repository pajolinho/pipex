# Pipex 
The **Pipex** project at École 42 is about recreating the behavior of a shell pipeline (`|`) in C.  
Given two commands and an input/output file, the program redirects the data so that the **output of the first command** becomes the **input of the second**, just like in Bash:  

```bash
$ < infile cmd1 | cmd2 > outfile
