% PAPILLARY
figure;
xdataP = [0.005,0.0075,0.025,0.25, 0.5, 0.75];
ydataP = [0.09,0.111,0.157,0.545, 0.647, 0.65];

xFitP = linspace(min(xdataP), max(xdataP), 1000); % 1000 points.
coefficients = polyfit(xdataP, ydataP, 2);
yFittedP = polyval(coefficients, xFitP);
plot(xFitP,yFittedP,xdataP,ydataP,'O'); % pPapillary
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Papillary');
saveas(gcf,'Papillary-lysis-ratio','jpg');

%SPHERICAL
figure;
xdataS = [0.005, 0.0075, 0.025, 0.25, 0.75];
ydataS = [0.0021, 0.00335,0.0136,0.0306, 0.0356];
xFitS = linspace(min(xdataS), max(xdataS), 1000);
coefficients = polyfit(xdataS, ydataS, 2);
yFittedS = polyval(coefficients, xFitS);
plot(xFitS,yFittedS,xdataS,ydataS,'O');
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Spherical');
saveas(gcf,'Spherical-lysis-ratio','png');

% FILAMENTARY
figure;
xdataF = [0.005,0.0075,0.025, 0.25, 0.75];
ydataF = [0.0178,0.0667,0.158,0.256,0.295];
xFitF = linspace(min(xdataF), max(xdataF), 1000);
coefficients = polyfit(xdataF, ydataF, 2);
yFittedF = polyval(coefficients, xFitF);

plot(xFitF,yFittedF,xdataF,ydataF,'o')
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Filamentary');
saveas(gcf,'Filamentary-lysis-ratio','png');
