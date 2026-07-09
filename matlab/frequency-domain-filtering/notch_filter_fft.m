clc; clear; close all;
% 1. Görüntünün Okunması ve Gösterilmesi
img = imread('noisy_image.png');
if size(img, 3) == 3
    img = rgb2gray(img); 
end
img_double = im2double(img); 

[M, N] = size(img_double);
disp(['Görüntü Boyutu: ', num2str(M), 'x', num2str(N)]);

% 2. 2B Fourier Dönüşümünün Hesaplanması
F = fft2(img_double); 
F_shifted = fftshift(F); 

% 3. Genlik Spektrumunun Görselleştirilmesi
amp_spec = abs(F_shifted); 

log_amp_spec = log(1 + amp_spec);
% 4. Gürültü Frekanslarının Belirlenmesi
u0 = floor(M/2) + 1;
v0 = floor(N/2) + 1;

temp_spec = log_amp_spec;
[X, Y] = meshgrid(1:N, 1:M);

D_center = sqrt((X - v0).^2 + (Y - u0).^2);
temp_spec(D_center < 30) = 0; 

threshold = max(temp_spec(:)) * 0.75; 
peaks = temp_spec > threshold;

[peak_row, peak_col] = find(peaks);

disp('Tespit Edilen Gürültü Frekans Koordinatları (Satır, Sütun):');
for k = 1:length(peak_row)
    fprintf('Pik %d: (%d, %d)\n', k, peak_row(k), peak_col(k));
end

% 5. Frekans Alanında Filtre Tasarımı
radius = 4; 
H = ones(M, N); 


for k = 1:length(peak_row)
    dist = sqrt((X - peak_col(k)).^2 + (Y - peak_row(k)).^2);
    H(dist <= radius) = 0; 
end

G = F_shifted .* H;
log_G_spec = log(1 + abs(G));

% 6. Ters Fourier Dönüşümü ile Görüntünün Geri Oluşturulması
G_ishift = ifftshift(G); 
img_clean = real(ifft2(G_ishift)); 

img_clean = (img_clean - min(img_clean(:))) / (max(img_clean(:)) - min(img_clean(:)));

% 7. Görselleştirme ve Rapor İçin Çıktılar
figure('Name', 'Bulgular', 'Position', [100, 100, 1200, 800]);

subplot(2,4,1); imshow(img_double); title('1. Gürültülü Görüntü');
subplot(2,4,2); imshow(amp_spec, []); title('2. Fourier Genlik Spektrumu');
subplot(2,4,3); imshow(log_amp_spec, []); title('3. Logaritmik Spektrum');
subplot(2,4,4); imshow(temp_spec, []); title('4. Gürültü Frekansları (Pikler)');
subplot(2,4,5); imshow(H, []); title('5. Filtre Maskesi');
subplot(2,4,6); imshow(log_G_spec, []); title('6. Filtrelenmiş Spektrum');
subplot(2,4,7); imshow(img_clean); title('7. Temizlenmiş Görüntü');

% Orijinal ve Temizlenmiş Görüntü 
figure('Name', 'Karşılaştırma', 'Position', [200, 200, 1000, 500]);
subplot(1,2,1); imshow(img_double); title('Orijinal Gürültülü Görüntü');
subplot(1,2,2); imshow(img_clean); title('Filtrelenmiş Temiz Görüntü');
