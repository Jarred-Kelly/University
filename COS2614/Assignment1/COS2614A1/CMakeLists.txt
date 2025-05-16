cmake_minimum_required(VERSION 3.19)
project(COS2614A1_New LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(COS2614A1_New
    main.cpp
    book.h book.cpp
    libraryitem.h libraryitem.cpp
    magazine.h magazine.cpp
    magazine.h magazine.cpp
    librarymanager.h librarymanager.cpp
)

target_link_libraries(COS2614A1_New
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS COS2614A1_New
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET COS2614A1_New
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
