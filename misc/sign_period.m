clear
clc

% INPUTS
m = 5;
start_prime = 43;
periods =  list_primes(length(primes(start_prime))+(m-1));
periods = periods(end-(m-1):end)
max_p = max(periods);

% SIMULATING
n = 10000;
x = linspace(0,60,n);

Y = zeros(m,n);
for ii = 1:m
    % COPY THIS EQUATIONS TO OUTPUT PART!
    Y(ii,:) = exp(cos(2*pi*x*periods(ii)/max_p)*3);
end
Y = Y .- min(min(Y));
Y = Y ./ max(max(Y));
y_sum = sum(Y);

% PLOTTING
figure(1)
clf
hold on

for ii = 1:m
    subplot(m+1,1,ii);
    plot(x,Y(ii,:))
end

subplot(m+1,1,m+1);
area(x, y_sum, 'FaceColor', 'r', 'EdgeAlpha', 0)

hold off


% OUTPUT
n = 256;
x = linspace(-pi,pi,n);
y = zeros(1,n);
% COPY EQUATION TO HERE!
y = exp(cos(x)*3);
y = y .- min(y);
y = y ./ max(y);
y = y .* 255;

fout = fopen('ADD_TO_HEADER.cpp', 'w');
fprintf(fout, '////////////////////////////////////////////////////////////////\n');
fprintf(fout, '// BEGIN SECTION GENERATED BY sign_period.m\n');
fprintf(fout, '\n');

% #define CURVE_LENGTH 256
% #define MS_IN_S 1000
% #define MIN_FREQ 43
% #define FREQUENCY_COUNT 5
% #define F_NUM CURVE_LENGTH
% #define F_DEN (MS_IN_S * MIN_FREQ)
%
fprintf(fout, '#define CURVE_LENGTH %d\n', n);
fprintf(fout, '#define MS_IN_S 1000\n');
fprintf(fout, '#define MIN_FREQ %d\n', min(periods));
fprintf(fout, '#define FREQUENCY_COUNT %d\n', m);
fprintf(fout, '#define F_NUM CURVE_LENGTH\n');
fprintf(fout, '#define F_DEN (MS_IN_S * MIN_FREQ)\n');
fprintf(fout, '\n');

%const unsigned int frequencies[] = {43*F_NUM, 47*F_NUM, 53*F_NUM, 59*F_NUM, 61*F_NUM};
%
fprintf(fout, 'const unsigned int frequencies[] = {');
for ii = 1:m
    fprintf(fout, '%d*F_NUM', periods(ii));
    if ii < m
        fprintf(fout, ', ');
    end
end
fprintf(fout, '};\n');
fprintf(fout, '\n');

%const uint8_t curve[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 10, 11, 11, 12, 13, 14, 16, 17, 18, 20, 21, 23, 24, 26, 28, 30, 33, 35, 38, 40, 43, 46, 49, 53, 56, 60, 64, 68, 73, 77, 82, 87, 92, 97, 102, 108, 113, 119, 125, 131, 137, 144, 150, 156, 163, 169, 175, 181, 188, 194, 200, 205, 211, 216, 221, 226, 231, 235, 239, 242, 245, 248, 250, 252, 254, 255, 255, 255, 255, 254, 252, 250, 248, 245, 242, 239, 235, 231, 226, 221, 216, 211, 205, 200, 194, 188, 181, 175, 169, 163, 156, 150, 144, 137, 131, 125, 119, 113, 108, 102, 97, 92, 87, 82, 77, 73, 68, 64, 60, 56, 53, 49, 46, 43, 40, 38, 35, 33, 30, 28, 26, 24, 23, 21, 20, 18, 17, 16, 14, 13, 12, 11, 11, 10, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
%
fprintf(fout, 'const uint8_t curve[] = {');
for ii = 1:n
    fprintf(fout, '%d', round(y(ii)));
    if ii < n
        fprintf(fout, ', ');
    end
end
fprintf(fout, '};\n');
fprintf(fout, '\n');

fprintf(fout, '// END SECTION GENERATED BY sign_period.m\n');
fprintf(fout, '////////////////////////////////////////////////////////////////\n');
fclose(fout);
