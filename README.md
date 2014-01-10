Hook-Game
=========
Pudge-wars stand alone.

Using [allegro5](http://alleg.sourceforge.net/).

#Building

	mkdir build
	cd build
	cmake ..

Debug and release builds can be built as shown below.
Debug builds display extra game info in seperate windows.

	cmake -DCMAKE_BUILD_TYPE=Debug ..
	cmake -DCMAKE_BUILD_TYPE=Release ..

