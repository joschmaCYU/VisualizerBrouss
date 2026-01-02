cmake_minimum_required(VERSION 3.16)

project(VisualizerBrouss VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appVisualizerBrouss
    main.cpp
)

qt_add_qml_module(appVisualizerBrouss
    URI VisualizerBrouss
    QML_FILES
        Main.qml
        SOURCES
        QML_FILES
        SOURCES
        SOURCES brouss/src/compiler.cpp brouss/src/compiler.hpp brouss/src/include/arena.hpp brouss/src/include/generation.hpp brouss/src/include/parser.hpp brouss/src/include/parser.hpp brouss/src/include/tokenization.hpp
        QML_FILES
        SOURCES
        SOURCES brouss/src/tree.hpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVisualizerBrouss PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVisualizerBrouss
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVisualizerBrouss
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appVisualizerBrouss
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
