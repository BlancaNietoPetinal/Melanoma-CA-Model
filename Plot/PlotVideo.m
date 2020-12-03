NX = 50;
NY = 50;
NFrames = 10;
fig = figure(); % create a figure
hold on;
for frame = 0:NFrames
   T = load (strcat('../../Tests/Sample/Ttest_50x50_230.txt'));
   N = load (strcat('../T/',int2str(frame),'.txt'));

   T = reshape(T,[(2*NX-1), (2*NY-1)]);
   N = reshape(N,[(2*NX-1), (2*NY-1)]);
   set(gcf,'position',[140,140,1000,400]) % x0, y0, width, height
   %colormap hot
   M1min = min(T(:));
   M1max = max(T(:));
   M2min = min(N(:));
   M2max = max(N(:));        
   subplot(1,2,1)
   image(T,'CDataMapping','scaled');
   title('Tumor')
   colorbar
   caxis([M1min M1max])
   subplot(1,2,2)
   image(N,'CDataMapping','scaled');
   title('Tumor lisado')
   colorbar
   caxis([M2min M2max])
   
   F(frame+1) = getframe(fig);
end

writerObj = VideoWriter('TumorLysis.avi');
writerObj.FrameRate = 1;
open(writerObj);
writeVideo(writerObj, F)
hold off;
close(writerObj);
