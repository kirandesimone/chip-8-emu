CFLAGS:=-std=c++23 -Wall -Wextra -Werror -pedantic-erorrs

run: main.cpp
	gcc++ CFLAGS main.cpp -o main
