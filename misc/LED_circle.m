clear
clc

% mm
w = 16.6;
h = 13;
w_L = 5;
h_L = 5;

h1 = (h - h_L) / 2;
h2 = h - h1;
w1 = (w - w_L) / 2;
w2 = w - w1;

r_o = 254/2; % 127
r_i = r_o * 0.931;
theta = linspace(0,2*pi,100);
x_c = cos(theta);
y_c = sin(theta);

x_d_b = [0 w w 0 0];
y_d_b = [0 0 h h 0];
x_d_L = [w1 w2 w2 w1 w1];
y_d_L = [h1 h1 h2 h2 h1];

%figure(0)
%clf
%hold on
%plot(x_d_b, y_d_b, 'b')
%plot(x_d_L, y_d_L, 'r')
%hold off


% method 1, full size
x0 = 2*w/2 + 0.003;
y0 = sqrt(r_o^2 - x0^2);
k = 0;
y_top = y0;
y_bot = y0 - h;
n = [];
while y_bot > -r_o
    y_max = max(abs(y_top), abs(y_bot));
    x_max = 2 * sqrt(r_o^2 - y_max^2);
    n(k+1) = floor(x_max / w);
    k = k + 1;
    y_top = y_top - h;
    y_bot = y_bot - h;
end


row_distances_from_top = ((r_o - y0) + h * [0:k]')/10
number_of_rows = k
count_by_row = [1:k; n; cumsum(n)]'
row_half_and_full_widths = w/10*[0.5*n; n]' - [0.25*ones(k,1) 0.5*ones(k,1)]
total = sum(n)


figure(1)
clf
hold on
for ii = 1:k
    y_d_0 = y0 - ii * h;
    x_d_0 = -1 * n(ii) * w / 2;
    for jj = 1:n(ii)
        plot(x_d_0 + x_d_b, y_d_0 + y_d_b, 'b')
        plot(x_d_0 + x_d_L, y_d_0 + y_d_L, 'r')
        x_d_0 = x_d_0 + w;
    end
end
plot(r_o * x_c, r_o * y_c, 'k')
plot(r_i * x_c, r_i * y_c, 'k')
axis("equal")
hold off



%% method 2, LED size
%x0 = w_L/2 + 0.001;
%y0 = sqrt(r_o^2 - x0^2);
%k = 0;
%y_top = y0 - h1;
%y_bot = y0 - h2;
%n = [];
%while y_bot > -r_o
%    y_max = max(abs(y_top), abs(y_bot));
%    x_max = 2 * sqrt(r_o^2 - y_max^2);
%    n(k+1) = floor((x_max - 1) / w) + 1;
%    k = k + 1;
%    y_top = y_top - h;
%    y_bot = y_bot - h;
%end
%
%
%k
%n'
%sum(n)
%
%
%figure(2)
%clf
%hold on
%for ii = 1:k
%    y_d_0 = y0 - ii * h;
%    x_d_0 = -1 * n(ii) * w / 2;
%    for jj = 1:n(ii)
%        plot(x_d_0 + x_d_b, y_d_0 + y_d_b, 'b')
%        plot(x_d_0 + x_d_L, y_d_0 + y_d_L, 'r')
%        x_d_0 = x_d_0 + w;
%    end
%end
%plot(r_o * x_c, r_o * y_c, 'k')
%plot(r_i * x_c, r_i * y_c, 'k')
%hold off
