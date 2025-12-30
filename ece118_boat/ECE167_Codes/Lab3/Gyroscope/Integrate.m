close all;
clear all;
clc;

xfileID= fopen('gyroh_x.txt','r');
yfileID= fopen('gyroh_y.txt','r');
zfileID= fopen('gyroh_z.txt','r');

formatSpec='%f';
x= fscanf(xfileID,formatSpec);
y= fscanf(yfileID,formatSpec);
z= fscanf(zfileID,formatSpec);

fclose(xfileID);
fclose(yfileID);
fclose(zfileID);

xbias = -5.3326;
ybias = -43.2620;
zbias = 9.8428;

l=(length (x)-1)*0.02;
timex =(0:0.02:l);
l=(length (y)-1)*0.02;
timey=(0:0.02:l);
l=(length (z)-1)*0.02;
timez=(0:0.02:l);
xscale=(x-xbias)./131;
yscale=(y-ybias)./131;
zscale=(z-zbias)./131;

xaxis=cumtrapz(timex,xscale);
yaxis=cumtrapz(timey,yscale);
zaxis=cumtrapz(timez,zscale);

figure;
subplot(3,1,1);
plot(timex,xaxis);
subplot(3,1,2);
plot(timey,yaxis);
subplot(3,1,3);
plot(timez,zaxis);
