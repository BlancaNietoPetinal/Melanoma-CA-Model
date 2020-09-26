x = 1:299; % 2NX-1
y = 1:299; % 2NY-1 
[X,Y] = meshgrid(x,y);
fig = figure(); % create a figure
colormap hot
for i = 0:11
    T = load (strcat('Tumor-',int2str(i*10),'.txt'));
    T = reshape(T,[299,299]);
    image(T,'CDataMapping','scaled');
    title(strcat('t = ',int2str(i*10)))
    colorbar
    drawnow
    pause(0.2)
end;
saveas(fig,'Kafka.png');


