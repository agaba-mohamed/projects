cmake_minimum_required(VERSION 3.15)
project(rtype_server)



set(CMAKE_TOOLCHAIN_FILE "./conan_toolchain.cmake")

# Specify the version of C++ you want to use (C++11, C++14, C++17, etc.)
set(CMAKE_CXX_STANDARD 17)

# Specify the source files for the server
set(SERVER_SOURCES
    src/Server/mainServer.cpp
)

set(SFML_DIR "build")

set(opengl_system_DIR "build")


set(freetype_DIR "build")

set(PNG_DIR "build")

set(ZLIB_DIR "build")

set(BZip2_DIR "build")

set(brotli_DIR "build")

set (stb_DIR "build")

set(flac_DIR "build")

set(Ogg_DIR "build")

set(OpenAL_DIR "build")

set(Vorbis_DIR "build")
# In your CMakeLists.txt file
add_definitions(-D_WIN32_WINNT=0x0601)
if(WIN32)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
endif()
set(ASIO_DIR "build")
# Create the executable for the server
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(rtype_server ${SERVER_SOURCES})
include (conan_toolchain.cmake)


# Specify the source files for the client
find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
find_package(ASIO REQUIRED)
file(GLOB CLIENT_SOURCES "src/Client/mainCli.cpp")

# Create the executable for the client
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(rtype_client ${CLIENT_SOURCES})

add_executable(map_builder src/editor.cpp)


target_include_directories(rtype_server PRIVATE ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIRS})

target_include_directories(rtype_client PRIVATE ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIRS})


include_directories(${CONAN_INCLUDE_DIRS_ASIO})

target_link_libraries(rtype_server sfml-graphics sfml-audio sfml-window sfml-system ${CONAN_LIBS_SFML} ${asio_LIBRARIES})
target_link_libraries(rtype_client sfml-graphics sfml-audio sfml-window sfml-system ${CONAN_LIBS_SFML} ${asio_LIBRARIES})
if(linux)
target_link_libraries(rtype_server dl)
target_link_libraries(rtype_client dl)
endif()
# Link ASIO libraries for the client

target_link_libraries(map_builder sfml-graphics sfml-audio sfml-window sfml-system ${CONAN_LIBS_SFML} ${asio_LIBRARIES})
# Rajoute pthread pour le serveur et le client
find_package(Threads REQUIRED)
target_link_libraries(rtype_server Threads::Threads)
target_link_libraries(rtype_client Threads::Threads)
install(TARGETS rtype_server rtype_client
    RUNTIME DESTINATION bin
)

install(DIRECTORY assets/
    DESTINATION assets
)

set(SHARED_LIBRARIES
    player
    enemy
    bullet
    tele_bullet
    tele_enemy
    random_bullet
    sinu_bullet
    rotate_bullet
    chase_bullet
    chase_enemy
    random_enemy
)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")

foreach(LIBRARY ${SHARED_LIBRARIES})
    add_library(${LIBRARY} SHARED
        ../scripts/${LIBRARY}.cpp
    )

    target_link_libraries(${LIBRARY}
        sfml-graphics
        sfml-audio
        sfml-window
        sfml-system
    )
    target_include_directories(${LIBRARY} PRIVATE  ${SFML_INCLUDE_DIR} ${asio_INCLUDE_DIRS})
    set_target_properties(${LIBRARY} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../libs"
    )
endforeach()
set(CPACK_PACKAGE_NAME "rtype_server_client")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "LADOUILLEFC")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "RType Server and Client")


include(CPack)
