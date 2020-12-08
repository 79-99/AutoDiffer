file(GLOB AUTODIFFER_H *.h)

set(AUTODIFFER_SRC
    All.cpp
)

# ==================== #
# Build shared library #
# ==================== #
add_library(AutoDiffer SHARED ${AUTODIFFER_SRC} ${AUTODIFFER_H})

OPTION(THREAD "Link against openmp" OFF)
if(THREAD)
	find_package(OpenMP REQUIRED)
	target_link_libraries(AutoDiffer OpenMP::OpenMP_CXX)
	target_compile_definitions(AutoDiffer PUBLIC USE_THREAD)
endif()

# Install targets into specific directories
install(TARGETS AutoDiffer 
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
	ARCHIVE DESTINATION lib/
)

install(FILES ${AUTODIFFER_H} DESTINATION include)
install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)
