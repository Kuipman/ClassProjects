close all;
clear all;
clc;

xfileID= fopen('gyro_slow_x','r');
yfileID= fopen('gyro_slow_y','r');
zfileID= fopen('gyro_slow_z','r');

formatSpec='%f';
x= fscanf(xfileID,formatSpec);
y= fscanf(yfileID,formatSpec);
z= fscanf(zfileID,formatSpec);

fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

yb = mean(y);

xbias = 1.018908906882591e+03;
ybias = -51.025114155251140;
zbias = 9.8428;

l=(length (x)-1)*0.02;
timex =(0:0.02:l);
l=(length (y)-1)*0.02;
timey=(0:0.02:l);
l=(length (z)-1)*0.02;
timez=(0:0.02:l);
xscale= (x-xbias)./131;
yscale=(y-ybias)./131;
zscale=(z-zbias)./131;

xaxis=cumtrapz(timex,xscale);
yaxis=cumtrapz(timey,yscale);
zaxis=cumtrapz(timez,zscale);


figure;
subplot(3,1,1);
plot(timex,xaxis);
title('X- axis 90 Degree Back and Forth');
xlabel('Time(20ms)') 
ylabel('Degrees')
subplot(3,1,2);
plot(timey,yaxis);
title('Y- axis 90 Degree Back and Forth');
xlabel('Time(20ms)') 
ylabel('Degrees')
subplot(3,1,3);
plot(timez,zaxis);
xlabel('Time(20ms)') 
ylabel('Degrees')
title('Z- axis 180 Degree Back and Forth');
xlabel('Time(20ms)') 
ylabel('Degrees')