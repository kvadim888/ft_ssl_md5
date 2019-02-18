cmake_minimum_required(VERSION 3.12)
project(ft_ssl C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(./libft/sources/ft_memory MEMORY)
aux_source_directory(./libft/sources/ft_printf/src PRINTF)
aux_source_directory(./libft/sources/ft_string STRING)
aux_source_directory(./libft/sources/ft_list LIST)
aux_source_directory(./libft/sources/ft_sys SYS)

add_library(ft STATIC ${MEMORY} ${STRING} ${PRINTF} ${LIST} ${SYS})

target_include_directories(ft PUBLIC ./includes)

aux_source_directory(./src/ SSL_SRC)     # Collects the names of all the source files
                                            # in the specified directory and stores the list
                                            # in the <variable> provided

include_directories(./inc ./libft/includes)

#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_executable(ft_ssl ${SSL_SRC})
target_link_libraries(ft_ssl ft)
