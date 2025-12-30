close all;
clc;
clear all;

xfileID= fopen('accelx','r');
yfileID= fopen('accely','r');
zfileID= fopen('accelz','r');

%Open as floats
formatSpec = '%f';

%Store data and then close file
accel_x = fscanf(xfileID, formatSpec);
accel_y = fscanf(yfileID, formatSpec);
accel_z = fscanf(zfileID, formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scale_Factor_Accelerometer_x=accel_x.*0.00058;
scale_Factor_Accelerometer_y=accel_y.*0.00058;
scale_Factor_Accelerometer_z=accel_z.*0.00058;
norm_A= sqrt(scale_Factor_Accelerometer_x.^2+scale_Factor_Accelerometer_y.^2+scale_Factor_Accelerometer_z.^2);

x = (accel_x + 20.4722).*0.00058;
y = (accel_y + 57.4691).*0.00058;
z = (accel_z + 15.0247).*0.00058;
normA = x.^2 + y.^2 + z.^2;

figure;
subplot(2,1,1)
plot(norm_A);
title('Original Accelerometer Data')
ylabel('Gravity (G)')

subplot(2,1,2)
plot(normA);
title('Naive Accelerometer Data');
ylabel('Gravity (G)');

%Calibrating Accelerometer Using Matlab Function
time = 0:0.02:((length(accel_x)-1)*0.02);

[Atile,Btile]=CalibrateEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,20,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,Atile,Btile);

norm_CalibratedA= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))

figure;
subplot(2,1,1)
plot(time,norm_A);
title('Original Accelerometer Data')
xlabel('time (ms)') 
ylabel('Gravity (G)')

subplot(2,1,2)
plot(time,norm_CalibratedA);
title('Calibrated Accelerometer Data')
xlabel('time (ms)') 
ylabel('Gravity (G)') 


%-------------------------------------------
%Calibrations for Magnetometer
%-------------------------------------------

xfileID= fopen('magx','r');
yfileID= fopen('magy','r');
zfileID= fopen('magz','r');

%Open as floats
formatSpec = '%f';

%Store data and then close file

mag_x = fscanf(xfileID, formatSpec);
mag_y = fscanf(yfileID, formatSpec);
mag_z = fscanf(zfileID, formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scaled_mag_x=mag_x;
scaled_mag_y=mag_y;
scaled_mag_z=mag_z;
norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2)

mx = (accel_x - 88.1723);
my = (accel_y - 288.7218);
mz = (accel_z + 51.9787);
normM = mx.^2 + my.^2 + mz.^2;


figure;
subplot(2,1,1)
plot(norm_M);
title('Original Magnetometer Data')
ylabel('Earth Magnetic Field')

subplot(2,1,2)
plot(normM);
title('Naive Magnetometer Data')
ylabel('Earth Magnetic Field')

%Calibrating Magnetometer using Matlab Function
[Atile,Btile]=CalibrateEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,20,0)

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,Atile,Btile);
time = 0:0.02:((length(scaled_mag_x)-1)*0.02);

norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2)
norm_CalibratedM= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2))

figure;
subplot(2,1,1)
plot(time,norm_M);
title('Original Magnetometer Data')
ylabel('Magnetic Field (uT)') 
xlabel('time (ms)') 

subplot(2,1,2)
plot(time,norm_CalibratedM);
title('Calibrated Magnetometer Data')
ylabel('Magnetic Field (uT)') 
xlabel('time(ms)')
