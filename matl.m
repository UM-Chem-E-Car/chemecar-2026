

% makeplots(4, 10000);
% makeplots(1, 10000);
% makeplots(2, 10000);
% makeplots(3, 10000);
% makeplots(4, 10000);

for i = 1:10;
    makeplots(i, 10000);
end

% makeplots(11, 10000);
% makeplots(12, 10000);
% makeplots("1A", 10000);
% makeplots("1B", 10000);
% makeplots("1C", 10000);

function makeplots(testNum, time)
fileName = "Reaction" + testNum + "A.csv";
cd(fullfile("C:","Users","aryar","UM-ChemE-Car"));   % set to correct folder
isfile("./iguana_platformio/data/" + fileName);   % true if file exists

opts = detectImportOptions("./iguana_platformio/data/"+fileName,'Delimiter',','); % or set to correct delimiter
opts.PreserveVariableNames = true;

data = readtable("./iguana_platformio/data/"+fileName, ...
    'Delimiter', ',', ...
    'ReadVariableNames', true, ...
    'VariableNamingRule', 'preserve');

figure(testNum)
% myPlot(data.Time, averageChannel(), "b");
% hold on
% avgChannel = averageChannel();
% 
% figure(testNum);
% hold on;
% 
% myPlot(data.Time, avgChannel, "b");
% 
% Find maximum


% Horizontal line at maximum

% Optional: mark maximum point


% hold off


myPlot(data.Time, data.Value, "m");
hold on
xlim([0, 60e3]);
ylim([0,300])
% myPlot(data.Time, filt(data.b), "b");
% myPlot(data.Time, filt(data.c), 'c');
% myPlot(data.Time, filt(data.g), 'g');
% myPlot(data.Time, filt(data.gy), [161 235 52]/255);
% myPlot(data.Time, filt(data.y), 'y');
% myPlot(data.Time, filt(data.o), [235 150 52]/255);
% myPlot(data.Time, filt(data.r), 'r');
% myPlot(data.Time, filt(data.cl), 'w');
% myPlot(data.Time, filt(data.nir), [0 0 0]);

% [maxValue, maxIndex] = max(data.gy(50:end));
% yline(maxValue, 'r--', 'LineWidth', 1.5);


% title(data.Time(maxIndex));

hold off
end


function myPlot(time, input, color)
cutoffValue = 10;
plot(time(cutoffValue:end), input(cutoffValue:end), ...
    'Color', color, 'LineWidth', 1.5);
end

function ret = averageChannel()
    global data;
    wavelengths = [1, 2, 3, 4, 5];
    % wavelengths = [415, 445, 480, 515, 555, 590, 630, 680];
    % Sensor channel values
    values = [
        % data.v, ...
        data.b, ...
        data.c, ...
        data.g, ...
        data.gy, ...
        data.y, ...
        % data.o, ...
        % data.r
        ];
    
    % Weighted average wavelength for every time sample
    ret = sum(values .* wavelengths, 2) ./ sum(values, 2);
    
end

function f = filt(x)
    windowSize = 1; 
    b = (1/windowSize)*ones(1,windowSize);
    a = 1;
    f = filter(b,a,x);
end