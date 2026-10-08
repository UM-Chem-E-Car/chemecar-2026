for i = 30:34
data = getData(i);
Cutoff_Value = 3;
data = data(Cutoff_Value:end,:);
WINDOW_SIZE = 1;
data.Value = movmean(data.Value, [WINDOW_SIZE-1 0]);




startb = 500;
endb = 1000;

starte = 59000;
ende = 60000;

maskb = data.Time >= startb & data.Time <= endb;
BenchMark = mean(data.Value(maskb, :));

maske = data.Time >= starte & data.Time <= ende;
EndMark = mean(data.Value(maske, :));


reactioninfo = BenchMark - EndMark;
reactioninfo = fix(reactioninfo * 100) / 100;


figure(i);
plot(data.Time, data.Value, "Color", "m");
hold on
plot(data.Time, [0; diff(data.Value)], "Color", "b");
xregion(startb, endb, 'FaceColor', 'yellow', 'FaceAlpha', 0.3);
xregion(starte, ende, 'FaceColor', 'yellow', 'FaceAlpha', 0.3);
xlim([0, 60e3]);
ylim([0, 1100]);
title(reactioninfo)
hold off

end

function ret = getData(testNum);
fileName = "Run" + testNum + ".csv";
cd(fullfile("C:","Users","aryar","UM-ChemE-Car"));   % set to correct folder
isfile("./iguana_platformio/data/" + fileName);   % true if file exists

opts = detectImportOptions("./iguana_platformio/data/"+fileName,'Delimiter',','); % or set to correct delimiter
opts.PreserveVariableNames = true;

ret = readtable("./iguana_platformio/data/"+fileName, ...
    'Delimiter', ',', ...
    'ReadVariableNames', true, ...
    'VariableNamingRule', 'preserve');
end

function f = filt(x)
windowSize = 1; 
b = (1/windowSize)*ones(1,windowSize);
a = 1;
f = filter(b,a,x);
end