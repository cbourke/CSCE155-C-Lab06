


The good folks in the admin department of CS50 IDE revoked sudoer status of
default ubunut account sometime in early 2021.  As a result, all of the
directives in labs and other handouts that required the installation of
packages (such as cmocka) no longer worked.

It was unlikely that sudoer access would be restored, so the workaround below
was developed.  We didn't want to force students to download and build libraries
from source, so we did most of the work and built a static library and committed
it to the repo (along with the necessary header file).  We updated the makefile
directives to utilize this local static library so that the instructions to
students would still be a single "make" command.

Unfortunately, this is a very bad workaround as it may be necessary to build
and rebuild this library as the CS50 ubuntu image gets updated (or even worse
if students have different ubuntu versions).  Ultimately the awesome CS50 IDE
admins came through and installed most of the libraries we use for CSCE 155E/H
(2021/06/06) and so this workaround is no longer necessary.  However, we've
preserved the step-by-step process in case it becomes necessary or useful in
the future.  The makefile retains the make directive for the workaround as
`colorUtilsTesterCmockaWorkaround`

1. d/l cmocka
 https://cmocka.org/
 (as of 2021/05/21):
 https://cmocka.org/files/1.1/cmocka-1.1.5.tar.xz
2. extract
3. Build (see https://embeddedartistry.com/blog/2017/10/26/building-cmocka-as-a-static-library/):
```
   cd cmocka-1.1.5
   mkdir build
   cd build
   cmake ../ -DWITH_STATIC_LIB=true
   make
```
4. This should build a stand-alone `libcmocka-static.a` static library
   located in `cmocka-1.1.5/build/src/libcmocka-static.a`
5. Copy libcmocka-static.a to root project directory
6. Copy the include/cmocka.h to the root project directory
7. Make file rule:

```
colorUtilsTesterCmockaWorkaround: colorUtils.o colorUtilsTesterCmocka.c
  $(CC) $(FLAGS) -I./include colorUtils.o colorUtilsTesterCmocka.c -o colorUtilsTesterCmocka $(INCLUDES) -L. -l :libcmocka-static.a
```
  * `-I` tells gcc where to look for included header files
  * `-L.` tells gcc to Look for libraries in the cwd
  * `-l :libcmocka-static.a` tells gcc to use the *specific* file (the colon prefix)
