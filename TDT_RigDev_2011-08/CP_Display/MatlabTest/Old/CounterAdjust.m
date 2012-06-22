% strVisServerName ='VisServer1';
strVisServerName ='grappelli';
hW = actxserver('VisServer.VisWindow',strVisServerName);  pause(.1);

% Position and size are in fractions of the screen size 
h   =.02;
w   =.3;
off =.1;
left   = 1-w-off;
bottom = 1-h;

hW.logmode =1;
hW.counter=15;
increment = 0.01;

while 1
  hW.counterpos=[left bottom]; 
  hW.countersize=[w h];
  hW.counter=15;
  hW.drawnow();
  
  reply = input('L - left R - right W - wider, N-narrower, Q - quit:', 's');
  if isempty(reply)
      reply = 'Q';
  end  

  switch reply
    case 'l'
       left = left - increment;
    case 'r'
       left = left + increment;
    case 'w'
       w = w + increment;
    case 'n'
       w = w - increment;
    case 'q'
       break;
    otherwise
       fprintf('Try again');
  end  

end

left
w


if iscom(hW)  release(hW); end;


