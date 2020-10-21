NX = 5;
NY = 5;
x = 1:(2*NX-1);
y = 1:(2*NY-1); 
[X,Y] = meshgrid(x,y);
fig = figure(); % create a figure
colormap hot
T = load ('N-3.txt');
T = reshape(T,[2*NX-1,2*NY-1]);
image(T,'CDataMapping','scaled');
colorbar
% for i = 0:10
%     T = load (strcat('N-',int2str(i),'.txt'));
%     T = reshape(T,[2*NX-1,2*NY-1]);
%     image(T,'CDataMapping','scaled');
%     title(strcat('t = ',int2str(i)))
%     colorbar
%     drawnow
%     pause(0.2)
% end;
