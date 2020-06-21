set(this Socket)

project(${this})

set(Headers
    client.hpp
    server.hpp
)

set(Source 
    client.cpp
    server.cpp
)

add_library(${this} 
    ${Headers}
    ${Source}
)