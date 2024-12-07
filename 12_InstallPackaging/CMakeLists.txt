cmake_minimum_required(VERSION 3.10)
project(guess)

set(CMAKE_C_STANDARD 99)

find_package(Gettext REQUIRED)
find_package(Doxygen)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION /usr/local/share/locale/ PO_FILES po/ru/guess.po)

add_library(guess_lib src/guess.c)
add_executable(guess src/main.c)
target_link_libraries(guess PRIVATE guess_lib)

if(DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/src/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

  add_custom_target(doc_doxygen ALL
     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     COMMENT "Generating API documentation with Doxygen"
     VERBATIM
  )
  add_custom_command(TARGET doc_doxygen POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E rename ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/man3/guess.c.3 ${CMAKE_CURRENT_SOURCE_DIR}/docs/man/man3/guess.3
  COMMENT "Renaming man page"
     )
else()
  message("Doxygen need to be installed to generate the documentation")
endif()

install(TARGETS guess DESTINATION /usr/local/bin/)
install(TARGETS guess_lib DESTINATION /usr/local/lib/)

install(FILES docs/man/man3/guess.3 DESTINATION /usr/local/share/man/man3)

# install(FILES po/ru/LC_MESSAGES/guess.mo DESTINATION /share/locale/ru/LC_MESSAGES)

option(ENABLE_TESTS "Enable making tests" OFF)

if(ENABLE_TESTS)
  enable_testing()
  add_executable(test_guess tests/test_guess.c)
  target_link_libraries(test_guess PRIVATE guess_lib)
  add_test(NAME GuessTest COMMAND test_guess)
endif()
