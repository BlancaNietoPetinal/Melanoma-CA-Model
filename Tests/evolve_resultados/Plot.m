NX = 10;
NY = 10;
x = 1:(2*NX-1);
y = 1:(2*NY-1); 
[X,Y] = meshgrid(x,y);
fig = figure(); % create a figure
colormap hot
for i = 0:3
    T = load (strcat('T-',int2str(i*10),'.txt'));
    T = reshape(T,[(2*NX-1),(2*NY-1)]);
    image(T,'CDataMapping','scaled');
    title(strcat('t = ',int2str(i*10)))
    colorbar
    drawnow
    pause(0.2)
end;
saveas(fig,'Kafka.png');


