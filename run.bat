@echo off
echo main [arg_0] [arg_1] [arg_2]
echo:
echo    [arg_0]: Length of the vector
echo:
echo    [arg_1]: Sorting algorithm
echo       -s: selection sort
echo       -d: double selection sort
echo       -h: heapsort 
echo       -c: cycle sort
echo       -t: stable selection sort
echo:
echo    [arg_2]: List style
echo       -r: random
echo       -i: inversed
echo       -o: ordered
echo       -mi: mostly inversed
echo       -mo: mostly ordered
echo:
echo Valid calls: "main 100 -s -r"
echo              "main 340 -h -mi"
echo:
echo On the window: Press 'Enter' to pause/resume the sorting
echo                Press 'Left Arrow' to step forward
echo                Hold 'Control' to slow down the sorting 
echo:
cmd /k
