clear; clc; close all; fclose('all');

gh_file = 'U Cant Touch This.gh';
music_file = '../m4a/U Cant Touch This.m4a';

fid = fopen(gh_file);
blip_counter = 0;

blip_times = [];

while (~feof(fid))
	% Line
	temp = textscan(fid,'%s',1,'delimiter','\n');
    
    % Get Rid of Empty Cells
    emptyCells = cellfun(@isempty,temp);
    if (sum(emptyCells > 0))        
        temp(emptyCells) = [];
        continue;
    end
    
    % Get Rid of Colon
    line = char(temp{1});
    line = line(3:end);
    
    % Parse By Comma
    line = regexp(line,',','split');
    
    for i = 1:length(line)       
       blip_times = [blip_times,str2num(line{i})];
    end
end
fclose(fid);

% Sort
blip_times = sort(blip_times);

% Read Music
aud_size = m4aread(music_file,'size');
aud_size = aud_size(1);
[d_orig,sr] = m4aread(music_file,aud_size,20, 1, 4);

% Combine
blip_indices = floor(blip_times*sr);

ovr_max = max(d_orig);
d_orig(blip_indices) = 30*ovr_max;

soundsc(d_orig,sr);











