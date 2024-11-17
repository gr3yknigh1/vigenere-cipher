cmake_minimum_required(VERSION 3.20)
project(vigenere-cipher LANGUAGES C)

option(BUILD_TESTS "Build with tests" ON)

add_library(vigenere
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/vigenere.c
  ${CMAKE_CURRENT_SOURCE_DIR}/vigenere.h
)
target_include_directories(vigenere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(vigenere PUBLIC c_std_99)

add_executable(vigenere_cli
  ${CMAKE_CURRENT_SOURCE_DIR}/vigenere_cli.c
)

target_link_libraries(vigenere_cli PRIVATE vigenere)

if(BUILD_TESTS)
  enable_testing()
  find_package(nocheck REQUIRED CONFIG)

  foreach(VIGENERE_TEST_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_basic.c
  )
    get_filename_component(VIGENERE_TEST_NAME ${VIGENERE_TEST_SOURCE} NAME_WE)
    add_executable(${VIGENERE_TEST_NAME} ${VIGENERE_TEST_SOURCE})

    target_link_libraries(
      ${VIGENERE_TEST_NAME}
      PRIVATE nocheck::nocheck
      PRIVATE vigenere
    )

    add_test(${VIGENERE_TEST_NAME} ${VIGENERE_TEST_NAME})
  endforeach()
endif()
