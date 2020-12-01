NX = 6;
NY = 6;
NFrames = 3;
%showMultipleFrames(NFrames,NX,NY); 
[T, N] = setFrame(NFrames, NX, NY);
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
        framestr = strcat('00',int2str(frame));
    elseif frame<100
        framestr = strcat('0',int2str(frame));
    else
        framestr = int2str(frame);
    end
    
    
    %ISAS COMPUTER RESULTS
    %mat1 = load (strcat('../../DELETE/T/',framestr,'.txt'));
    %mat2 = load (strcat('../../DELETE/N/',framestr,'.txt'));
    
    %TEST
    %mat1 = load (strcat('../../Tests/DELETE/T.txt'));
    %mat2 = load (strcat('../../Tests/DELETE/T.txt'));
    %mat2 = load (strcat('../../Tests/tumor_lysis/E.txt'));
    %mat2 = load (strcat('../../Tests/Sample/Ntest_6x6_15.txt'));

    %RESULTS
    mat1 = load (strcat('../../Tests/Sample/Ttest_6x6_20.txt'));
    %mat2 = load (strcat('../../Tests/Sample/Ntest_6x6_20.txt'));
    %mat1 = load (strcat('../../Tests/Sample/Trk4.txt'));
    %mat2 = load (strcat('../../Tests/Sample/Hrk4.txt'));
    %mat1 = load (strcat('../T/destruction',int2str(frame),'.txt'));
    mat2 = load (strcat('../T/effector',int2str(frame),'.txt'));
    %mat1 = load (strcat('../T/',framestr,'.txt'));
    %mat2 = load (strcat('../N/',framestr,'.txt'));
    
    mat1 = reshape(mat1,[(2*NX-1), (2*NY-1)]);
    mat2 = reshape(mat2,[(2*NX-1), (2*NY-1)]);
end

