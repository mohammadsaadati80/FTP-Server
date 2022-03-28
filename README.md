# FTP Server
Computer Assignment 1, Computer Networks Course, University of Tehran

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
## Supported Commands

| Template            | Example          | Description                                  |
| ------------------- | ---------------- | -------------------------------------------- |
| user "username"     | user Ali         | enter username for authentication            |
| pass "password"     | pass 1234        | enter password for authentication            |
| pwd                 | pwd              | get current working directory                |
| mkd "directory"     | mkd temp         | create new directory with provided name      |
| dele -f "filename"  | dele -f temp_f   | delete file with provided name               |
| dele -d "dirpath"   | dele -d temp_d   | delete directory with provided name          |
| ls                  | ls               | get files and directories in pwd             |
| cwd "new path"      | cwd new_path     | change current working directory to new_path |
| rename "from" "to"  | rename old new   | rename file from old name to new name        |
| retr "filename"     | retr config.json | download a file                              |
| help                | help             | get help message for commands                |
| quit                | quit             | logout from account                          |
