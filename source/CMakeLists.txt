target_sources(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/diskio.c)
target_sources(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ff.c)
target_sources(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ffsystem.c)
target_sources(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ffunicode.c)

# target_sources(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fatfs_sdram.c)

target_include_directories(fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})