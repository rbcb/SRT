# Software Ray Tracer 
A simple ray tracer for Linux

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
SRT uses the GNU auto tools build process, thus install autoconf on your distribution. For example on Arch Linux:
```
$ pacman -S autoconf
```

### Installing
To build a copy of SRT on your machine follow the standard build process:
```
$ ./autogen.sh
...
$ ./configure
...
$ make
...
```
After following this process there will be an ELF executable in the top level directory named srt. To run simply:
```
$ ./srt
```

## Acknowledgments

* libSDL
