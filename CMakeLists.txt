cmake_minimum_required(VERSION 3.10)

project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(Tetris main.cpp)

target_sources(Tetris PRIVATE
	game_logic.cpp
	rendering.cpp
)

target_link_libraries(Tetris PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)

set(TETRIS_RUNTIME_DLLS
	"C:/msys64/ucrt64/bin/libfreetype-6.dll"
	"C:/msys64/ucrt64/bin/libharfbuzz-0.dll"
	"C:/msys64/ucrt64/bin/libbrotlidec.dll"
	"C:/msys64/ucrt64/bin/libbrotlicommon.dll"
	"C:/msys64/ucrt64/bin/libgcc_s_seh-1.dll"
	"C:/msys64/ucrt64/bin/libbz2-1.dll"
	"C:/msys64/ucrt64/bin/libpng16-16.dll"
	"C:/msys64/ucrt64/bin/zlib1.dll"
	"C:/msys64/ucrt64/bin/libwinpthread-1.dll"
	"C:/msys64/ucrt64/bin/libstdc++-6.dll"
	"C:/msys64/ucrt64/bin/libgraphite2.dll"
	"C:/msys64/ucrt64/bin/libglib-2.0-0.dll"
	"C:/msys64/ucrt64/bin/libintl-8.dll"
	"C:/msys64/ucrt64/bin/libpcre2-8-0.dll"
	"C:/msys64/ucrt64/bin/libiconv-2.dll"
)

foreach(runtimeDll IN LISTS TETRIS_RUNTIME_DLLS)
	add_custom_command(TARGET Tetris POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${runtimeDll}"
			$<TARGET_FILE_DIR:Tetris>
	)
endforeach()