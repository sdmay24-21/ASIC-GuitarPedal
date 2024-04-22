

#memorycontroller
verilator --cc --exe --build -j 0 -Wall memorycontroller.cpp ../../../rtl/memory/memorycontroller.v
obj_dir/Vmemorycontroller "test1.csv" "test1impulse.csv" "test1output.csv"