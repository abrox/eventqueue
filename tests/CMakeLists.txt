

add_executable (tests main.cpp tests.cpp)
find_library(UNIT_TEST_LIB libUnitTest++.a )
message(STATUS ${UNIT_TEST_LIB})
target_link_libraries (tests ${UNIT_TEST_LIB})

