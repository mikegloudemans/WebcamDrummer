clear; clc; close all; fclose('all');

music_file = '../m4a/U Cant Touch This.m4a';
aud_size = m4aread(music_file,'size');
aud_size = aud_size(1);
[d_orig,sr] = m4aread(music_file,aud_size/3,20, 1, 4);
wavwrite(d_orig,sr,'U Cant Touch This.wav');