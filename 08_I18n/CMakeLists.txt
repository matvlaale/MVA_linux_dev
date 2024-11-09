cmake_minimum_required(VERSION 3.0)
project(guess)

find_package(Gettext REQUIRED)

GETTEXT_PROCESS_PO_FILES(ru ALL INSTALL_DESTINATION po PO_FILES po/ru/guess.po)
GETTEXT_PROCESS_PO_FILES(ro ALL INSTALL_DESTINATION po PO_FILES po/ro/guess.po)

add_executable(guess guess.c)

install(TARGETS guess DESTINATION ${CMAKE_INSTALL_PREFIX})
