
python test.py
./main_wesley < t.in > wesley.out
./main_yian < t.in > yian.out
python new_test.py
./main_yian < wesley2.in > wesley2.out
diff wesley2.out 0.testcase
sh assert.sh

