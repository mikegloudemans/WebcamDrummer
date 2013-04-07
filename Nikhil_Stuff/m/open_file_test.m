clear; clc;

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
        new_songs{new_count} = curr_song;
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