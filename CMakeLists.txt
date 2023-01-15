cmake_minimum_required(VERSION 3.0.0)
project(TrainBookingSystem VERSION 0.1.0)

include(CTest)
enable_testing()


file(GLOB SRC_LIST "src/*.cpp")
file(GLOB SRC_HEADERS "src/*.h")
file(GLOB SRC_TRAIN_LIST "src/Train/*.cpp")
file(GLOB SRC_TRAIN_HEADERS "src/Train/*.h")
file(GLOB SRC_PASSENGER_LIST "src/Passenger/*.cpp")
file(GLOB SRC_PAEESENGER_HEADERS "src/Passenger/*.h")
file(GLOB SRC_BOOKING_LIST "src/Booking/*.cpp")
file(GLOB SRC_BOOKING_HEADERS "src/Booking/*.h")

set(SRC ${SRC_LIST} ${SRC_HEADERS} ${SRC_TRAIN_LIST} ${SRC_TRAIN_HEADERS} ${SRC_PASSENGER_LIST} ${SRC_PASSENGER_HEADERS} ${SRC_BOOKING_LIST} ${SRC_BOOKING_HEADERS})

add_executable(TrainBookingSystem ${SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
