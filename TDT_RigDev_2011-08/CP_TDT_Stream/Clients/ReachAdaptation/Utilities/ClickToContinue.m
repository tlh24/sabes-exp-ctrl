function time = ClickToContinue( hMouse, timeout, buttons )

% FUNCTION  time = ClickToContinue( hMouse )
% FUNCTION  time = ClickToContinue( hMouse , timeout )
% FUNCTION  time = ClickToContinue( hMouse , timeout, buttons )
%
% INPUT
%   hMouse  : handle to a mouse server (VisServer.MouseServer)
%   timeout : maximum time to pause
%   buttons : boolean 3-vector indicating which buttons matter
%
% OUTPUT
%   time    : scalar, time elapsed in seconds
%
% NOTES
%
%   The routine pauses until a mouse button is pressed.  The
%   optional output is the time elapsed between function call and
%   1st button press.
%
%   If the optional timeout variable is set, the routine will keep
%   control for no more than that time.  If no mouse button is pressed
%   then, the returned time will be set to time=-1; If timeout<=0,
%   then the timeout is infinite (which is the default behavior).
%
%   If the optional buttons array is used, only the buttons which are
%   indicated will be considered.
%
%   This routine begins with a call to the "reset" method, thereby
%   clearing any existing mouse button presses.

%%%%%% OPTIONS

%% TIMEOUT 
if(nargin<2),
  timeoutFlag = 0;
else
  if(timeout<=0) timeoutFlag=0;
  else timeoutFlag=1;
  end
end

%% BUTTONS
if(nargin<3),
  buttons=[1 1 1]';
else,
  buttons=buttons(:);
  if(size(buttons,1)~=3), 
    error(['ClickToContinue: 3rd arugment BUTTONS must be 3x1']);
  end
end

%%%%%% WAIT

invoke(hMouse,'capture');  % capture Mouse to VisWindow!
invoke(hMouse,'reset');  % clear previous button presses

timedOut=0;
tic; 
while( hMouse.click*buttons==0 & ~timedOut )
  if( timeoutFlag ),
    if(toc>timeout), timedOut=1;
    end
  end
end

%% Output
if(nargin>0),
  if(timedOut) time=-1;
  else time=toc;
  end
end
