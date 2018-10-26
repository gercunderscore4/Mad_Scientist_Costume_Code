% draw logic circuit for Halloween costume
clear
clc

% x = absolute position x
% y =  y
% dx = displacement x
% dy = displacement y
% sx = spacing of x
% sy = spacing of y
% l = lenth
% b = breadth

% w = of wire
% i = of integrated circuit
% p = of pin
% r = of resistor
% c = of capacitor

%dxw = 0; % don't bother using
%dyw = 0; % don't bother using
sxw = 1;
syw = 1;

dxp = 0.4;
dyp = 0.6;
dxi = 3;
dyi = 1 - dyp;
sxp = dxi + dxp;
syp = syw;

lr = 4*sxw;
br = 0.5*sxw;
er = 0.5;
sr = 6;
lrl = [0 er er+([1:sr]-0.5)*((lr-2*er)/sr) lr-er lr NaN];
brb = [0 0 (-1).^[0:(sr-1)] 0 0 NaN]*br;

lc = 3*sxw;
bc = 0.75*sxw;
lcl = [0 0.4 0.4 0.4 NaN 0.6 0.6 0.6 1]*lc;
bcb = [0 0 1 -1 NaN 1 -1 0 0]*bc;

% pc = pin count (one side)
% ll = lower left of current integrated circuit
% t = temp

% initialize lines
xw = [];
yw = [];
xi = [];
yi = [];
xp = [];
yp = [];
xr = [];
yr = [];
xc = [];
yc = [];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% VCC
xt = dxi + dxp + 4*sxw;
x1 = 0 - 5*dxp - 16*sxw - 2*dxi - lr;
yt = dyi/2 + 3*syp + dyp/2 + 3*syw;
xw = [xw xt x1 NaN];
yw = [yw yt yt NaN];


% GND
xt = dxi + dxp + sxw   +3*sxw;
x1 = 0 - 7*dxp - 24*sxw - 3*dxi - lr;
yt = dyi/2 + 0*syp + dyp/2 - syp*4 - syw*3;
xw = [xw xt x1 NaN];
yw = [yw yt yt NaN];



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 555 timer
pc = 4;
xll = 0;
yll = 0;

% draw IC
xi = [xi xll xll xll+dxi xll+dxi xll NaN];
yi = [yi yll yll+(pc-1)*syp+dyp+dyi yll+(pc-1)*syp+dyp+dyi yll yll NaN];
for ii = 1:pc
  yt = yll + dyi/2 + (ii-1)*syp;

  xt = xll - dxp;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];

  xt = xll + dxi;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];
end

% draw wires

% 4, 1
xt = xll - dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw xt NaN];
yw = [yw yt yt yt+3*syp yt+3*syp NaN];

% 2
xt = xll - dxp;
yt = yll + dyi/2 + 2*syp + dyp/2;
xw = [xw xt xt-2*sxw xt-2*sxw xt+2*dxp+dxi+2*sxw NaN];
yw = [yw yt yt yt+syp-2*lr yt+syp-2*lr NaN];

% 3
xt = xll - dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt-3*sxw NaN];
yw = [yw yt yt NaN];

% 5
yt = yll + dyi/2 + 0*syp + dyp/2;
xt = xll + dxi + dxp;
xw = [xw xt xt+sxw NaN xt+sxw xt+sxw NaN];
yw = [yw yt yt NaN yt-lc yt-syp*4-syw*3 NaN];
% c
xc = [xc xt+sxw-bcb];
yc = [yc yt-lcl];

% 6
yt = yll + dyi/2 + 1*syp + dyp/2;
xt = xll + dxi + dxp;
xw = [xw xt xt+2*sxw xt+2*sxw xt+4*sxw NaN];
yw = [yw yt yt yt+2*syp-2*lr yt+2*syp-2*lr NaN];

% 7
yt = yll + dyi/2 + 2*syp + dyp/2;
xt = xll + dxi + dxp;
xw = [xw xt xt+3*sxw xt+3*sxw xt+4*sxw NaN];
yw = [yw yt yt yt+syp-lr yt+syp-lr NaN];
% r
xr = [xr xt+4*sxw+brb];
yr = [yr yt-lr+syp-lrl];

% 8
yt = yll + dyi/2 + 3*syp + dyp/2;
xt = xll + dxi + dxp;
xw = [xw xt xt+4*sxw xt+4*sxw NaN];
yw = [yw yt yt yt+3*syw NaN];
% r
xr = [xr xt+4*sxw+brb];
yr = [yr yt-lrl];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% counter
pc = 8;
xll = xll - dxp - 7*sxw - dxi - dxp;
yll = yll - 4*syp;

% draw IC
xi = [xi xll xll xll+dxi xll+dxi xll NaN];
yi = [yi yll yll+(pc-1)*syp+dyp+dyi yll+(pc-1)*syp+dyp+dyi yll yll NaN];
for ii = 1:pc
  yt = yll + dyi/2 + (ii-1)*syp;

  xt = xll - dxp;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];

  xt = xll + dxi;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];
end

% 1
xt = xll - dxp;
yt = yll + dyi/2 + 7*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw xt-sxw-lr NaN];
yw = [yw yt yt yt+syw yt+syw NaN];

% 2
xt = xll - dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt-sxw-lr xt-sxw-lr NaN];
yw = [yw yt yt yt-5*syp-syw NaN];

% 3,4,5,6,7
for ii = 5:-1:1
    xt = xll - dxp;
    yt = yll + dyi/2 + ii*syp + dyp/2;
    xw = [xw xt-lr xt-lr NaN];
    yw = [yw yt yt-syp NaN];
    % r
    xr = [xr xt-lrl];
    yr = [yr yt+brb];
end
% add connector to bottom

% 8
xt = xll - dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw NaN];
yw = [yw yt yt yt-syw*3 NaN];

% 9
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt+3*sxw xt+3*sxw NaN];
yw = [yw yt yt yt+syp NaN];

% 10
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt+3*sxw xt+3*sxw NaN];
yw = [yw yt yt yt+6*syp NaN];

% 11, 13
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 2*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw xt NaN];
yw = [yw yt yt yt+2*syp yt+2*syp NaN];

% 12
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 3*syp + dyp/2;
xw = [xw xt xt+2*sxw xt+2*sxw NaN];
yw = [yw yt yt yt-3*syp-3*syw NaN];

% 14
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 5*syp + dyp/2;
xw = [xw xt xt+2*sxw xt+2*sxw NaN];
yw = [yw yt yt yt-2*syp NaN];

% 15
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt+4*sxw xt+4*sxw NaN];
yw = [yw yt yt yt-syp NaN];

% 16
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 7*syp + dyp/2;
xw = [xw xt xt+3*sxw xt+3*sxw NaN];
yw = [yw yt yt yt+3*syw NaN];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% not gate
pc = 7;
xll = xll - dxp - 4*sxw - lr - dxi - dxp;
yll = yll + syp;

% draw IC
xi = [xi xll xll xll+dxi xll+dxi xll NaN];
yi = [yi yll yll+(pc-1)*syp+dyp+dyi yll+(pc-1)*syp+dyp+dyi yll yll NaN];
for ii = 1:pc
  yt = yll + dyi/2 + (ii-1)*syp;

  xt = xll - dxp;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];

  xt = xll + dxi;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];
end

% 1
xt = xll - dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw xt+dxp+dxi+dxp+3*sxw NaN];
yw = [yw yt yt yt+syw yt+syw NaN];
xw = [xw xt-sxw xt-3*sxw NaN];
yw = [yw yt+syw yt+syw NaN];

% 2
xt = xll - dxp;
yt = yll + dyi/2 + 5*syp + dyp/2;
xw = [xw xt xt-3*sxw NaN];
yw = [yw yt yt NaN];

% 3, 4
xt = xll - dxp;
yt = yll + dyi/2 + 4*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw xt NaN];
yw = [yw yt yt yt-syp yt-syp NaN];

% 5
xt = xll - dxp;
yt = yll + dyi/2 + 2*syp + dyp/2;
xw = [xw xt xt-2*sxw xt-2*sxw xt+dxp+dxi+dxp+3*sxw NaN];
yw = [yw yt yt yt-2*syp-syw yt-2*syp-syw NaN];
xw = [xw xt-2*sxw xt-2*sxw xt-3*sxw NaN];
yw = [yw yt yt+2*syp yt+2*syp NaN];

% 6
xt = xll - dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt-3*sxw NaN];
yw = [yw yt yt NaN];

% 7
xt = xll - dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw NaN];
yw = [yw yt yt yt-syp-syw*3 NaN];

% 8, 13
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt+2*sxw xt+2*sxw xt NaN];
yw = [yw yt yt yt+5*syp yt+5*syp NaN];

% 9, 10
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw xt NaN];
yw = [yw yt yt yt+syp yt+syp NaN];

% 11, 12
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 3*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw xt NaN];
yw = [yw yt yt yt+syp yt+syp NaN];

% 14
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw NaN];
yw = [yw yt yt yt+3*syw NaN];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% and gate
pc = 7;
xll = xll - dxp - 6*sxw - dxi - dxp;
yll = yll;

% draw IC
xi = [xi xll xll xll+dxi xll+dxi xll NaN];
yi = [yi yll yll+(pc-1)*syp+dyp+dyi yll+(pc-1)*syp+dyp+dyi yll yll NaN];
for ii = 1:pc
  yt = yll + dyi/2 + (ii-1)*syp;

  xt = xll - dxp;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];

  xt = xll + dxi;
  xp = [xp xt xt xt+dxp xt+dxp xt NaN];
  yp = [yp yt yt+dyp yt+dyp yt yt NaN];
end

% 1
xt = xll - dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw xt+dxp+dxi+dxp+3*sxw NaN];
yw = [yw yt yt yt+syw yt+syw NaN];

% 2
xt = xll - dxp;
yt = yll + dyi/2 + 5*syp + dyp/2;
xw = [xw xt xt-2*sxw xt-2*sxw xt+dxp+dxi+dxp+2*sxw xt+dxp+dxi+dxp+2*sxw NaN];
yw = [yw yt yt yt+syp+2*syw yt+syp+2*syw yt-syp NaN];

% 3
xt = xll - dxp;
yt = yll + dyi/2 + 4*syp + dyp/2;
xw = [xw xt xt-5*sxw xt-5*sxw NaN];
yw = [yw yt yt yt-4*syp-8*syw NaN];

% 4
xt = xll - dxp;
yt = yll + dyi/2 + 3*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw NaN];
yw = [yw yt yt yt+3*syw NaN];

% 5
xt = xll - dxp;
yt = yll + dyi/2 + 2*syp + dyp/2;
xw = [xw xt xt-2*sxw xt-2*sxw xt+dxp+dxi+dxp+sxw xt+dxp+dxi+dxp+sxw NaN];
yw = [yw yt yt yt-2*syp-syw yt-2*syp-syw yt-syp NaN];

% 6
xt = xll - dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt-4*sxw xt-4*sxw NaN];
yw = [yw yt yt yt-syp-7*syw NaN];

% 7
xt = xll - dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt-sxw xt-sxw NaN];
yw = [yw yt yt yt-syp-syw*3 NaN];

% 8
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 0*syp + dyp/2;
xw = [xw xt xt+3*sxw xt+3*sxw xt-dxp-dxi-dxp-2*sxw xt-dxp-dxi-dxp-2*sxw NaN];
yw = [yw yt yt yt-3*syw yt-3*syw yt-5*syw NaN];

% 9
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 1*syp + dyp/2;
xw = [xw xt xt+3*sxw NaN];
yw = [yw yt yt NaN];

% 10, 13
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 2*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw xt NaN];
yw = [yw yt yt yt+3*syp yt+3*syp NaN];
%xw = [xw xt+sxw xt+5*sxw NaN];
%yw = [yw yt+3*syp yt+3*syp NaN];

% 11
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 3*syp + dyp/2;
xw = [xw xt xt+2*sxw xt+2*sxw xt-dxp-dxi-dxp-3*sxw  xt-dxp-dxi-dxp-3*sxw NaN];yw = [yw yt yt yt-3*syp-2*syw yt-3*syp-2*syw yt-3*syp-6*syw NaN]; 
% 12
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 4*syp + dyp/2;
xw = [xw xt xt+3*sxw NaN];
yw = [yw yt yt NaN];

% 13
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 5*syp + dyp/2;
xw = [xw xt xt+3*sxw NaN];
yw = [yw yt yt NaN];

% 14
xt = xll + dxi + dxp;
yt = yll + dyi/2 + 6*syp + dyp/2;
xw = [xw xt xt+sxw xt+sxw NaN];
yw = [yw yt yt yt+3*syw NaN];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

xt = xll - dxp;
yt = yll + dyi/2 + 4*syp + dyp/2;
xt = xt-6*sxw;
yt = yt-syp;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(1)
clf
hold on
plot(xw, yw, 'k') %'r')
plot(xp, yp, 'k') %'b')
plot(xi, yi, 'k') %'k')
plot(xr, yr, 'k') %'m')
plot(xc, yc, 'k') %'g')
%plot(lrl, brb, 'k')
%plot(lcl, bcb+3, 'k')
axis("equal")
hold off

