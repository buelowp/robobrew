cmake_minimum_required(VERSION 3.0)
project(robobrew)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)

set(robobrew_SRC
  src/main.cpp
  src/robobrew.cpp
  src/relaymanager.cpp
)

# Tell CMake to create the helloworld executable
add_executable(${PROJECT_NAME} ${robobrew_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Network)

# Install the executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
