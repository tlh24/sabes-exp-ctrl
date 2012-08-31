%  TonePiano.m
%
%  Fun with tones
%  

word0 = [0 0.1];

word1 = [1000 0.01; 0 0.01];
word2 = [1200 0.01; 0 0.01];
word3 = [1500 0.01; 0 0.01];
word4 = [600 0.01; 0 0.01];
word5 = [500 0.01; 0 0.01];
word6 = [1600 0.01; 0 0.01];
word7 = [400 0.01; 0 0.01];

word10 = [1600 0.009; 1400 0.009];

phrase1 = repmat(word1,10,1);
phrase2 = repmat(word2,10,1);
phrase3 = repmat(word3,20,1);
phrase4 = repmat(word4,7,1);
phrase5 = repmat(word5,7,1);

B1 = [380 0.20; 0 0.1; 380 0.20; 0 0.1; 380 0.20; 0 0.15; 300 0.9];
B2 = [338 0.2; 0 0.1; 338 0.2; 0 0.1; 338 0.2; 0 0.2; 285 0.9];
notes = [];

if 1
  notes = [415 0.35; 0 0.1; 415 0.35; 0 0.1; 439 0.35; 0 0.1; 493 0.35; 0 0.1; ...    
           493 0.35; 0 0.1; 439 0.35; 0 0.1; 415 0.35; 0 0.1; 370 0.35; 0 0.1; ...
           330 0.35; 0 0.1; 330 0.35; 0 0.1; 370 0.35; 0 0.1; 415 0.35; 0 0.1;...
           415 0.55; 0 0.1; 370 0.2; 0 0.01; 370 0.55; 0 0.5; ...
           415 0.35; 0 0.1; 415 0.35; 0 0.1; 439 0.35; 0 0.1; 493 0.35; 0 0.1; ...    
           493 0.35; 0 0.1; 439 0.35; 0 0.1; 415 0.35; 0 0.1; 370 0.35; 0 0.1; ...
           330 0.35; 0 0.1; 330 0.35; 0 0.1; 370 0.35; 0 0.1; 415 0.35; 0 0.1; 370 0.55; 0 0.1; ...
           330 0.2; 0 0.01; 330 0.55; 0 0.1;
            ];
  
end


if 0  
  notes = [B1; ...
            0 0.45; ...
           B2; ...
           0 0.45; ...
           [B1(:,1) B1(:,2).*0.5]; ...
           0 0.2; ...
           [B2(:,1) B2(:,2).*0.5]; ...
           0 0.1; ...
           [B1(:,1) B1(:,2).*0.5]; ...
          ];

  
end

if 0
  notes = [repmat(word10,11,1); 0 0.1; repmat(word1,10,1); 0 0.2; repmat(word7,23,1); ...
           600 0.35; 0 0.15; 605 0.3; ...
    
          ];
end


if 0
notes = [phrase1; phrase2; phrase3; ...
          phrase5; word0; phrase4; word0; phrase5; word0; ...
          phrase5; word0; repmat(word1,7,1); word0; phrase5; word0; ...
          phrase5; word0; phrase4; word0; phrase5; ...
];
end

if 0
notes = [notes;
         1000 0.6; ...
         400  0.1; ...
         1000 0.5; ...
         400 0.2; ...
         1000 0.4; ...
         400 0.3; ...
         1000 0.3; ...
         400 0.4; ...
         1000 0.2; ...
         400 0.5; ...
         1000 0.1; ...
         400 0.6; ...
         0 0.3; ...
         200 1; ...
         1200 0.5; ...
         0 0.2; ...
         500 0.6; ...
         750 1; ...
         200 0.4; ...
         0 0.2; ...
         200 0.4; ...
         0 0.2; ...
         200 0.4; ...
         1200 0.2
        ];
end

for i = 1:size(notes,1)
  ToneStart(notes(i,1),notes(i,2));
  pause(notes(i,2));  
end