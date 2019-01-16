cmake_minimum_required(VERSION 3.13)
project(mileStone2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(mileStone2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h CacheManager.h FileCasheManager.cpp FileCasheManager.h StringReverser.cpp StringReverser.h State.h Searchable.h Isearcher.h Searcher.h BestFirstSearch.h MatrixOfStates.h IntPairMatrixCreator.cpp IntPairMatrixCreator.h MatrixOfPairs.cpp MatrixOfPairs.h DFS.h BFS.h Astar.h Sockets.cpp Sockets.h MyParallelServer.cpp MyParallelServer.h SearchSolver.h MyClientHandler.cpp MyClientHandler.h)