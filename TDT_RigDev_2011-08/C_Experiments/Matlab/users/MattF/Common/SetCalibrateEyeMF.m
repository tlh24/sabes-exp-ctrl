%  SetCalibrateEyeMF.m
%
%  MF Oct. 18, 2007
%


H = CalibrateEye;


switch 3

  case 1
    %  New April, 2008.  Good for subworkspace 1 (left side)

    set(H.txtCenterX,'string','0');

    set(H.txtCenterY,'string','0');

    set(H.txtHalfWidth,'string','50');

    set(H.txtHalfHeight,'string','50');

    set(H.txtGridAxisXmin,'string','-65');

    set(H.txtGridAxisXmax,'string','65');

    set(H.txtGridAxisYmin,'string','-65');

    set(H.txtGridAxisYmax,'string','65');

  case 2
    set(H.txtCenterX,'string','30');

    set(H.txtCenterY,'string','-10');

    set(H.txtHalfWidth,'string','48');

    set(H.txtHalfHeight,'string','38');

    set(H.txtGridAxisXmin,'string','-35');

    set(H.txtGridAxisXmax,'string','85');

    set(H.txtGridAxisYmin,'string','-65');

    set(H.txtGridAxisYmax,'string','40');
  case 3
    set(H.txtCenterX,'string','42.5');

    set(H.txtCenterY,'string','-7.5');

    set(H.txtHalfWidth,'string','110');

    set(H.txtHalfHeight,'string','75');

    set(H.txtGridAxisXmin,'string','-90');

    set(H.txtGridAxisXmax,'string','170');

    set(H.txtGridAxisYmin,'string','-90');

    set(H.txtGridAxisYmax,'string','75');
end