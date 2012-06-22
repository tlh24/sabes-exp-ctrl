function currfreq=tdtTone(freq)

% FUNCTION tdtTone(freq)
%
% Set tone frequence
%
% freq - scalar>0 - frequency in Hz
%      - 0        -  turn tone off
%      - []       -  return current tone
%

global TDTdev
persistent lastFreq

%% First Time
if( isempty(lastFreq) ) lastFreq=0; end

%% Return tone
if( isempty(freq) ) currfreq=lastFreq; return; end

%% Nothing has changed
if( freq == lastFreq) return; end

%% Turn off
if( freq == 0 )
    invoke(TDTdev,'SetTargetVal','RP2(1).ToneGate',0);
    lastFreq=freq;
    return
end

%% Set Freq
invoke(TDTdev,'SetTargetVal','RP2(1).ToneFreq',freq);

%% Turn on
if( lastFreq == 0 )
    invoke(TDTdev,'SetTargetVal','RP2(1).ToneGate',1);
end
lastFreq=freq;
