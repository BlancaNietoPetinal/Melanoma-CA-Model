
figure;
fig = plot([0.005,0.0075,0.025,0.25, 0.5, 0.75],[0.09,0.111,0.157,0.545, 0.647, 0.65],'o'); % pPapillary
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Papillary');
saveas(fig,'Papillary-lysis-ratio','png');

figure;
fig = plot([0.005, 0.0075, 0.025, 0.25, 0.75],[0.0021, 0.00335,0.0136,0.0306, 0.0356],'o'); % Spherical
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Spherical');
saveas(fig,'Spherical-lysis-ratio','png');

figure;
fig = plot([0.005,0.0075,0.025, 0.25, 0.75],[0.0178,0.0667,0.158,0.256,0.295],'o') %Filamentary
xlabel('Target ratio (E/T)');
ylabel('Lysis');
title('Filamentary');
saveas(fig,'Filamentary-lysis-ratio','png');

