cmake_minimum_required(VERSION 2.8)
project(flow)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_cpp_STANDARD 14)
set(CMAKE_BUILD_TYPE debug)

set(DATATREE /home/ogolosov/Desktop/analysis/DataTree)
set(CENTRALITY /home/ogolosov/Desktop/analysis/centrality)
set(PID /home/ogolosov/Desktop/analysis/pid)
set(EXPERIMENT "SHINE")

set(EXE_SOURCES
        CorrectionTask.cpp
        CorrelationTask.cpp
        main.cpp)

set(CORR_SOURCES
        Correlation/Correlation.cpp
        Correlation/CorrelationManager.cpp)

set(DIFF_SOURCES
        DifferentialCorrection/EventInfo.cpp
        DifferentialCorrection/VariableManager.cpp
        DifferentialCorrection/CorrectionManager.cpp
        DifferentialCorrection/Detector.cpp
        DifferentialCorrection/Interface/DataFiller.cpp
        DifferentialCorrection/Interface/VarManager.cpp
        DifferentialCorrection/HistogramManager.cpp
        )

set(CUTS_SOURCES
        cuts/isGoodEvent.cpp
        cuts/isGoodTrack.cpp
        )

set(BASE_SOURCES
        Base/DataVector.cpp
        Base/DataContainer.cpp
        Base/Axis.cpp
        Base/QVector.cpp
        Base/Stats.cpp
        Base/DataContainerHelper.cpp
        Base/Efficiency.cpp)

string(REPLACE ".cpp" ".h" BASE_HEADERS "${BASE_SOURCES}")
string(REPLACE ".cpp" ".h" DIFF_HEADERS "${DIFF_SOURCES}")
string(REPLACE ".cpp" ".h" CORR_HEADERS "${CORR_SOURCES}")
string(REPLACE ".cpp" ".h" CUTS_HEADERS "${CUTS_SOURCES}")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Telling CMake where to find the ROOT installation.
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib")

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core MathCore MathMore RIO Hist Tree Net TreePlayer)

# Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})
add_compile_options(-DDATATREE_${EXPERIMENT}) 

include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${DATATREE}/src ${CENTRALITY}/src ${PID}/src)

add_subdirectory(QnCorrections)
# add_subdirectory(googletest)

ROOT_GENERATE_DICTIONARY(G__BaseFlow ${BASE_HEADERS} LINKDEF Base/BaseLinkDef.h)
add_library(BaseFlow SHARED ${BASE_SOURCES} G__BaseFlow)
target_link_libraries(BaseFlow ${ROOT_LIBRARIES} qncorrflow)

add_library(cuts SHARED ${CUTS_SOURCES})
target_link_libraries(cuts ${ROOT_LIBRARIES} "${DATATREE}/build/libDataTree.so")

add_library(diffflow SHARED ${DIFF_SOURCES})
target_link_libraries(diffflow ${ROOT_LIBRARIES} qncorrflow BaseFlow "${DATATREE}/build/libDataTree.so" "${CENTRALITY}/build/libCentrality.so" "${PID}/build/libPid.so" cuts)

add_library(correlationflow SHARED ${CORR_SOURCES})
target_link_libraries(correlationflow ${ROOT_LIBRARIES} BaseFlow)

# Create a main program using the library
add_executable(main ${EXE_SOURCES})
target_link_libraries(main correlationflow diffflow BaseFlow ${ROOT_LIBRARIES} ${QNCORRECT_LIB} "${CENTRALITY}/build/libCentrality.so" "${PID}/build/libPid.so")
target_include_directories(main PUBLIC ${EXE_HEADERS} ${QNCORRECT_INC})

