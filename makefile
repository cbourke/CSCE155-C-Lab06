#
# makefile for image and color utilities C library
#
#

CC = gcc -std=gnu99
FLAGS = -Wall
INCLUDES = -lm

imageDriver: imageUtils.o colorUtils.o imageDriver.c
	$(CC) $(FLAGS) $(INCLUDES) imageUtils.o colorUtils.o imageDriver.c -o imageDriver $(INCLUDES)

imageUtils.o: imageUtils.c imageUtils.h
	$(CC) $(FLAGS) $(INCLUDES) -c imageUtils.c -o imageUtils.o

colorUtilsTesterCmocka: colorUtils.o colorUtilsTesterCmocka.c
	$(CC) $(FLAGS) -I./include colorUtils.o colorUtilsTesterCmocka.c -o colorUtilsTesterCmocka $(INCLUDES) -L. -l :libcmocka-static.a

colorUtils.o: colorUtils.c colorUtils.h
	$(CC) $(FLAGS) $(INCLUDES) -c colorUtils.c -o colorUtils.o

clean:
	rm -f *~ *.o

# Very bad workaround:
# 1. d/l cmocka
#  https://cmocka.org/
#  (as of 2021/05/21):
#  https://cmocka.org/files/1.1/cmocka-1.1.5.tar.xz
# 2. extract
# 3. Build (see https://embeddedartistry.com/blog/2017/10/26/building-cmocka-as-a-static-library/):
#    cd cmocka-1.1.5
#    mkdir build
#    cd build
#    cmake ../ -DWITH_STATIC_LIB=true
#    make
# 4. This should build a stand-alone libcmocka-static.a static library
#    located in cmocka-1.1.5/build/src/libcmocka-static.a
# 5. Copy libcmocka-static.a to root project directory
# 6. Copy the include/cmocka.h to the root project directory
# 7. Make file rule:

#colorUtilsTesterCmocka: colorUtils.o colorUtilsTesterCmocka.c
#	$(CC) $(FLAGS) -I./include colorUtils.o colorUtilsTesterCmocka.c -o colorUtilsTesterCmocka $(INCLUDES) -L. -l :libcmocka-static.a
# -I tells gcc where to look for included header files
# -L. tells gcc to Look for libraries in the cwd
# -l :libcmocka-static.a tells gcc to use the *specific* file (the colon prefix)

# include directory:
#  cmocka_pbc.h

#https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
# does not run:l
#  setting LD_LIBRARY_PATH=.:/home/ubuntu/cmocka_build_test/myTest/CSCE155-C-Lab06:$LD_LIBRARY_PATH
#  doesn't work because it still wants to load the symlinks, simply copying them does not work
