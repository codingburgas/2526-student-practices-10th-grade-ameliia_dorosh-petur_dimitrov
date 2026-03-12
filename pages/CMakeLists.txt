add_library(pages STATIC
    logandregisterpage.cpp
    logandregisterpage.h
)

target_include_directories(pages PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pages PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
