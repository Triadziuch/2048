# Minimalna wersja CMake
cmake_minimum_required(VERSION 3.15)

# Włączenie vcpkg
set(CMAKE_TOOLCHAIN_FILE "E:/Programy/Program Files/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Nazwa projektu
project(2048)

# Ustawienia C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ścieżki do katalogów z nagłówkami
# Include directories
include_directories(
    include
    assets
    lib
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Dodanie źródeł
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "IEventManager.cpp"
    "TileMatrixModel.cpp"
    "TileModel.cpp"
)

# Wskazanie, które pliki nagłówkowe mają być używane
file(GLOB_RECURSE HEADERS 
    "src/*.h"
    "IEventManager.h"
    "TileMatrixModel.h"
    "TileModel.h"
)

# Wskazanie, że to jest aplikacja
add_executable(2048 ${SOURCES} ${HEADERS})

# Linkowanie bibliotek SFML (zmień nazwę na odpowiednią, jeśli korzystasz z różnych bibliotek)
set(SFML_DIR "lib/cmake/SFML")  # Ścieżka do katalogu CMake dla SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    target_link_libraries(2048 sfml-graphics sfml-window sfml-system)
endif()

# Linkowanie bibliotek FTXUI (jeśli używasz)
find_package(ftxui CONFIG REQUIRED)

if(ftxui_FOUND)
    target_link_libraries(2048 ftxui::dom ftxui::screen ftxui::component)
else()
    message(WARNING "FTXUI not found")
endif()

# Możesz dodać dodatkowe biblioteki tutaj
# target_link_libraries(2048 <nazwa_biblioteki>)