cmake_minimum_required(VERSION 3.26)
project(toys)

function(CPMInitialize)
    set(CPM_DOWNLOAD_VERSION 0.38.2)

    if(CPM_SOURCE_CACHE)
        set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    elseif(DEFINED ENV{CPM_SOURCE_CACHE})
        set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    else()
        set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    endif()

    if(NOT(EXISTS ${CPM_DOWNLOAD_LOCATION}))
        message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
        file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION}
        )
    endif()

    include(${CPM_DOWNLOAD_LOCATION})
endfunction()

CPMInitialize()
CPMAddPackage(
    NAME nlohmann_json
    VERSION 3.11.2
    GITHUB_REPOSITORY nlohmann/json
    OPTIONS
    "JSON_BuildTests OFF"
)

add_executable(main)
target_sources(main
PRIVATE
    toys/main.cpp
)
target_link_libraries(main
PRIVATE
    nlohmann_json
)

function(copy_to_binary_directory __TARGET__)
    add_custom_command(TARGET ${__TARGET__} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/bin/"$<TARGET_FILE_NAME:${__TARGET__}>"
        COMMAND ${CMAKE_COMMAND} -E copy  "$<TARGET_FILE:${__TARGET__}>" ${CMAKE_BINARY_DIR}/bin
    )
endfunction()

copy_to_binary_directory(main)
