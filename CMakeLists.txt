cmake_minimum_required(VERSION 3.25)

project(fs)

# add_executable(fs test/app1.c)
add_executable(fs test/app2.c test/fatfs_sdram.c)


add_subdirectory(source)