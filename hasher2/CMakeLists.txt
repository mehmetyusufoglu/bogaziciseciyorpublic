cmake_minimum_required(VERSION 2.8)

project(hasher)
#target_link_libraries(program OpenSSL::Crypto)

#find_package(OpenSSL REQUIRED)
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME}  OpenSSL::Crypto)
