# FTP Server
Computer Assignment #1, Computer Networks Course, University of Tehran

Implementinga a simple FTP Server and Client using socket programming in C++ language.

The goal is to read the informations of users from config.json and set them into our database
After that any user can log in to its account. Any user as client has some options to do like creating files, deleting files, deleting directories, pwd, changing current directory, downloading files and ...
For the file transfering part, the server checks for the file and sends the data inside it to the client.
All kinds of errors are handled in this process.

## How to  Compile ?
In project repository run `make` command to make project by g++.

## How to run ?
### Server
```bash
./server.out config.json
```
### Client
```bash
./client.out config.json
```
