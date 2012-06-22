ServerNamesInclude;

hVMain = actxserver('CP_Display.VMain', strDisplayComputer); 

TMtxIn = hVMain.GetTransformMatrix

%if iscom(hVMain)  release(hVMain); end;
TMtxOut = [ 588.039673 202.422653
            2.255886  0.058983
            -0.011221  -2.003372
            0.000001  -0.000074
            -0.001019  -0.000086
            -0.000046  0.001072 ];
          
hVMain.SetTransformMatrix(TMtxOut);
TMtxIn = hVMain.GetTransformMatrix
TMtx1 = [  0     0
           1     0
           0     1
           0     0
           0     0
           0     0 ];

hVMain.SetTransformMatrix(TMtx1);

