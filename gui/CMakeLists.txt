set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.hpp)
set(LAYOUT  ${CMAKE_CURRENT_SOURCE_DIR}/layout/main_window.ui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS})

# 1. If a Q_OBJECT or Q_GADGET macro is found in a header file, moc will be run on the file.
#    The result will be put into a file named according to moc_<basename>.cpp
# 2. If the macro is found in a C++ implementation file, the moc output will be put into a
#    file named according to <basename>.moc The moc file may be included by the user in the
#    C++ implementation file with a preprocessor #include. If it is not so included, it will
#    be added to a separate file which is compiled into the target.

# 3. If a preprocessor #include directive is found which matches ui_<basename>.h, and a <basename>.ui
#    file exists, then uic will be executed to generate the appropriate file.

# 4. creates rules to execute rcc at the appropriate time on source files which have the suffix .qrc.

#qt5_wrap_ui(LAYOUT_HEADERS ${LAYOUT})
add_library(gui ${SOURCES} ${HEADERS} moc_main_window.cpp)
