function W = DataTank2RawBinary(tankname,block,server,client)

% FUNCTION W = DataTank2RawBinary(tankname,block,server,client)
%
% Read raw neural data from Tank and save in a binary
% file that Plexon's Offline Sorter can read
% Filename is  "<tankname>_Block-<block>_raw.bin" 
%
% INPUT:
%   tank    - tank name (string)
%   block   - block number (integer)
%   server  - server name (string), OPTIONAL: default is 'Local'
%   client  - client name (string), OPTIONAL: default is ''
%
% OUTPUT:
%   The output is optional, as the data will be saved to a file
%   in any case
%
%   W   - raw waveform (doubles)

MAX_EVENTS = 1000000;

if(nargin<1),
	fprintf(1,'Use: ReadDataTank(tank,block)\n')
	return
end

%servername = 'cannonball';                   % server
servername = 'Local';                         % server
clientname = 'Me';                            % change this if not Local server
blockname  = sprintf('Block-%d',block);    % block (case-sensitive!)
filename   = sprintf('%s_%s_raw.bin',tankname,blockname);

%%%%%  Establish TDT Connection
TTX = actxcontrol('ttank.x');

if (invoke(TTX, 'ConnectServer', servername, clientname) ~= 1)
	fprintf(1, '\n+++ Error connecting to server.\n')
	return
end

if (invoke(TTX, 'OpenTank', tankname, 'r') ~= 1)
	fprintf(1, '\n+++ Error opening tank or tank %s does not exist.\n', tankname)
	return
end

if (invoke(TTX, 'SelectBlock', blockname) ~= 1)
	fprintf(1, '\n+++ Error selecting block or %s does not exist.\n',blockname)
	return
end

fprintf(1,'\nConnected to Tank %s, %s\n\n',tankname,blockname);


%%%% Get Raw Data

%% Get locally stored all data for 'var'. Nev = number of events read.
Var       = 'RAWs';
Channel   = 0;    % All Channels
SortCode  = 0;    % All Sorted Spikes Channels

%%%%%%%%%%%% NEW

%% Open File
% fid = fopen(filename,'wb');

%% Read Data
Scale = 1/50;
DT    = 2;
t0    = 0;
Nstep = 1;
Ntot  = 0;
Itot  = 0;
Freq  = 0;
while Nstep>0,
	% Read a chunk of data from Tank to TTX
	Nstep = invoke(TTX, 'ReadEventsV', MAX_EVENTS, Var, Channel, SortCode, t0, t0+DT, 'ALL');
	if(Nstep==0) continue; end
	
	% Reach chunk to matlab
	% Returns single (16bit) Integer
	W = invoke(TTX, 'ParseEvV', 0, Nstep);
	if(Freq==0)
		Freq = invoke(TTX, 'ParseEvInfoV', 0, Nstep, 9);        % sampling frequency
		Freq = Freq(1);
    TimeStamp0 = invoke(TTX, 'ParseEvInfoV', 0, Nstep, 6);        % timestamp
    TimeStamp0 = TimeStamp0(1);
	end

    % Write It
% 	Istep = fwrite(fid,W,'int16');
% 	if(Istep==0) keyboard; end
	% keyboard
    
	% Step
	Ntot = Ntot + Nstep;
% 	Itot = Itot + Istep;
	t0=t0+DT;
end
fprintf(1,'Read %d blocks,  Wrote %d integers (%.1f sec @ %.0f Hz)\n',Ntot,Itot,Itot/Freq,Freq)
fprintf('Timestamp of block 0 is  (%.1f sec)\n', TimeStamp0)

%% Close File
% fclose(fid);


%% Clean Up
if(nargout<1) clear W; end
invoke(TTX, 'CloseTank')


% The following are valid values for the 3rd parameter of ParseEvInfoV:
%   1  = Amount of waveform data in bytes
%   2  = Record Type (see TCommon.h)
%   3  = Event Code Value
%   4  = Channel No.
%   5  = Sorting No.
%   6  = Time Stamp
%   7  = Scalar Value (only valid if no data is attached)
%   8  = Data format code (see TCommon.h)
%   9  = Data sample rate in Hz. (not value unless data is attached)
%   10 = Not used returns 0.
%   0  = Returns all values above
