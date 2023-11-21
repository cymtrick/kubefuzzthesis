cd libs/abseil-cpp && mkdir build && cd build && cmake -DABSL_BUILD_TESTING=ON -DABSL_USE_GOOGLETEST_HEAD=ON -DCMAKE_CXX_STANDARD=14 .. && cmake --build . --target all
cd ../../

