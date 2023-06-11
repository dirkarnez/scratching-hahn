cmake_minimum_required(VERSION 3.18)

project("scratching-hahn")

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

# find_package(portaudio 19 EXACT REQUIRED) # PATHS "P:\\Downloads\\cpp-libraries\\portaudio\\build\\cmake\\portaudio")
find_package(SndFile 1.2.0 EXACT REQUIRED)
find_package(SoundTouch 2.3.1 EXACT REQUIRED)


# IF(portaudio_FOUND)
#     message(STATUS "YES")
# ELSE()
#     message(STATUS "NO")
# ENDIF()

if(SndFile_FOUND)
    message(STATUS "SndFile_FOUND: YES")
else()
    message(STATUS "SndFile_FOUND: NO")
endif()

if(SoundTouch_FOUND)
    message(STATUS "SoundTouch_FOUND: YES")
else()
    message(STATUS "SoundTouch_FOUND: NO")
endif()

add_executable(${PROJECT_NAME}
    "src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} SndFile::sndfile SoundTouch::SoundTouch) # portaudio_static)
