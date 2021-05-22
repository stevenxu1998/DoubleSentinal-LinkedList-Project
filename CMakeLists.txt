cmake_minimum_required(VERSION 3.9)
project(project_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(project_1
        assign.int.in.txt
        assign.int.out.txt
        double.in.txt
        double.out.txt
        Double_node_tester.h
        Double_sentinel_list.h
        Double_sentinel_list_driver.cpp
        Double_sentinel_list_tester.h
        ece250.h
        Exception.h
        int.in.txt
        int.out.txt
        step.int.in.txt
        step.int.out.txt
        test.cpp
        Tester.h Move_and_copy_tests.cpp)
