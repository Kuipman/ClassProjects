clc;
close all;
clear all;

tape_measurement = [0 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30]; %in cm
ping_measurement = [516 640 694 744 797 850 920 1009 1061 1114 1167 1274 1361 1414 1502 1554 1589 1642 1677 1730 1785 1819 1874 1924 1977 2047 2083 2136 2188 2258]; %uno reading
newY = 0.0170*ping_measurement+(-9.1564);

figure
plot(ping_measurement, tape_measurement);
hold on
plot(ping_measurement, newY);

X = transpose([ping_measurement; ones(1, length(ping_measurement))]);
Y = transpose(tape_measurement);

p = X\Y;

disp(p);