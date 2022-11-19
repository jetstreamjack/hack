cmake_minimum_required(VERSION 3.12)

# Toolchain for working with the NK-parser.
include (platform/nk)

# Set compiler flags.
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wno-deprecated-declarations")

add_executable (Subscriber "src/main.cpp" "src/subscriber.cpp" )
add_dependencies (Subscriber subscriber_edl_files)
add_dependencies (Subscriber mqtt_subscriber_idl_files mqtt_subscriber_cdl_files mqtt_subscriber_server_edl_files)
target_link_libraries(Subscriber 
                      ${mosquitto_CXX_LIB}
                      ${vfs_CLIENT_LIB}
)

# We do not need the default VFS entity which comes from ${vfs_CLIENT_LIB}.
set_target_properties (Subscriber PROPERTIES ${vfs_ENTITY}_REPLACEMENT "")
set_target_properties (Subscriber PROPERTIES LINK_FLAGS ${VULN_LDFLAGS})
find_package(nlohmann_json 3.2.0 REQUIRED)
#add_library(Subscriber ...)
target_link_libraries(Subscriber  nlohmann_json::nlohmann_json)
