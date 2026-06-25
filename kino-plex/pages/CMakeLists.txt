add_library(pages STATIC
    logandregisterpage.cpp
    movielistpage.cpp
    movielistpage.h
    moviedetailspage.cpp
    moviedetailspage.h
    seatselectionpage.cpp
    seatselectionpage.h
    checkoutpage.cpp
    checkoutpage.h
    logandregisterpage.h
)

target_include_directories(pages PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pages PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
