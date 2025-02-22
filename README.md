[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/cvGWw7TG)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=18160537&assignment_repo_type=AssignmentRepo)
# First Challenge

This code challenge has the purpose of getting a sense of your coding and algorithmic skills. This challenge's solving will provide the professor some insights in the level and methodology that should be followed in the class.

The main problem is simple, you need to sort all strings in the `data.txt` file and out it in `sorted_data.txt` file. 


## General Instructions
- It's a 2-members team's work
- We'll have 3 winner teams, they will obtain 10% extra bonus on the final grade
- The winners' policy will be based on performance and execution time (fastest program is the one that wins)
- The program must be `terminal-based` in the programming language of your choice
- Make sure to document all requirements to buid/compile and run your program (update the [how-to-build-comple](#how-to-buildcompile) and [how to run](#how-to-run) sections)
- Make sure your program compiles and runs
- Take advantage of the [`sorted_sample.txt`](https://storage.googleapis.com/tec-challenge/sorted_sample.txt) and [`sorted_complete.txt`](https://storage.googleapis.com/tec-challenge/sorted_complete.txt) files in order to compare you output `sorted_data.txt` file
- Since the data files are big, tt's recommended to download the file with `wget` or other remote-downloading tool.


## Problem-specific Instructions
- There's a 1GB [data.txt](https://storage.googleapis.com/tec-challenge/data.txt) with `4,194,304` usorted `256-bytes` string
- The program will take the [`data.txt`](https://storage.googleapis.com/tec-challenge/data.txt) file as input and will generate a `sorted_data.txt` output file with all string sorted.
- There's an example small [`sorted_sample.txt`](https://storage.googleapis.com/tec-challenge/sorted_sample.txt) file, it can be used as reference about how data should be sorted
- The [`sorted_complete.txt`](https://storage.googleapis.com/tec-challenge/sorted_complete.txt) file is the result sorted file you can use to compare with your `sorted_data.txt` file.
- The program's execution time will be measured. Programs that run more than 5 minutes will be discualifed
- You have the freedom to choose the sorting algorithm(s)
- The strings contains numbers and letter only
- Numbers have higher priority over letter. Numbers sorting starts on `0`

## How to build/compile

This code is written in C++ latest version. Its a single file that can be compiled with the following command g++ -std=c++17 -o challenge challenge.cpp

## How to run

Open the .exe file after compilling it. The user needs MacOs for the program to work properly (because every operative system needs a different library to read the RAM of the device)

## Test Cases

Your program will be tested in an isolated environment (containers) with the following test cases. On each test, the execution time will be measured

### Test 1
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 1GB

### Test 2 
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 512MB

### Test 3
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 256MB

### Test 4
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 128MB

### Test 5
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 64MB

### Test 6
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 32MB

### Test 7
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 16MB

### Test 8
- Storage - unlimited
- CPU - 8 vCPUs
- Memory - 8MB

## Grading Policy

Grading will be based in the time it takes for each test case, and the team 
that gets the fastest time in all scenarios is the one that will win the 
contest and will get the extra bonus in the final grade.
