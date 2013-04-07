% Nikhil Saxena
% hackBlue
% 04/06/13

% function [] = ghWriter()

%% Initialize
clear; clc; close all; 

%% Parameters
file_name = 'U Cant Touch This.m4a';

%% Read M4A Audio
aud_size = m4aread(file_name,'size');
[d_orig,sr] = m4aread(file_name,aud_size(1), 1, 4);

d = d_orig(1:end/20);

% figure;
% subplot(1,2,1); spectrogram(d(:,1),sr);
% subplot(1,2,2); plot(d(:,1));

[S_orig,F,T,P] = spectrogram(d(:,1),sr);
F = F*pi*sr/(2*pi);

out_orig = istft(S_orig); 
% figure; plot(out_orig);

snare_ind = find(F >= 150);
snare_ind = snare_ind(1);

S = zeros(size(S_orig));
for i = 1:length(T)
    curr_point = abs(S_orig(snare_ind,i))
    ovr_max = max(max(abs(S_orig(snare_ind,:))));
    
    if (curr_point > 0.75*ovr_max)
       S(snare_ind,i) = ovr_max;
    end
end
out_snare = istft(S); 

figure; plot(out_snare);

sound(out_orig+15*out_snare,sr);

%% Read Auxiliary Sounds
% [snare_drum,snare_fs] = wavread('snare_drum.wav');
% % soundsc(snare_drum,snare_fs);
% 
% [find_snare,lags] = xcorr(d,snare_drum);
% figure; plot(lags,find_snare);
% 
% find_snare = (find_snare >= max(max(find_snare))*0.6);
% find_snare = double(find_snare);
% find_snare = find_snare(max(lags):end-1);
% figure; plot(find_snare);
% d_snare = find_snare;
% 
% NFFT = 2^nextpow2(length(snare_drum)); % Next power of 2 from length of y
% fft_snare = fft(snare_drum,NFFT)/length(snare_drum);
% f = snare_fs/2*linspace(0,1,NFFT/2+1);
% figure; plot(f(1:floor(0.4*end)),2*abs(fft_snare(1:floor(0.4*(NFFT/2+1))))) 
% 
% % Augmented Frequencies
% aug_freq = [60; % bass drum
%             150]; % snare drum
% 
% aug_indices = zeros(size(my_spect),2);
        
% Output Sound
% soundsc(d+15*d_snare,sr);


% tempo_beats = beat2(d,sr); % Tempo Array
% tempo_sum = 0;
% for i=1:length(tempo_beats)
%     tempo_sum = tempo_sum + tempo_beats(i);
% end
% tempo_avg = tempo_sum/length(tempo_beats); % Seconds between Beats
% d_beats = mkblips(tempo_beats,sr,length(d))







