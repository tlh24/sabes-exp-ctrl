        ��  ��                  `      �� ��     0 	        `4   V S _ V E R S I O N _ I N F O     ���               ?                        �   S t r i n g F i l e I n f o   �   0 4 0 9 0 4 b 0       C o m m e n t s        C o m p a n y N a m e     L   F i l e D e s c r i p t i o n     C P _ D i s p l a y   M o d u l e   6   F i l e V e r s i o n     1 ,   0 ,   0 ,   1     6   I n t e r n a l N a m e   C P _ D i s p l a y     B   L e g a l C o p y r i g h t   C o p y r i g h t   2 0 0 7     (    L e g a l T r a d e m a r k s     (    O L E S e l f R e g i s t e r     F   O r i g i n a l F i l e n a m e   C P _ D i s p l a y . E X E          P r i v a t e B u i l d   6   P r o d u c t N a m e     C P _ D i s p l a y     :   P r o d u c t V e r s i o n   1 ,   0 ,   0 ,   1          S p e c i a l B u i l d   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	��   0   R E G I S T R Y   ��d       0 	        HKCR
{
	NoRemove AppID
	{
		{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8} = s 'CP_Display'
		'CP_Display.EXE'
		{
			val AppID = s {EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}
		}
	}
}
 �  0   R E G I S T R Y   ��f       0	        HKCR
{
	CP_Display.VMain.1 = s 'VMain Class'
	{
		CLSID = s '{EBD33088-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	CP_Display.VMain = s 'VMain Class'
	{
		CLSID = s '{EBD33088-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	NoRemove CLSID
	{
		ForceRemove {EBD33088-CEB1-11D5-9C3E-0050DA2A68C8} = s 'VMain Class'
		{
			ProgID = s 'CP_Display.VMain.1'
			VersionIndependentProgID = s 'CP_Display.VMain'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			LocalServer32 = s '%Module%'
		}
	}
}
 �  0   R E G I S T R Y   ��h       0	        HKCR
{
	CP_Display.VDisk.1 = s 'VDisk Class'
	{
		CLSID = s '{EBD33090-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	CP_Display.VDisk = s 'VDisk Class'
	{
		CLSID = s '{EBD33090-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	NoRemove CLSID
	{
		ForceRemove {EBD33090-CEB1-11D5-9C3E-0050DA2A68C8} = s 'VDisk Class'
		{
			ProgID = s 'CP_Display.VDisk.1'
			VersionIndependentProgID = s 'CP_Display.VDisk'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			LocalServer32 = s '%Module%'
		}
	}
}
 �  0   R E G I S T R Y   ��l       0	        HKCR
{
	CP_Display.VMouse.1 = s 'VMouse Class'
	{
		CLSID = s '{EBD330A8-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	CP_Display.VMouse = s 'VMouse Class'
	{
		CLSID = s '{EBD330A8-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	NoRemove CLSID
	{
		ForceRemove {EBD330A8-CEB1-11D5-9C3E-0050DA2A68C8} = s 'VMouse Class'
		{
			ProgID = s 'CP_Display.VMouse.1'
			VersionIndependentProgID = s 'CP_Display.VMouse'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			LocalServer32 = s '%Module%'
		}
	}
}
  M  0   R E G I S T R Y   ��m       0	        HKCR
{
	CP_Display.VPolygon.1 = s 'VPolygon Class'
	{
		CLSID = s '{EBD33098-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	CP_Display.VPolygon = s 'VPolygon Class'
	{
		CLSID = s '{EBD33098-CEB1-11D5-9C3E-0050DA2A68C8}'
		CurVer = s 'CP_Display.VPolygon.1'
	}
	NoRemove CLSID
	{
		ForceRemove {EBD33098-CEB1-11D5-9C3E-0050DA2A68C8} = s 'VPolygon Class'
		{
			ProgID = s 'CP_Display.VPolygon.1'
			VersionIndependentProgID = s 'CP_Display.VPolygon'
			ForceRemove 'Programmable'
			LocalServer32 = s '%MODULE%'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
		}
	}
}
   �  0   R E G I S T R Y   ��o       0	        HKCR
{
	CP_Display.VText.1 = s 'VText Class'
	{
		CLSID = s '{EBD330A0-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	CP_Display.VText = s 'VText Class'
	{
		CLSID = s '{EBD330A0-CEB1-11D5-9C3E-0050DA2A68C8}'
	}
	NoRemove CLSID
	{
		ForceRemove {EBD330A0-CEB1-11D5-9C3E-0050DA2A68C8} = s 'VText Class'
		{
			ProgID = s 'CP_Display.VText.1'
			VersionIndependentProgID = s 'CP_Display.VText'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			LocalServer32 = s '%Module%'
		}
	}
}
 �  0   R E G I S T R Y   ��p       0	        HKCR
{
	CP_Display.VComplexShape.1 = s 'VComplexShape Class'
	{
		CLSID = s '{015EA1C0-B904-4D55-B4F7-C195665FEF69}'
	}
	CP_Display.VComplexShape = s 'VComplexShape Class'
	{
		CLSID = s '{015EA1C0-B904-4D55-B4F7-C195665FEF69}'
		CurVer = s 'CP_Display.VComplexShape.1'
	}
	NoRemove CLSID
	{
		ForceRemove {015EA1C0-B904-4D55-B4F7-C195665FEF69} = s 'VComplexShape Class'
		{
			ProgID = s 'CP_Display.VComplexShape.1'
			VersionIndependentProgID = s 'CP_Display.VComplexShape'
			ForceRemove 'Programmable'
			LocalServer32 = s '%MODULE%'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			'TypeLib' = s '{ebd33084-ceb1-11d5-9c3e-0050da2a68c8}'
		}
	}
}
�  0   R E G I S T R Y   ��q       0	        HKCR
{
	CP_Display.VMotion.1 = s 'VMotion Class'
	{
		CLSID = s '{82B82EDC-EB68-4C2B-BD86-4245641B918A}'
	}
	CP_Display.VMotion = s 'VMotion Class'
	{
		CLSID = s '{82B82EDC-EB68-4C2B-BD86-4245641B918A}'
		CurVer = s 'CP_Display.VMotion.1'
	}
	NoRemove CLSID
	{
		ForceRemove {82B82EDC-EB68-4C2B-BD86-4245641B918A} = s 'VMotion Class'
		{
			ProgID = s 'CP_Display.VMotion.1'
			VersionIndependentProgID = s 'CP_Display.VMotion'
			ForceRemove 'Programmable'
			LocalServer32 = s '%MODULE%'
			val AppID = s '{EBD33080-CEB1-11D5-9C3E-0050DA2A68C8}'
			'TypeLib' = s '{ebd33084-ceb1-11d5-9c3e-0050da2a68c8}'
		}
	}
}
|X  ,   T Y P E L I B   ��     0 	        MSFT      	      A                         �   p      ����       �             d   �   ,  �  �  X  �     �  �  L  �    |  x  ����   �	     ����   �	     ����   <	  p   ����   �  �   ����   t  �  ����   �	     ����   �  8  ����     l	  ����   x$      ����   ����    ����   �$     ����   �$     ����   ����    ����   ����    ����   %"  �$                                     H                         ����                  ����4" �$                                    �   @  0       0           ���� `             ����%"  )                                     �            �          ����                 ����4"  )                                    �   @  0      �          ���� �             ����%" 00                                     �      ,      �          ����                  ����4" 00                                    �   @  @      �          ���� �             ����%" 8                                          �      �          ����      0           ����4" 8                 "                      @  	      �          ���� �             ����%" �@                                     8            8          ����      @           ����4"	 �@                 
                   P  @        H          ���� D             ����%"
 �B                                     h     �      �          ����      P           ����4" �B                 .                   �  @  �      �          ���� �             ����%" �N                                     �     �      �          ����      `           ����4" �N                 &                   �  @        �          ���� �             ���������   �  �����  �   �������������   �������������  ������������8  `   h  ����P  ��������0     ������������   ����   �0�����> P�*h���������c�w�|Q���  �w<���������d�w�|Q���  �w<����������0�����> P�*h�    ����0     �      F   ����      �      F   �����0�����> P�*h�d   �����0�����> P�*h��   �����0�����> P�*h�,  �����0�����> P�*hȐ  �����0�����> P�*h��  �����0�����> P�*h�X  �����0�����> P�*hȼ      �0�����> P�*h�   H   �0�����> P�*hȄ  �   ��^�UM����f_�i�  ����xHD,EJ�����L  x   �.��h�+L��BEd���  �   �_�f�dvF�gbkb��  ����d      ��������,     ���������     ���������     ���������     ��������L     ��������     ��������      x   `          - stdole2.tlbWWW����P  \   �  0  �����  �  �  �����  �  �����	  ����	  ����X    ���������  $  @	  ����l  �     H    �
  �����  �  �  �    <  �    �����  �����  ����    �  P     �����  �  �  �	       \  �	  �  �����  L
    �  l
  ��������8    �  (  �   �  �  `  �   ���������  �����  ����4  �����  �  p  ,  |  �����  ��������<  ������������p  ����8  �����  �  �  x  �����  T  �  ����L  �	  �   h  �  �������������  ,
  ����  ����h	  ��������8  �������� ��CP_DISPLAYLibWWW    ����8�SVMainWWWd   ����8YIIVMainWWd   ����
 +�GetVersionWW�������� �pbstVersionWd   ����	 �DStartSyncWWWd   ���� �2StopSyncd   ���� �gGetFrameCountWWW�������� HpnFramesd   ���� ��GetTransformMatrixWW�������� l�pvMatrixd   ���� SetTransformMatrixWW�������� ��vMatrixWd   ���� ��GetTimeScale�������� ��pdC0�������� ��pdC1d   ���� ��SetTimeScale�������� ɂdC0W�������� ʂdC1Wd   ���� ��StartBatchDrawWWd   ���� k7FinishBatchDrawW�������� �AiLogIDWWd   ����	 h�MoveGroupWWW�������� �(iGroupID�������� 9�vXYWd   ����
 �lScaleGroupWW�������� �idScaleWWd   ���� #�RotateGroupW�������� �dAngleWWd      	 �HideGroupWWWd   ����	 K�ShowGroupWWWd   ���� A�ResetEventLogWWWd   \   #:GetEventLogW�������� �:pvLogIDW�����   �pvTimeStampMsWWW�   ����8��VDiskWWW,  ����8��IVDiskWW,     GetXYWWW��������  �pvXY,  �   9�SetXYWWW,  ���� ��GetZ�������� D�pdZW,  �   ��SetZ����    ]dZWW,  0   ��GetScale����h   �KpdScaleW,  ���� ��SetScale,  ���� �RGetAngle�������� �pdAngleW,      �;SetAngle,  p   mWGetColor����|   �pvColors,  �   K@SetColor�������� F�vColorsW,  ���� �GetAlpha�������� �KpdAlphaW,  ���� ��SetAlpha�������� jdAlphaWW,  �   �GetFillFlagW����H  
 �
piFillFlagWW,  ���� $�SetFillFlagW��������	 �OiFillFlagWWW,  ���� �gGetShowFlagW����t   
 >�piShowFlagWW,  �   �;SetShowFlagW����0   	 ��iShowFlagWWW,  4  
 ?GetGroupIDWW��������	 ��piGroupIDWWW,  �  
 ��SetGroupIDWW,  ���� �GetClippedCountW�������� �piClippedCountWW,  L   >yMove,  $   ��ScaleWWW,  ���� �RotateWW,  ���� �Show,  �   9zHide,     	 ��GetRadiusWWW�����   �'pdRadius,  ����	 
FSetRadiusWWW�������� 3KdRadiusW,  L   �=GetN_VerticesWWW��������
 ��pnVerticesWW,  ���� �SetN_VerticesWWW�����  	 ��nVerticesWWW�  ����8�.VPolygon�  ����	8��IVPolygonWWW�  ���� o�GetVerticesW��������
 �tpvVerticesWW�  ���� )�SetVerticesW��������	 �vVerticesWWW�  \  
 K�GetTextureWW�����  	 �2pvTextureWWW��������	 ��pnPixelsWWWW����p   FRpnPixelH�������� '�pdTexturePhysWidthWW�  ����
 ShSetTextureWW�����   �vTexture�������� �dTexturePhysWidthWWW�  �   ��GetTextureFlagWW�������� 6�plngTextureFlagW�  �   /|SetTextureFlagWW�����   ;flngTextureFlagWWX  �  8��VTextWWW�    8��IVTextWW�  �   �GetTextW����t   ��pbstText�  D   ��SetTextW����`   ��bstTextW�  ���� ��GetFontNameW����d   ��pVal�  �   ��SetFontNameW�����   plnewValWW�  ���� �0GetFontWeightWWW����`  	 rlngWeightWWW�  ���� E�SetFontWeightWWW�     'GetFontUnderlineFlag�������� ��plngUnderlineFlagWWW�  	   >SetFontUnderlineFlag�����   A�lngUnderlineFlag�      F�GetFontItalicFlagWWW����     �MplngItalicFlagWW�  ���� �SetFontItalicFlagWWW�������� ��lngItalicFlagWWW   ����8�FVMouseWW�  @  8rIVMouseW�����   �pvMtxWWW�  �   ��GetAllEvents�  �    lGetDownEventsWWW�     b�GetUpEventsW�  �
   ƎGetDblclickEventsWWW�  �   ��ClearEventsW�  ����8=�VComplexShapeWWWL  ����84IVComplexShapeWWL  �   /%GetDrawModeWL  
   ��SetDrawModeWL  �    �1GetExactL  ���� �SetExactL  ����	 �GetColorsWWWL  �  	 r9SetColorsWWWL  X   �pGetPointSizeL  �   �%SetPointSizeL  �   �GetLineWidthL  X   �rSetLineWidthL  ���� �GetLineStippleWWL  ���� [TSetLineStippleWWL  ���� -�GetLineStippleFactorL  �	   D�SetLineStippleFactorL  ���� �GetPolygonStippleWWWL  ���� �gSetPolygonStippleWWWL  ����
 ϔGetIndicesWWL  �
  
 V8SetIndicesWWL  4   �GetEdgeFlagsL  ���� 5�SetEdgeFlags�  ,	  8�VMotionW  �	  8ErIVMotion  �
   ��IsCircle  ����	 88UseCircleWWW  �   �IsSquare  (  	 �yUseSquareWWW  ����
 "{GetNPointsWW  �  
 �SetNPointsWW  L   �GetLifetimeW  ���� ��SetLifetimeW  x   "LGetCoherence  D    +SetCoherence  4   �GetVelocityW  T	   ��SetVelocityW CP_Display 0.0 Type LibraryWWW VMain ClassWWW IVMain InterfaceWW2 Starts counting frames and outputting frame pulses1 Stops counting frames and outputting frame pulsesW Returns current frame count.WWM Defines 2nd-order transform from physical to screen coordinates (calibration)W Time scale coefficientsWWWF After this call everything is drawn off-screen until FinishBatchDraw()- Shows all updates made after StartBatchDraw()W Moves all graphics objects Scales all graphics objectsWWW Rotates all graphics objectsWW Hides all graphics objects Shows all graphics objects All log events are cleared9 LogIDs and timestamps since the last ResetEventLog() callW VDisk ClassWWW IVDisk InterfaceWW Origin position X,YWWW Origin position Z (depth)W Scaling factor Rotation angle, degreesWWW Color (R,G,B)W Alpha (transparency) 1= solidW$ Filled (=1) or just the contour (=0)WW Show (=1) or Hide (=0) GroupID is 0 by defaultWWW. Number of clipped vertices, calculated on draw Moves graphics objectW Scales graphic objectW Rotates graphics objectWWW Shows graphics objectW Hides graphics objectW Disk radiusWWW. N of poins on the circle to represent the disc VPolygon Class IVPolygon InterfaceWWW4 Vertices of the polygon relative to its origin (X,Y)WW> Texture image, 4 doubles per pixel, W x H x RGBA, 1D array!!!!: Texture image, 4 doubles per pixel, W x H x RGBA, 3D array  1 = apply texture, 0 = use colorWW VText ClassWWW IVText InterfaceWW Text stringWWW Text font name Font weight - 100:100:900W" Font underline. 0 = not underlined Font italic 0 = not italic VMouse ClassWW IVMouse InterfaceW$ Mouse cursor: Show (=1) or Hide (=0)WW Mouse position in pixelsWW7 Button up/down/dblclick (3 events x 3 buttons) 1 = TRUEWWW  Button down (3 buttons) 1 = TRUEWW Button up (3 buttons) 1 = TRUE$ Button dblclick (3 buttons) 1 = TRUEWW Clear all events to 0W Shows mouse cursor Hides mouse cursor VComplexShape ClassWWW IVComplexShape InterfaceWW property drawModeW property exact property verticesW property colorsWWW property pointSize property lineWidth property lineStippleWW property lineStippleFactor property polygonStippleWWW property indicesWW property edgeFlags VMotion ClassW IVMotion Interface property IsCircleW property UseCircle property IsSquareW property UseSquare property NPointsWW property lifetimeW property coherence property velocityW @ � @ � @ � @ � ��\NWW � WW       ����0          p  $    �     L 	         \          �      4 	         D       �    $ 4 	         x   ,   �    ( L 	        �      �      ,   �    , L 	        �      �      ,   �    0 D 	        �    �$     8   �    4 d 	             P        `     8   �    8 T 	           ��      ��         �    < 4 	         8  0 	  �    @ \ 		        �     � ��  1   P 
  �    D | 	
        �  ��������   � �      �       ��  1   P   �    H | 	        �  ��������   � �      �H      ��  1   P   �    L | 	        �  ��������   � �      �t      ��  1   @   �    P l 	          ����   � �      ��  1   @   �    T l 	        (  ����   � �      ��  1       �    X 4 	         D  8   �    \ d 	        `     �                ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` `D   t   �   �   �     8  p  �  �  �  0  \  �  �  �  �      $   D   d   �   �   �      X  x  �  �  H  �  �    8  �  ,    �     L 	         �     X     @   �      l 	        �  ����   � �       ��  1   ,   �    $ L 	        �     �     @   �    ( l 	        �  ����   � ��      ��  1   ,   �    , L 	        �     �     @   �    0 l 	        �  ����   � �H      ��  1   ,   �    4 L 	                  @   �    8 l 	          ����   � �t      ��  1   ,   �    < L 	              H     @ 	  �    @ l 		           ����   � �p      ��  1   , 
  �    D L 	
        0     �     @   �    H l 	        0  ����   � ��      ��  1   ,   �    L L 	        P     �     @   �    P l 	        P  ����   � �      ��  1   ,   �    T L 	        x     L     @   �    X l 	        x  ����   � �|      ��  1   ,   �    \ L 	        �     �     ,   �    ` D 	        �   �     ,   �    d L 	        �     �     @   �    h l 	        �  ����   � �       ��  1   @   �    l l 	        �  ����   � �H      ��  1   @   �    p l 	          ����   � �t      ��  1   0   �    t \ 	        (     � ��  1   0   �    x \ 	        @     � ��  1   ,   �    | L 	        X     �     @   �    � l 	        X  ����   � ��      ��  1   ,   �    � L 	        h     �     @   �    � l 	        h  ����   � �      ��  1     ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` `D  h  |  �  �  �  �     4  \  �  �  �    4  d  �  �  �    $  8  L  \  l  �  �  �      ,   l   �   �     D  p  �  �    H  �  �  �     `  �  �  �  $  d  �  �    0  p  �  |  ,    �     L 	         �     X     @   �      l 	        �  ����   � �       ��  1   ,   �    $ L 	        �     �     @   �    ( l 	        �  ����   � ��      ��  1   ,   �    , L 	        �     �     @   �    0 l 	        �  ����   � �H      ��  1   ,   �    4 L 	                  @   �    8 l 	          ����   � �t      ��  1   ,   �    < L 	              H     @ 	  �    @ l 		           ����   � �p      ��  1   , 
  �    D L 	
        0     �     @   �    H l 	        0  ����   � ��      ��  1   ,   �    L L 	        P     �     @   �    P l 	        P  ����   � �      ��  1   ,   �    T L 	        x     L     @   �    X l 	        x  ����   � �|      ��  1   ,   �    \ L 	        �     �     ,   �    ` D 	        �   �     ,   �    d L 	        �     �     @   �    h l 	        �  ����   � �       ��  1   @   �    l l 	        �  ����   � �H      ��  1   @   �    p l 	          ����   � �t      ��  1   0   �    t \ 	        (     � ��  1   0   �    x \ 	        @     � ��  1   ,   �    | L 	        �     p     @   �    � l 	        �  ����   � ��      ��  1   P   �    � � 	        �     �        �                      P   �    � | 	        8  ��������   � �L      �`      ��  1   ,   �    � L 	        t     �     @   �    � l 	        t  ����   � ��      ��  1     ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` `D  h  |  �  �  �  �     4  \  �  �  �    4  d  �  �  �    $  8  L  \  X  �  �  4  �  �      ,   l   �   �     D  p  �  �    H  �  �  �     `  �  �  �  $  d  �  �    0  p  �    <     ,    �     L 	         �     X     @   �      l 	        �  ����   � �       ��  1   ,   �    $ L 	        �     �     @   �    ( l 	        �  ����   � ��      ��  1   ,   �    , L 	        �     �     @   �    0 l 	        �  ����   � �H      ��  1   ,   �    4 L 	                  @   �    8 l 	          ����   � �t      ��  1   ,   �    < L 	              H     @ 	  �    @ l 		           ����   � �p      ��  1   , 
  �    D L 	
        0     �     @   �    H l 	        0  ����   � ��      ��  1   ,   �    L L 	        P     �     @   �    P l 	        P  ����   � �      ��  1   ,   �    T L 	        x     L     @   �    X l 	        x  ����   � �|      ��  1   ,   �    \ L 	        �     �     ,   �    ` D 	        �   �     ,   �    d L 	        �     �     @   �    h l 	        �  ����   � �       ��  1   @   �    l l 	        �  ����   � �H      ��  1   @   �    p l 	          ����   � �t      ��  1   0   �    t \ 	        (     � ��  1   0   �    x \ 	        @     � ��  1   ,   �    | L 	        �      ,	     @   �    � l 	        �  ����   � �T	      ��  1   ,   �    � L 	        �      �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     ,
     @   �    � l 	        �  ����   � �l
      ��  1   ,    �    � L 	              �
     @ !  �    � l 	!          ����   � ��
      ��  1     ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` `  `! `D  h  |  �  �  �  �     4  \  �  �  �    4  d  �  �  �    $  8  L  \  	  @	  h	  �	  �	  �	  
  L
  �
  �
      ,   l   �   �     D  p  �  �    H  �  �  �     `  �  �  �  $  d  �  �    0  p  �  �    H  t  �  �  �  ,    �     L 	         \     L     ,   �      D 	        \   �|     ,   �    $ L 	        �     (     ,   �    ( L 	        �     (     ,   �    , L 	        �     (     ,   �    0 L 	              (     ,   �    4 L 	              (         �    8 4 	         H      �    < 4 	         `    	  �    @ 4 		         t    ` ` ` ` ` ` ` ` `	 `4  d  D  <  T  p  �  �  L  \      ,   X   �   �   �     4  T  t  �	  ,    �     L 	         �     X     @   �      l 	        �  ����   � �       ��  1   ,   �    $ L 	        �     �     @   �    ( l 	        �  ����   � ��      ��  1   ,   �    , L 	        �     �     @   �    0 l 	        �  ����   � �H      ��  1   ,   �    4 L 	                  @   �    8 l 	          ����   � �t      ��  1   ,   �    < L 	              H     @ 	  �    @ l 		           ����   � �p      ��  1   , 
  �    D L 	
        0     �     @   �    H l 	        0  ����   � ��      ��  1   ,   �    L L 	        P     �     @   �    P l 	        P  ����   � �      ��  1   ,   �    T L 	        x     L     @   �    X l 	        x  ����   � �|      ��  1   ,   �    \ L 	        �     �     ,   �    ` D 	        �   �     ,   �    d L 	        �     �     @   �    h l 	        �  ����   � �       ��  1   @   �    l l 	        �  ����   � �H      ��  1   @   �    p l 	          ����   � �t      ��  1   0   �    t \ 	        (     � ��  1   0   �    x \ 	        @     � ��  1   ,   �    | L 	        �      �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,    �    � L 	              �	     @ !  �    � l 	!          ����   � ��	      ��  1   , "  �    � L 	"             �	     @ #  �    � l 	#          ����   � ��	      ��  1   , $  �    � L 	$        0     �	     @ %  �    � l 	%        0  ����   � ��	      ��  1   , &  �    � L 	&        H     �	     @ '  �    � l 	'        H  ����   � ��	      ��  1   , (  �    � L 	(        d     �	     @ )  �    � l 	)        d  ����   � ��	      ��  1   , *  �    � L 	*        �     �	     @ +  �    � l 	+        �  ����   � ��	      ��  1   , ,  �    � L 	,        �     �	     @ -  �    � l 	-        �  ����   � ��	      ��  1     ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` `  `! `" `# `$ `% `& `' `( `) `* `+ `, `- `D  h  |  �  �  �  �     4  \  �  �  �    4  d  �  �  �    $  8  L  \  �    (  <  X  �  P  h  �  �  �  �  �  �    8  X  x  �  �  �  �      ,   l   �   �     D  p  �  �    H  �  �  �     `  �  �  �  $  d  �  �    0  p  �  �    H  t  �  �     L  �  �  �  $  d  �  �  �  <	  h	  �  ,    �     L 	         �     X     @   �      l 	        �  ����   � �       ��  1   ,   �    $ L 	        �     �     @   �    ( l 	        �  ����   � ��      ��  1   ,   �    , L 	        �     �     @   �    0 l 	        �  ����   � �H      ��  1   ,   �    4 L 	                  @   �    8 l 	          ����   � �t      ��  1   ,   �    < L 	              H     @ 	  �    @ l 		           ����   � �p      ��  1   , 
  �    D L 	
        0     �     @   �    H l 	        0  ����   � ��      ��  1   ,   �    L L 	        P     �     @   �    P l 	        P  ����   � �      ��  1   ,   �    T L 	        x     L     @   �    X l 	        x  ����   � �|      ��  1   ,   �    \ L 	        �     �     ,   �    ` D 	        �   �     ,   �    d L 	        �     �     @   �    h l 	        �  ����   � �       ��  1   @   �    l l 	        �  ����   � �H      ��  1   @   �    p l 	          ����   � �t      ��  1   0   �    t \ 	        (     � ��  1   0   �    x \ 	        @     � ��  1   ,   �    | L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        �  ����   � ��	      ��  1   ,   �    � L 	        �     �	     @   �    � l 	        	  ����   � ��	      ��  1   ,   �    � L 	        	     �	     @   �    � l 	        	  ����   � ��	      ��  1   ,    �    � L 	         0	     �	     @ !  �    � l 	!        0	  ����   � ��	      ��  1   , "  �    � L 	"        D	     �	     @ #  �    � l 	#        D	  ����   � ��	      ��  1   , $  �    � L 	$        X	     �	     @ %  �    � l 	%        X	  ����   � ��	      ��  1     ` ` ` ` ` ` ` ` `	 `
 ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` `  `! `" `# `$ `% `D  h  |  �  �  �  �     4  \  �  �  �    4  d  �  �  �    $  8  L  \  (  <     4  L  `  x  �  �  �  �  �           ,   l   �   �     D  p  �  �    H  �  �  �     `  �  �  �  $  d  �  �    0  p  �  �    H  t  �  �     L  �  �  4       �� ��     0	                
 C P _ D i s p l a y                       