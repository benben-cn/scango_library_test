cmake_minimum_required(VERSION 3.20)
project(Scango_Dll_Test)

if(MSVC)
    # 对于MSVC编译器
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>")
else()
    # 对于GCC/Clang等编译器
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

add_executable(Scango_Dll_Test scangodll_test.cpp)
set_target_properties(Scango_Dll_Test PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 包含 DLL 的头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)
# 链接到 DLL 的导入库
target_link_libraries(SCANGO_Dll PRIVATE ${PROJECT_SOURCE_DIR}/lib)
