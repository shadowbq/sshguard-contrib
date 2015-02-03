cmake_minimum_required (VERSION 2.8)
project (sshguard-contrib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include(ExternalProject)
ExternalProject_Add (sshguard
  URL http://downloads.sourceforge.net/project/sshguard/sshguard/sshguard-1.5/sshguard-1.5.tar.bz2
  URL_MD5 11b9f47f9051e25bdfe84a365c961ec1
  CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --with-firewall=null
  PATCH_COMMAND patch -p1 < ${CMAKE_SOURCE_DIR}/src/expose.patch
  BUILD_IN_SOURCE 1
)

ExternalProject_Get_Property(sshguard source_dir)
include_directories(${source_dir}/src)

FILE(WRITE ${source_dir}/src/sshguard_blacklist.o "")
SET_SOURCE_FILES_PROPERTIES(${source_dir}/src/sshguard_blacklist.o PROPERTIES EXTERNAL_OBJECT TRUE)
FILE(WRITE ${source_dir}/src/seekers.o "")
SET_SOURCE_FILES_PROPERTIES(${source_dir}/src/seekers.o PROPERTIES EXTERNAL_OBJECT TRUE)
FILE(WRITE ${source_dir}/src/simclist.o "")
SET_SOURCE_FILES_PROPERTIES(${source_dir}/src/simclist.o PROPERTIES EXTERNAL_OBJECT TRUE)

add_executable(sshguard-dump src/sshguard-dump.c ${source_dir}/src/sshguard_blacklist.o
  ${source_dir}/src/simclist.o ${source_dir}/src/seekers.o
)
add_executable(sshguard-reprieve src/sshguard-reprieve.c ${source_dir}/src/sshguard_blacklist.o
  ${source_dir}/src/simclist.o ${source_dir}/src/seekers.o
)

install(TARGETS sshguard-reprieve sshguard-dump DESTINATION bin)
