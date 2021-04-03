# define a header-only library

add_library(cec_benchmark
        include/cec2013/F1.h
        include/cec2013/F2.h
        include/cec2013/F3.h
        include/cec2013/F4.h
        include/cec2013/F5.h
        include/cec2013/F6.h
        include/cec2013/F7.h
        include/cec2013/F8.h
        include/cec2013/F9.h
        include/cec2013/F10.h
        include/cec2013/F11.h
        include/cec2013/F11.h
        include/cec2013/F12.h
        include/cec2013/F13.h
        include/cec2013/F14.h
        include/cec2013/F15.h
        include/cec2013/Benchmarks.h
        include/cec2013/Header.h

        library/F1.cpp
        library/F2.cpp
        library/F3.cpp
        library/F4.cpp
        library/F5.cpp
        library/F6.cpp
        library/F7.cpp
        library/F8.cpp
        library/F9.cpp
        library/F10.cpp
        library/F11.cpp
        library/F11.cpp
        library/F12.cpp
        library/F13.cpp
        library/F14.cpp
        library/F15.cpp
        library/Benchmarks.cpp
        library/random.cpp)


target_include_directories(cec_benchmark PUBLIC include)
target_include_directories(cec_benchmark PRIVATE include/cec2013)

