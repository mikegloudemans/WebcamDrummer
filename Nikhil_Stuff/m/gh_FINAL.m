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
    file_name = '../m4a/03 YMCA.m4a';

    %% Scout File for Size and Max
    aud_size = m4aread(file_name,'size');
    aud_size = aud_size(1);
    full_file = m4aread(file_name,aud_size/20,20,1,4);
    ovr_max = max(full_file);
    clearvars full_file;
    
    %% Read M4A Audio
    segment_size = 200000;
    num_segments = ceil(aud_size/segment_size);
    
    waitbar_handle = waitbar(0,'Generating Level');
    
    nn_segments_max = floor(num_segments / 1);
    for nn = 1:nn_segments_max
        waitbar(nn/nn_segments_max);
                
        % Establish Range for Current Audio Segment
        range_start = (nn-1)*segment_size+1;
        if (nn == num_segments)
            range = [range_start, aud_size];
        else            
            range = [range_start, nn*segment_size];
        end              
        
        [d_orig,sr] = m4aread(file_name,range,20, 1, 4);
        d_orig = single(d_orig);
   
%         figure; plot(d_orig); title('Original');

        %% Adaptive Threshold Processing
%         window_size = 100;
%         num_windows = floor(length(d_orig)/window_size);
% 
%         adapt_thresh = zeros(length(num_windows));
%         for i = 1:num_windows
%             if ((length(d_orig) - (i-1)*window_size+1) < window_size)
%                 window = d_orig((i-1)*window_size+1:end);
%             else
%                 window = d_orig((i-1)*window_size+1:(i-1)*window_size+window_size);
%             end      
% 
%             % Mean of Positive Values    
%             temp_thresh = mean(window);    
%             adapt_thresh(i) = temp_thresh;
%         end
%         ovr_thresh = mean(adapt_thresh);
% 
%         clearvars adapt_thresh temp_thresh window num_windows window_size

        %% Keep This Til Fix Adaptive Thresh
        ovr_thresh = 0.45*ovr_max;  
        
        %% Apply Threshold and Store Indices    
        blip_time = zeros(length(d_orig/2),1);
        blip_count = 0;

%         refractory_period = 0.1;
        in_refr = 0;          
        refractory_period = 0.25;
        refr_start = 0;

        max_vol = max(d_orig);
        
%         d_orig = downsample(d_orig,sr);
        
        for i = 1:length(d_orig)
            if (in_refr) && (i/sr - refr_start < refractory_period)
                continue;
            end
 
            if (d_orig(i) >= ovr_thresh)
                d_orig(i) = 4*max_vol;

                blip_count = blip_count + 1;
                blip_time(blip_count) = (range_start+i)/sr;

                refr_start = i/sr;
                in_refr = 1;
            end   
        end
        
%         figure; plot(d_orig); title('With Blips');

%         soundsc(d_orig,sr);
   
        %% Apply Transitions
        clearvars d_orig;   

        %% Split Information into Several Drums
        blip_time(blip_count+1:end) = [];
                
        % Random Number in [1,5]
        r = floor(rand(length(blip_time),1)*5)+1;   
        
        % Initialize Cells
        blip_cell = cell(5,1);
        blip_count = ones(5,1);
        blip_cell{1} = zeros(length(blip_time),1);
        blip_cell{2} = zeros(length(blip_time),1);
        blip_cell{3} = zeros(length(blip_time),1);
        blip_cell{4} = zeros(length(blip_time),1);
        blip_cell{5} = zeros(length(blip_time),1);
     
        % Randomize
        for i = 1:length(r)
            blip_cell{r(i)}(blip_count(r(i))) = blip_time(i);
            blip_count(r(i)) = blip_count(r(i)) + 1;            
        end
        
        clearvars r blip_time
        
        % Eliminate Excess Zeros
        for i = 1:5
           blip_cell{i}(blip_count(i):end) = []; 
        end
        
        %% Write to GH File        
        % File Naming
        name_part = regexp(file_name,'/','split');
        name_part = name_part{length(name_part)};
        name_part = regexp(name_part,'\.','split');
        name_part = name_part(1);
        name_part = char(strcat(name_part,'.gh'));

        % Open File
        if (nn == 1) 
            % If First Time, Write Over
            fID = fopen(name_part,'w');
        else
            % Else, Append to End
            fID = fopen(name_part,'a');
        end

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
    end
    
    close(waitbar_handle);
    
    %% Clear Unnecessary Variables
%     close all;
%     clearvars -except song_files ii    
end