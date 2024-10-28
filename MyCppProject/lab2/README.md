Инструкция по пользованию лабой:

Находясь в директории MyCppProject пишем

cmake -G "MinGW Makefiles"
mingw32-make
.\gtests.exe       
А если хотим запустить main_lab1_16.cpp (то есть проверить работу с вводом данных через консоль), то пишем:

cmake -G "MinGW Makefiles" (если не писали ранее)
mingw32-make (если не писали ранее)
.\test_exe.exe