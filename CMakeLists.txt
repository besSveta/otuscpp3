cmake_minimum_required(VERSION 3.2)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(allocator allocator.cpp)
add_library(listlib SimpleForwardList.cpp)
add_library(alloclib ListAllocator.cpp)
add_executable(test_allocator allocator_test.cpp)

set_target_properties(allocator listlib  alloclib test_allocator PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(test_allocator PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(allocator 
	listlib  
	alloclib
    Threads::Threads
)

target_link_libraries(test_allocator	
	${Boost_LIBRARIES}
	listlib  
	alloclib
)
	
install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")


set(CPACK_PACKAGE_CONTACT bessveta@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(allocatorTest test_allocator)
