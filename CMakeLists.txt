project(ethereum)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_AUTOMOC ON)

cmake_policy(SET CMP0015 NEW)

# Default HEADLESS to 0.
set(HEADLESS CACHE BOOL 0)
if ("x${HEADLESS}" STREQUAL "x")
	set(HEADLESS 0)
endif ()

# Default TARGET_PLATFORM to "linux".
set(TARGET_PLATFORM CACHE STRING "linux")
if ("x${TARGET_PLATFORM}" STREQUAL "x")
	set(TARGET_PLATFORM "linux")
endif ()

if ("${TARGET_PLATFORM}" STREQUAL "linux")
	set(CMAKE_THREAD_LIBS_INIT pthread)
endif ()

if ("${TARGET_PLATFORM}" STREQUAL "w64")
	set(CMAKE_SYSTEM_NAME Windows)

	set(CMAKE_CXX_LIBRARY_ARCHITECTURE	x86_64-w64-mingw32)
	set(CMAKE_C_COMPILER			x86_64-w64-mingw32-gcc)
	set(CMAKE_CXX_COMPILER			x86_64-w64-mingw32-g++)
	set(CMAKE_RC_COMPILER			x86_64-w64-mingw32-windres)
	set(CMAKE_AR				x86_64-w64-mingw32-ar)
	set(CMAKE_RANLIB			x86_64-w64-mingw32-ranlib)

	set(CMAKE_EXECUTABLE_SUFFIX		.exe)

	set(CMAKE_FIND_ROOT_PATH
		/usr/x86_64-w64-mingw32
	)

	set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
	set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
	set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

	set(CMAKE_INSTALL_PREFIX	/usr/x86_64-w64-mingw32)
	set(ETH_BUILD_PLATFORM "windows")
else ()
	set(ETH_BUILD_PLATFORM ${CMAKE_SYSTEM_NAME})
endif()

if (CMAKE_COMPILER_IS_MINGW)
	set(ETH_BUILD_PLATFORM "${ETH_BUILD_PLATFORM}/mingw")
elseif (CMAKE_COMPILER_IS_MSYS)
	set(ETH_BUILD_PLATFORM "${ETH_BUILD_PLATFORM}/msys")
elseif (CMAKE_COMPILER_IS_GNUCXX)
	set(ETH_BUILD_PLATFORM "${ETH_BUILD_PLATFORM}/g++")
elseif (CMAKE_COMPILER_IS_MSVC)
	set(ETH_BUILD_PLATFORM "${ETH_BUILD_PLATFORM}/msvc")
else ()
	set(ETH_BUILD_PLATFORM "${ETH_BUILD_PLATFORM}/unknown")
endif ()

# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "-std=c++11 -Wall -Wno-unknown-pragmas -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

aux_source_directory(. SRC_LIST)

include_directories(/opt/cpp-ethereum)
link_directories(/opt/cpp-ethereum/libethereum)

add_executable(ethcomp ${SRC_LIST})

if (${TARGET_PLATFORM} STREQUAL "w64")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
	target_link_libraries(ethcomp gcc)
	target_link_libraries(ethcomp gdi32)
	target_link_libraries(ethcomp ws2_32)
	target_link_libraries(ethcomp mswsock)
	target_link_libraries(ethcomp shlwapi)
	target_link_libraries(ethcomp iphlpapi)
	target_link_libraries(ethcomp boost_system-mt-s)
	target_link_libraries(ethcomp boost_thread_win32-mt-s)
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
else ()
	target_link_libraries(ethcomp boost_system)
	#target_link_libraries(ethcomp ${CMAKE_THREAD_LIBS_INIT})
endif ()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	include_directories(/usr/local/include)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

install( TARGETS ethcomp DESTINATION bin )
