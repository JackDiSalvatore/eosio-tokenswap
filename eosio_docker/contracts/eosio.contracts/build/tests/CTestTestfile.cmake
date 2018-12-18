# CMake generated Testfile for 
# Source directory: /Volumes/JackDiSalvatoreSSDT5/JacksFiles/EOSIO/eosio.contracts/tests
# Build directory: /Volumes/JackDiSalvatoreSSDT5/JacksFiles/EOSIO/eosio.contracts/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_test_binaryen "/Volumes/JackDiSalvatoreSSDT5/JacksFiles/EOSIO/eosio.contracts/build/tests/unit_test" "--report_level=detailed" "--color_output" "--" "--binaryen")
add_test(unit_test_wavm "/Volumes/JackDiSalvatoreSSDT5/JacksFiles/EOSIO/eosio.contracts/build/tests/unit_test" "--report_level=detailed" "--color_output" "--catch_system_errors=no" "--" "--wavm")
