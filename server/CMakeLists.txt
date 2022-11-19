project (server)
#cmake_minimum_required(VERSION 3.9)
# Tools for using NK parser.
include (platform/nk)

# Set compile flags.
project_header_default ("STANDARD_GNU_11:YES" "STRICT_WARNINGS:NO")
find_package(Protobuf REQUIRED)
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable (Server "src/server.cpp")
add_dependencies (Server mqtt_subscriber_server_edl_files)
target_link_libraries(Server ${OpenCV_LIBS})
#set_target_properties (Server PROPERTIES LINK_FLAGS "-no-pie -Ttext 0x00c00000")
