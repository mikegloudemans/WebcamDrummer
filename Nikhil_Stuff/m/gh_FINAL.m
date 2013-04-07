% Nikhil Saxena
% hackBlue
% 04/06/13

% function [] = gh_ALTERNATE()

%% Initialize
clear; clc; close all; fclose('all');

%% File Handling
% Get Info from File
fid = fopen('MUSIC_FILE.txt','r');
new_count = 0;
song_count = 0;
while (~feof(fid))       
    song_count = song_count+1;
    song_name(song_count) = textscan(fid,'%s',1,'delimiter','\n');
    
    % Get Rid of Empty Cells
    emptyCells = cellfun(@isempty,song_name);
    if (sum(emptyCells > 0))        
        song_name(emptyCells) = [];
        continue;
    end
    
    % Check to See Whether New Song or Not
    curr_song = char(song_name{song_count});
    if (curr_song(1) == '^')
        new_count = new_count+1;
        new_songs{new_count} = curr_song(2:end);
    end   
end
fclose(fid);

% Write Everything to File, Removing '^'
fid = fopen('MUSIC_FILE.txt','w');
for i = 1:length(song_name)
    curr_song = char(song_name{i});
    
    if (curr_song(1) == '^')
        curr_song = curr_song(2:end)
        fprintf(fid,'%s',curr_song);
    else
        fprintf(fid,'%s',curr_song);        
    end
    
    fprintf(fid,'\n');
end
fclose(fid);

for ii = 1:1 %length(new_songs)
    %% Create GH Files
%     file_name = char(new_songs{ii});
    file_name = '../m4a/U Cant Touch This.m4a';

    %% Read M4A Audio
    aud_size = m4aread(file_name,'size');
    
%     for nn = 1:50
    
    [d_orig,sr] = m4aread(file_name,aud_size(1)/30,20, 1, 4);
    d_orig = single(d_orig);
    
%     d = d_orig(1:floor(end/10));
%     figure; plot(d_orig); title('Original');

    %% Adaptive Threshold Processing
    window_size = 100;
    num_windows = floor(length(d_orig)/window_size);

    adapt_thresh = zeros(length(num_windows));
    for i = 1:num_windows
        if ((length(d_orig) - (i-1)*window_size+1) < window_size)
            window = d_orig((i-1)*window_size+1:end);
        else
            window = d_orig((i-1)*window_size+1:(i-1)*window_size+window_size);
        end      

        % Mean of Positive Values    
        temp_thresh = mean(window);    
        adapt_thresh(i) = temp_thresh;
    end
    ovr_thresh = mean(adapt_thresh);

    clearvars -except ii song_files ovr_thresh d_orig sr file_name
    
    %% Keep This Til Fix Adaptive Thresh
    ovr_thresh = 0.45;

    %% Apply Threshold and Store Indices    
    blip_time = zeros(length(d_orig/2),1);
    blip_count = 0;
    
    refractory_period = 0.1;
    in_refr = 0;
    refr_start = 0;
    
    max_vol = max(d_orig);
    for i = 1:length(d_orig)
        if (i/sr - refr_start < refractory_period)
            continue;
        end
        
        if (d_orig(i) >= ovr_thresh*max_vol)
            d_orig(i) = 4*max_vol;
            
            blip_count = blip_count + 1;
            blip_time(blip_count) = i/sr;
            
            refr_start = i/sr;
        end   
    end

%     figure; plot(d_orig); title('With Blips');


    %% Apply Transitions
    clearvars d_orig;    
    
    
    %% Split Information into Several Drums
    blip_time(blip_count+1:end) = [];
    
    blip_cell = cell(5,1);
    blip_cell{1} = zeros(length(blip_time),1);
    blip_cell{2} = zeros(length(blip_time),1);
    blip_cell{3} = zeros(length(blip_time),1);
    blip_cell{4} = zeros(length(blip_time),1);
    blip_cell{5} = zeros(length(blip_time),1);
    
    blip_count = 1;
    for i = 1:5:length(blip_time)
        diff = length(blip_time)-i;
        if (diff > 5)
            blip_cell{1}(blip_count) = blip_time(i);
            blip_cell{2}(blip_count) = blip_time(i+1);
            blip_cell{3}(blip_count) = blip_time(i+2);
            blip_cell{4}(blip_count) = blip_time(i+3);
            blip_cell{5}(blip_count) = blip_time(i+4);
        elseif (diff > 4)
            blip_cell{1}(blip_count) = blip_time(i);
            blip_cell{2}(blip_count) = blip_time(i+1);
            blip_cell{3}(blip_count) = blip_time(i+2);
            blip_cell{4}(blip_count) = blip_time(i+3);
        elseif (diff > 3)
            blip_cell{1}(blip_count) = blip_time(i);
            blip_cell{2}(blip_count) = blip_time(i+1);
            blip_cell{3}(blip_count) = blip_time(i+2);
        elseif (diff > 2)
            blip_cell{1}(blip_count) = blip_time(i);
            blip_cell{2}(blip_count) = blip_time(i+1);
        elseif (diff > 1)
             blip_cell{1}(blip_count) = blip_time(i);
        end
        
        blip_count = blip_count + 1;
    end    
    
    for i = 1:5
        blip_cell{i}(blip_count:end) = [];
    end
    
    %% Write to GH File        
    % File Naming
    name_part = regexp(file_name,'/','split');
    name_part = name_part{length(name_part)};
    name_part = regexp(name_part,'\.','split');
    name_part = name_part(1);
    name_part = char(strcat(name_part,'.gh'));
    
    % Open File
    fID = fopen(name_part,'w');
    
    % Print Drum One
    fprintf(fID,'1:');    
    gh_one = blip_cell{1};
    for i = 1:length(gh_one)
        fprintf(fID,'%0.4f',gh_one(i));
        
        if (i~=length(gh_one))
            fprintf(fID,',');
        end
    end
    fprintf(fID,'\n');
    
    % Print Drum Two
    fprintf(fID,'2:');    
    gh_two = blip_cell{2};
    for i = 1:length(gh_two)
        fprintf(fID,'%0.4f',gh_two(i));
        
        if (i~=length(gh_two))
            fprintf(fID,',');
        end
    end
    fprintf(fID,'\n');
    
    % Print Drum Three
    fprintf(fID,'3:');    
    gh_three = blip_cell{3};
    for i = 1:length(gh_three)
        fprintf(fID,'%0.4f',gh_three(i));
        
        if (i~=length(gh_three))
            fprintf(fID,',');
        end
    end
    fprintf(fID,'\n');
    
    % Print Drum Four
    fprintf(fID,'4:');    
    gh_four = blip_cell{4};
    for i = 1:length(gh_four)
        fprintf(fID,'%0.4f',gh_four(i));
        
        if (i~=length(gh_four))
            fprintf(fID,',');
        end
    end
    fprintf(fID,'\n');
    
    % Print Drum Five
    fprintf(fID,'5:');    
    gh_five = blip_cell{1};
    for i = 1:length(gh_five)
        fprintf(fID,'%0.4f',gh_five(i));
        
        if (i~=length(gh_five))
            fprintf(fID,',');
        end
    end
    fprintf(fID,'\n');   
    fclose(fID);
    
    %% Clear Unnecessary Variables
%     close all;
%     clearvars -except song_files ii    
end