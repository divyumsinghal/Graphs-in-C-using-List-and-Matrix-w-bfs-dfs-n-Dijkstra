cmake_minimum_required(VERSION 3.15)


project(Graphs C)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(DATA_DIR ${CMAKE_SOURCE_DIR}/db)

set(CSV_FILES
    ${DATA_DIR}/vertices.csv
    ${DATA_DIR}/edges.csv
)

foreach(file ${CSV_FILES})
    configure_file(${file} ${CMAKE_BINARY_DIR}/db COPYONLY)
endforeach()

add_executable( task1
				t1.h
				t1.C
				t1_test.C
)


add_executable( task2
				t2.h
				t2.C
				t2_test.C
)

add_executable( task3
				t3.h
				t3.C
				t3_test.C
				${CMAKE_BINARY_DIR}/db/vertices.csv
				${CMAKE_BINARY_DIR}/db/edges.csv
)


add_executable( task4
				t4.h
				t4.C
				t4_test.C
				${CMAKE_BINARY_DIR}/db/vertices.csv
				${CMAKE_BINARY_DIR}/db/edges.csv
)

 find_package(jansson CONFIG REQUIRED)
 find_package(curl CONFIG REQUIRED)

add_executable( try
				main.c
)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(try PRIVATE CURL::libcurl)
  target_link_libraries(try PRIVATE jansson::jansson)