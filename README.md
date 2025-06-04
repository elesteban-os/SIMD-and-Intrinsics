# SIMD and Intrinsics
To compile and execute this project you will need to have linux Ubuntu on recent versions like 22.04 LTS or 24.04 LTS, because this compile and execution instructions are focused on that OS.

## Dependencies
First you have to ensure to have installed some dependencies:
- C++17
- Python 3.12.3
- plotly (python library)
- pandas (python library)

If you are missing some of those dependencies, here are specific commands of Ubuntu to install them:
### C++17
```
sudo apt update
sudo apt install g++
```

### Python 3.12.3
```
sudo apt update
sudo apt install python3
```

### plotly
```
pip3 install plotly
```

### pandas
```
pip install pandas 
```

## Compilation and execution of graphics.py
This file is the script that compile and execute the C++ main.cpp program that contains the execution of the serial and SIMD algorithms to count a specific char in a string. Then generates two graphics that shows the relation between:
1. Lenght of the string vs execution time in both cases (serial and SIMD algorithm)
2. Lenght of the string vs number of occurrencies of the selected char in both cases (serial and SIMD algorithm)

To compile and execute this script use:
```
python3 graphics.py
```

## Configuration of perf in case of error
If you want to test the files main_serial.cpp or main_simd.cpp that contains little and specific tests for those algorithm, and use perf to see some metrics and statistics about memory usage and execution times, it is possible that if you use this command for example:
```
perf stat ./<executable>
```
you'll se some error, if that is your case, to fix it follow this steps:
1. run the command:
```
sudo nano /etc/sysctl.conf
```
this will open the sysctl.conf file to edit it.
2. go to the end of the file and write this:
```
kernel.perf_event_paranoid = -1
```
3. press `Ctrl + o` to save the changes
4. press `Enter` to finish save
5. press `Ctrl + x` to close the file
6. finally use this command 
```
sudo sysctl -p
```
This will give the permissions to perf to access some OS data.

## Compilation and execution of main_serial.cpp
This file has a test with a little string of the serial algorithm to count a specific char in a string. If you want to test it and see some metrics about memory usage and execution times with only this algoritm in specific, then use this command to navigate to serial folder:
```
cd serial
```
Then to compile it:
```
g++ main_serial.cpp char_count_serial.cpp -o main_serial
```
Then to execute it with perf to see statistics:
```
perf stat ./main_serial
```
Or if you just to want execute it normally:
```
./main_serial
```

## Compilation and execution of main_simd.cpp
This file has a test with a little string of the simd algorithm using intrinsics to count a specific char in a string. If you want to test it and see some metrics about memory usage and execution times with only this algoritm in specific, then use this command to navigate to simd folder:
```
cd simd
```
Then to compile it:
```
g++ main_simd.cpp char_count_simd.cpp -o main_simd -mavx
```
Then to execute it with perf to see statistics:
```
perf stat ./main_simd
```
Or if you just to want execute it normally:
```
./main_simd
```

## Compilation and execution of main_random_str.cpp
This file has a test little test to generate a 24 chars string with an aligment of 8 Bytes. If you want to test it then use this command to navigate to random_str folder:
```
cd random_str
```
Then to compile it:
```
g++ main_random_str.cpp random-str.cpp -o main_random_str
```
Then to execute it:
```
./main_random_str
```

## Compilation and execution of main.cpp
This file is which python script compile and execute to obtain the data (which is saved in a csv file "results.csv") and generate the graphics. If you want to compile and execute this file to just obtain the data in the csv file then use this command to compile it:
```
g++ -std=c++17 -O2 main.cpp random_str/random-str.cpp serial/char_count_serial.cpp simd/char_count_simd.cpp -o test -mavx
```
Then to execute it:
```
./test
```