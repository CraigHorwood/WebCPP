set INCLUDE_DIRS=-Isrc -IC:\Libraries\GLFW3\include -IC:\Libraries\glew-2.1.0\include -IC:\Libraries\lodepng
set LIB_DIRS=-LC:\Libraries\GLFW3\lib-mingw
set FLAGS=USE_GLFW=3
set SRC_FILES=src\Main.cpp
set OUTPUT_NAME=webcpp.html

em++ %INCLUDE_DIRS% %LIB_DIRS% %SRC_FILES% C:\Libraries\glew-2.1.0\glew.c C:\Libraries\lodepng\lodepng.cpp -o web\%OUTPUT_NAME% -s %FLAGS%

pause