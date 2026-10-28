# CProcessing starter project for Windows, Linux and macOS
#
# Build and run, from this folder:
#
#   cmake -B build
#   cmake --build build
#   cd build/bin
#   ./MyGame                (MyGame.exe on Windows)
#
# The game is built into build/bin, next to the CProcessing library and a
# copy of the Assets folder. Run it from there: CProcessing loads assets
# relative to the current working directory.
#
# Where CProcessing comes from:
#   - The Linux and macOS release packages include a CProcessing folder next
#     to this file, with the library already built. It's used when it's there.
#   - Otherwise CProcessing is downloaded and built from source the first time
#     you configure. That needs an internet connection and, on Linux, the
#     development packages listed in CProcessing's BUILDING.md.

cmake_minimum_required(VERSION 3.20)

# 프로젝트 이름 설정 (이 이름이 실행 파일 이름이 됩니다)
project(OneHole C CXX)

# 현재 폴더의 모든 .cpp 파일을 자동으로 찾아서 실행 파일로 만듦
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# CProcessing 엔진 라이브러리 경로 설정 (현재 폴더 자체가 엔진)
set(CPROCESSING_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
if(EXISTS "${CPROCESSING_DIR}/inc/cprocessing.h")
    # 미리 빌드된 라이브러리 사용
    add_library(CProcessing SHARED IMPORTED)
    set_target_properties(CProcessing PROPERTIES
        IMPORTED_LOCATION "${CPROCESSING_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}CProcessing${CMAKE_SHARED_LIBRARY_SUFFIX}"
        INTERFACE_INCLUDE_DIRECTORIES "${CPROCESSING_DIR}/inc")
else()
    # 인터넷에서 다운로드 (이 부분은 보통 타지 않습니다)
    enable_language(CXX)
    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()
    include(FetchContent)
    FetchContent_Declare(cprocessing
        URL https://github.com/DigiPen-Faculty/CProcessing/archive/refs/tags/v3.0.1.tar.gz)
    FetchContent_MakeAvailable(cprocessing)
endif()

# 프로젝트와 엔진 라이브러리 연결
target_link_libraries(${PROJECT_NAME} PRIVATE CProcessing)

# 실행 파일과 에셋을 build/bin 폴더에 배치
set(GAME_DIR "${CMAKE_BINARY_DIR}/bin")
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${GAME_DIR}$<0:>"
    VS_DEBUGGER_WORKING_DIRECTORY "${GAME_DIR}")

# Mac 환경 설정
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES BUILD_RPATH "@loader_path")
endif()

# 빌드 후 라이브러리와 에셋 폴더 복사
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:CProcessing>" "${GAME_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "${GAME_DIR}/Assets"
    VERBATIM)