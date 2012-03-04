% A simple routine to plot the k-omega output using matlab
% open the raw gram data file
fid = fopen('gramOut','r');
% fread the data into "a"
a = fread(fid,[128,513],'float');
% Swap so that broadside sits in the middle of the matrix
% a = [a(65:128,:);a(1:64,:)];
fclose(fid);
% output an image of the log of the data
imagesc(a);
set(gca,'YTickLabelMode','manual')
set(gca,'YTickMode','manual')
set(gca,'YTick',[1 32 64 96 128])
set(gca,'YTickLabel',[0 60 90 120 180])
set(gca,'YAxisLocation','right')
xlabel('Frequency (Hz)')
% not actualy bearing.
% y axis labels are a function of x axis
ylabel('Bearing')
