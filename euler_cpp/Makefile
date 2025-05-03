%: %.cpp 
	g++ -o $@ $< -std=c++17 -Ofast -DLOCAL -Wall -Wextra -Wconversion -Wshadow -Wno-sign-conversion -D_GLIBCXX_DEBUG -fsanitize=undefined,address -fsanitize-undefined-trap-on-error -fno-sanitize-recover=undefined

test:
	./test/test.sh

clean:
	rm -f p[0-9][0-9][0-9][0-9]
