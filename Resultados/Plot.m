NX = 10;
NY = 10;
x = 1:(2*NX-1);
y = 1:(2*NY-1);
[X,Y] = meshgrid(x,y);

x0=140;
y0=140;
width=1000;
height=400;

fig = figure(); % create a figure
set(gcf,'position',[x0,y0,width,height])
colormap hot

for i = 1:10
    T = load (strcat('T-',int2str(i),'.txt'));
    N = load (strcat('N-',int2str(i),'.txt'));
    T = reshape(T,[(2*NX-1), (2*NY-1)]);
    N = reshape(N,[(2*NX-1), (2*NY-1)]);
    
    subplot(1,2,1)
    image(T,'CDataMapping','scaled');
    title('Tumor')
    colorbar
    caxis([0 6])
    subplot(1,2,2)
    image(N,'CDataMapping','scaled');
    title('Nutrientes de division celular')
    sgtitle(strcat(int2str(i), ' meses'))
    colorbar
    caxis([1 7])
    F(i) = getframe(gcf) ;
    drawnow
    pause(0.3)
end;
writerObj = VideoWriter('myVideo.avi');
writerObj.FrameRate = 1;

% open the video writer
open(writerObj);
% write the frames to the video
for i=1:length(F)
    % convert the image to a frame
    frame = F(i) ;    
    writeVideo(writerObj, frame);
end
% close the writer object
close(writerObj);



