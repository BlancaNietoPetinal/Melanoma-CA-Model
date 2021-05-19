%mat2 = load('GaussianMat2.txt');
NX = 40; 
NY = 40;
mat1 = load('../Results/DELETE/DIV.txt');

mat1 = reshape(mat1,[(2*NX-1),(2*NY-1)]);

Mmin = min(mat1(:));
Mmax = max(mat1(:));
figure,
image(mat1,'CDataMapping','scaled');
title('\theta_{DIV}')
colorbar
caxis([Mmin Mmax])
drawnow

