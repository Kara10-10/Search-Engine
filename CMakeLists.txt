
#cmake_minimum_required (VERSION 3.8)
#project(crawler)
#set(SAMPLE_NAME "${crawler}-SimpleHttpClient")
#set(SAMPLE_SRCS "SimpleHttpClient.cpp")

set(SAMPLE_NAME "crawler")
set(SAMPLE_SRCS "crawler.cpp")
#depend libraries
find_package(Poco REQUIRED Foundation Data DataSQLite Net NetSSL Crypto CONFIG)
find_package(easyhttpcpp REQUIRED CONFIG)

add_executable(${SAMPLE_NAME} ${SAMPLE_SRCS} linkqueue.cpp ) 
target_link_libraries(${SAMPLE_NAME}
          easyhttpcpp::easyhttp
                    Poco::Foundation
                              Poco::Data Poco::DataSQLite
                                        Poco::Net Poco::NetSSL Poco::Crypto
                                                        ssl crypto
                                                            )