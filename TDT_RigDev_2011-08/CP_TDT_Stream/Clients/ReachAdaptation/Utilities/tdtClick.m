function [outfreq, outangle]=tdtClick(freq,angle)

% FUNCTION tdtClick(freq,angle)
%
% Set the following variables
%
% freq - scalar>0 - frequency in Hz
%      - 0        -  turn click off
% angle - scalar - angle in degrees

global TDTdev
persistent lastFreq lastAngle 

%fprintf(1,'Input values: angle= %d, freq = %d \n',angle,freq )

%% First Time
if( isempty(lastFreq) ) 
    lastFreq=0;
    lastAngle=0;
end

%% If no input values, return current frequency and angle
if (nargin==0) 
   outfreq  = lastFreq;
   outangle = lastAngle;
   return;
end

%% Turn off
if( freq == 0 )
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickGate',0);
    lastFreq=freq;
    return
end

%% Turn on
if( lastFreq == 0 )
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickGate',1);
end

%% Evaluate possible combinations 
if( freq == lastFreq & angle == lastAngle )                  %% Nothing has changed
    %fprintf(1,'1 - Output values: angle= %d, freq = %d \n',angle,freq)
    return;     
elseif ( freq == lastFreq & angle ~= lastAngle)              %% Angle only changed
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickAngle',angle);    
    lastAngle = angle;
    %fprintf(1,'2 - Output values: angle= %d, freq = %d \n',angle,freq)
elseif ( freq ~= lastFreq & angle == lastAngle)              %% Frequency only changed
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickFreq',freq);
    lastFreq = freq;
    %fprintf(1,'3 - Output values: angle= %d, freq = %d \n',angle,freq)
else                                                         %% Both frequency and angle changed
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickAngle',angle);
    invoke(TDTdev,'SetTargetVal','RX5(1).ClickFreq',freq);
    lastFreq  = freq;
    lastAngle = angle;
    %fprintf(1,'4 - Output values: angle= %d, freq = %d \n',angle,freq)
end

%fprintf(1,'Set value: angle = %d , freq = %d', angle, freq )

