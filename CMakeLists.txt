cmake_minimum_required(VERSION 3.1)
project(bruteforcefrac)

set(CMAKE_CXX_STANDARD 17)

add_library(bruteforcefrac include/bruteforcefrac.h include/IntFactorTree/IntFactorTreeNode.h include/IntFactor.h include/IntFactorTree/IntFactorTree.h include/IntFactorList/IntFactorListNode.h include/IntFactorList/IntFactorList.h include/PrimeFactorFinder.h include/RationalNum.h)
set_target_properties(bruteforcefrac PROPERTIES LINKER_LANGUAGE CXX)


add_subdirectory(examples)
