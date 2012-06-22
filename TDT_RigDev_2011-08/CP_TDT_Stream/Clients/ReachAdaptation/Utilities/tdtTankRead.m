%
% The following has been extracted from the examples in
% C:\TDT\OpenEx\Examples1.1\TTankX_Example\Matlab\
%
function tdtTankRrad 
%
% This is a sample bit of matlab code for accessing data in a Tank
% and displaying it on a couple of plots.  Most calls return 1
% if they are successful else they return 0.  If a variant is returned
% then a -1 means Empty variant or a NULL return.

% First extantiate a variable for the ActiveX wrapper interface
% that connect to the TTankServer and reads data from Tank
TTX = actxcontrol('TTank.X');

server  = 'cannonball';
myTank  = 'SignalSnippetsAQ_DT1_111304';
myBlock = 'Block-2';


% Then connect to a server.
% Local version %%%% invoke(TTX,'ConnectServer', 'Local', 'Me')
if(~invoke(TTX,'ConnectServer','cannonball','Me'))
    error('Cant connect to TDT Server');
end

% Now open a tank for reading.
fprintf(1,'Open Tank...\n')
%% invoke(TTX,'OpenTank', 'DemoTank', 'R')
invoke(TTX,'OpenTank',myTank,'R')

% Select the block to access
invoke(TTX,'SelectBlock',myBlock)

get(TTX)
%%%%%%%%%%%%

fprintf(1,'Starting Reading Events ...\n\n')

% Get all of the Snips across all time for channel-1
% after this call they are stored localing within the ActiveX
% wrapper code.  N will equal the number of events read.

maxNevents = 10000;
channel = 1;
evStart=0.0;
evEnd=0.0;

%N = invoke(TTX, 'ReadEventsV', 10000, 'Snip', 1, 0, 0.0, 0.0, 'ALL');
N = invoke(TTX, 'ReadEventsV', maxNevents, 'Snip', channel, 0, evStart, evEnd, 'ALL');

fprintf(1,'Number of cached events = %d\n',N)

% To parse out elements of the returned data use the
% ParseEvV and ParseEvInfoV calls as follow.

% To get all waveform data for all the events read just call
% the first 0 is the index offset into the list returned above
% the second arg is the number you would like parsed out and returned
W = invoke(TTX, 'ParseEvV', 0, N);
plot(W);
pause

% To get other information about the record events returned call
% ParseEvInfoV.  This call has the same two parameters as ParseEvV
% with one more param to indicate which bit of information you
% want returned.  The following are valid values for the 3rd 
% parameter:
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
TS = invoke(TTX, 'ParseEvInfoV', 0, N, 6);
Hist(TS, 30);
pause

SR = invoke(TTX, 'ParseEvInfoV', 0, N, 9);
Hist(SR, 40);
pause

% Any single value (in this case chan no.) can be returned like this:
chan = invoke(TTX, 'ParseEvInfoV', 3, 0, 4)

% The same can be done to return single waveforms like:
onewave = invoke(TTX, 'ParseEvV', 3, 0)

% Finally the ParseEvV call can be used to return the value(s)
% for a bunch of scalar events:
N = invoke(TTX, 'ReadEventsV', 10000, 'SwpN', 0, 0, 0.0, 0.0, 'ALL')
freqlist = invoke(TTX, 'ParseEvV', 0, N);

% Or a single value can be returned:
onefreq = invoke(TTX, 'ParseEvV', 3, 0)


%%%%%%%%%%%%

fprintf(1,'Close Tank and Release Server...\n')
invoke(TTX,'CloseTank')
invoke(TTX,'ReleaseServer')

fprintf(1,'End Tank Read.')
