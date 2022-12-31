# C Path Manager

## Overview

The C Path Manager is a small program (primarily intended for Linux machines) to keep track of a user's most commonly consulted directory or file paths. The program makes use of the Redis database and the C programming language to keep track of users' path preferences, and can be used in conjunction with other Linux commands.

## Installation

To use this program, the user **must** have the following installed:
* clang
* make
* redis
* hiredis

After this, the user must perform the following steps:

```shell
git clone URL
cd c-path-manager
make
```

By default, the name of the executable should be "cm". Feel free to change this to whatever you wish afterwards. To run the program, the user can simply run (with arguments, explained later):

```shell
./cm
```

In a later section, "Usage - Applications", this guide goes over potential use cases for this program.

## Usage - Commands

The following are valid commands for the program. Some of the commands may require ```KEY``` or ```PATH``` or both. These are mandatory arguments, and should be inserted correctly. All of the commands feature optional arguments to pass in a specific ```HOST``` and ```PORT``` to the Redis connection. By default (when no optional arguments passed in), the host and port arguments are set to "127.0.0.1" and 6379, respectively.

### Setting a path

The following command sets a PATH to a user-defined KEY:

```shell
cm set KEY PATH [HOST] [PORT]
```

Theoretically, KEY can be any valid term, but it may be more convenient for a user to use a key that is short. For instance, to save the "/home" directory with a key "home", perform the following command:

```shell
cm set home /home
```

If you want to save the current directory path to a key, pass in "." like so:

```shell
cm set home .
```

Note that this program does not know how to handle (at least, not yet) replacing the "." character with the current directory. As such, any folders in the current directory **cannot** be added like so:

```shell
cm set home ./someDirInsideHome
```

To update a key's path, pass in the same key, but a different path:

```shell
cm set home /home/Documents
```

### Getting a path

To output a path, pass in an existing KEY to this command:

```shell
cm get KEY [HOST] [PORT]
```

### Removing a path

To delete a KEY and its corresponding path, pass in an existing KEY to this command:

```shell
cm remove KEY [HOST] [PORT]
```

### Listing all saved paths

To list all keys and their saved paths, call the following command:

```shell
cm list [HOST] [PORT]
```

### Resetting all data

To remove all saved directories, call the following command:

```shell
cm reset [HOST] [PORT]
```

## Usage - Applications

1. Quickly changing directories
Given the nature of this program, one may find it useful to combine this program with other Linux commands. For instance, a powerful way a user can make use of this program is to quickly change to a preferred directory. In order to do so, a user may save the executable program path to an alias, or perhaps (specifically for Ubuntu) sudo copy the program to the /usr/local/bin directory. Then, the user can call the alias or copied program with the "cd" program like so:

```shell
cd $(cm get KEY)
```

2. Quickly opening a file
Since the program simply takes in paths and does not check if the path refers to a file or directory, one can use this program to quickly access and/or edit files. For instance, to call nano on .bashrc quickly, one can perform the follwing commands:

```shell
cm set bashrc ~/.bashrc

cd (to some other directory far from .bashrc)

nano $(cm get bashrc)
```
