# MathLib/src/CMakeLists.txt

# Gather module folders, filling MATHLIB_SOURCES & MATHLIB_HEADERS
add_subdirectory(Common)
add_subdirectory(Types)

# List main headers
set(MATHLIB_HEADERS ${MATHLIB_HEADERS}
    ${CMAKE_SOURCE_DIR}/include/MathLib/MathLib.h
    ${CMAKE_SOURCE_DIR}/include/MathLib/Version.h
)

# List main private headers
# set(MATHLIB_HEADERS_PRIVATE ${MATHLIB_HEADERS_PRIVATE}
#    ${CMAKE_SOURCE_DIR}/private/PrivateHelpers.h
#    PARENT_SCOPE
# )

# Create library from accumulated list
add_library(MathLib STATIC ${MATHLIB_SOURCES} ${MATHLIB_HEADERS} ${MATHLIB_HEADERS_PRIVATE})

# Include directories
target_include_directories(MathLib PUBLIC  ${CMAKE_SOURCE_DIR}/include)
target_include_directories(MathLib PRIVATE ${CMAKE_SOURCE_DIR}/private)


# Groups IDE

function(assign_filter FILE ROOT GROUP_ROOT)
    file(RELATIVE_PATH rel "${ROOT}" "${FILE}")
    get_filename_component(dir "${rel}" PATH)

    if(dir STREQUAL "")
        set(group "${GROUP_ROOT}")
    else()
        string(REPLACE "/" "\\" subdir "${dir}")
        set(group "${GROUP_ROOT}\\${subdir}")
    endif()

    source_group("${group}" FILES "${FILE}")
endfunction()



foreach(f ${MATHLIB_SOURCES})
    assign_filter("${f}" "${CMAKE_SOURCE_DIR}/src" "Source Files")
endforeach()

foreach(f ${MATHLIB_HEADERS})
    assign_filter("${f}" "${CMAKE_SOURCE_DIR}/include/MathLib" "Header Files\\include\\MathLib")
endforeach()

foreach(f ${MATHLIB_HEADERS_PRIVATE})
        assign_filter("${f}" "${CMAKE_SOURCE_DIR}/private" "Header Files\\private")
endforeach()
