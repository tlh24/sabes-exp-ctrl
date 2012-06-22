function MFMonkeyEye(widthFract,heightFract)
%  function MFMonkeyEye(widthFract,heightFract)
%
%
%
%
%
global NO_ISCAN
NO_ISCAN = 0;

if nargin == 0
    widthFract = 0.25;
    heightFract = 0.25;
elseif nargin == 2
else
    error('Wrong # of input args. Input: (widthFract,heightFract)');
end

Params = SensIntReaching_Params(0);

curdir = pwd;
cd('C:\Lab\matlab\MonkeyEyeCalib');
h = MonkeyEye;

xch = findobj(h,'tag','X0_input');
ych = findobj(h,'tag','Y0_input');
xwh = findobj(h,'tag','Xwid_input');
ywh = findobj(h,'tag','Ywid_input');

xph = findobj(h,'tag','Xpt_input');
yph = findobj(h,'tag','Ypt_input');


set(xch,'string',num2str(Params.wsCenter(1)));
set(ych,'string',num2str(Params.wsCenter(2)));
set(xwh,'string',num2str(Params.wsHalfWidths(1)*widthFract));
set(ywh,'string',num2str(Params.wsHalfWidths(2)*heightFract));
set(xph,'string',num2str(4));
set(yph,'string',num2str(3));

