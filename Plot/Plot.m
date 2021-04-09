NX = 110;
NY = 110;
NFrames =   9;
%showMultipleFrames(NFrames,NX,NY); 

[T, N] = setFrame(NFrames, NX, NY);
%sum(T(:));
plotFrame(T, N)
function showMultipleFrames(NFrames, NX, NY)
    figure(); % create a figure
    for frame = 0:NFrames
       [T, N] = setFrame(frame, NX, NY);
       plotFrame(T,N);
    end
end

function plotFrame(mat1, mat2)
        set(gcf,'position',[140,140,1000,400]) % x0, y0, width, height
        %colormap hot
        M1min = min(mat1(:));
        M1max = max(mat1(:));
        M2min = min(mat2(:));
        M2max = max(mat2(:));        
        subplot(1,2,1)
        image(mat1,'CDataMapping','scaled');
        title('Tumor')
        colorbar
        caxis([M1min M1max])
        subplot(1,2,2)
        image(mat2,'CDataMapping','scaled');
        title('Nutrientes de division celular')
        colorbar
        caxis([M2min M2max])
        drawnow
end

function [mat1, mat2] = setFrame(frame, NX, NY)
    if frame<10
        framestr = strcat('000',int2str(frame));
    elseif frame<100
        framestr = strcat('00',int2str(frame));
    elseif frame<1000
        framestr = strcat('0',int2str(frame));
    else
        framestr = int2str(frame);
    end
    %DESTRUCTION
    %mat1 = load (strcat('../Results/Destruction/T/',int2str(frame),'.txt'));
    %mat2 = load (strcat('../Results/Destruction/E/',int2str(frame),'.txt'));
    %GENERATION
    mat1 = load (strcat('../Results/Disconnected/T/0955.txt'));
    mat2 = load (strcat('../Results/Papillary/N/0900.txt'));
    %mat2 = load (strcat('../Results/Generation/N/001p.txt'));
    %EXAMPLE
    %mat1 = load (strcat('../Tests/Sample/Ttest_50x50_230.txt'));
    %mat2 = load (strcat('../Tests/Sample/Ntest_50x50_230.txt'));
    
    mat1 = reshape(mat1,[(2*NX-1), (2*NY-1)]);
    mat2 = reshape(mat2,[(2*NX-1), (2*NY-1)]);
end

