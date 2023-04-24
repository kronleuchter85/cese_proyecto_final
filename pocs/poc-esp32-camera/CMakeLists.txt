cmake_minimum_required(VERSION 3.16.0)

# (Not part of the boilerplate)
# This example uses an extra component for common functions such as Wi-Fi and Ethernet connection.
set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/../esp-idf-lib/components)


include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(poc-esp32-1)
