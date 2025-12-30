close all;
clear all;
clc;

xfileID= fopen('ta_x','r');
yfileID= fopen('ta_y','r');
zfileID= fopen('ta_z','r');
formatSpec='%f';
accel_x= fscanf(xfileID,formatSpec);
accel_y= fscanf(yfileID,formatSpec);
accel_z= fscanf(zfileID,formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scale_Factor_Accelerometer_x=accel_x.*0.00098;
scale_Factor_Accelerometer_y=accel_y.*0.00098;
scale_Factor_Accelerometer_z=accel_z.*0.00098;
norm_A= sqrt(scale_Factor_Accelerometer_x.^2+scale_Factor_Accelerometer_y.^2+scale_Factor_Accelerometer_z.^2);

x = (accel_x + 20.4722).*0.00098;
y = (accel_y + 57.4691).*0.00098;
z = (accel_z + 15.0247).*0.00098;
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

[Atile,Btile]=CalibrateEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,20,0);

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scale_Factor_Accelerometer_x,scale_Factor_Accelerometer_y,scale_Factor_Accelerometer_z,Atile,Btile);

norm_CalibratedA= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2));

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

figure;
subplot(2,1,1)
histfit(norm_A)
title('Original Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin')

subplot(2,1,2)
histfit(norm_CalibratedA)
title('Calibrated Accelerometer Data')
xlabel('Gravity (G)') 
ylabel('Bin')


%-------------------------------------------------------------------------------------------
%Calibrations for Magnetometer
%--------------------------------------------------------------------------------------------
xfileID= fopen('t_mag_x','r');
yfileID= fopen('t_mag_y','r');
zfileID= fopen('t_mag_z','r');

formatSpec='%f';

mag_x= fscanf(xfileID,formatSpec);
mag_y= fscanf(yfileID,formatSpec);
mag_z= fscanf(zfileID,formatSpec);
fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

scaled_mag_x=mag_x*1000;
scaled_mag_y=mag_y*1000;
scaled_mag_z=mag_z*1000;
norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2)

mx = (mag_x - 88.1723).*1000;
my = (mag_y - 288.7218).*1000;
mz = (mag_z + 51.9787).*1000;
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
[Atile,Btile]=CalibrateEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,20,0);

[Xcorr,Ycorr,Zcorr]=CorrectEllipsoidData3D(scaled_mag_x,scaled_mag_y,scaled_mag_z,Atile,Btile);
time = 0:0.02:((length(scaled_mag_x)-1)*0.02);

norm_M= sqrt(scaled_mag_x.^2+scaled_mag_y.^2+scaled_mag_z.^2);
norm_CalibratedM= sqrt((Xcorr.^2)+(Ycorr.^2)+(Zcorr.^2));

%Histagram for Magnetometer
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

figure;
subplot(2,1,1)
histfit(norm_M)
title('Original Magnetometer Data')
xlabel('Magnetic Field (nT)') 
ylabel('Bin') 

subplot(2,1,2)
histfit(norm_CalibratedM)
title('Calibrated Magnetometer Data')
xlabel('Magnetic Field (nT)') 
ylabel('Bin') 

%-------------------------------------
% 3D Plots
%-------------------------------------
figure;
plot3(accel_x, accel_y, accel_z,".");
title("Original Accelerometer Data")

figure;
plot3(x, y, z, ".")
title("Calibrated Accelerometer Data")

figure;
plot3(mag_x, mag_y, mag_z, ".");
title("Original Mag Data");
figure;
plot3(mx, my, mz, ".");
title("Calibrated Mag Data");



standard_naive_Deviation_Accelerometer=std(normA);
average_naive_Accelerometer=mean(normA)
standard_naive_Deviation_Magnetometer=std(normM);
average_naive_Magnetometer=mean(normM)
T=table(standard_naive_Deviation_Accelerometer,average_naive_Accelerometer,standard_naive_Deviation_Magnetometer,average_naive_Magnetometer)

standard_Deviation_Accelerometer=std(norm_CalibratedA);
average_Accelerometer=mean(norm_CalibratedA)
standard_Deviation_Magnetometer=std(norm_CalibratedM);
average_Magnetometer=mean(norm_CalibratedM)
T=table(standard_Deviation_Magnetometer,average_Magnetometer,standard_Deviation_Accelerometer,average_Accelerometer)


