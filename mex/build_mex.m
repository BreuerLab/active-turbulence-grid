function build_mex(filename)
% Build MEX file from src/ and output .mexw64 to mex/compiled/

% Always use character vectors
srcFile = fullfile('..', 'src', [filename, '.cpp']);       % ../src/ATG.cpp
outputFolder = fullfile(pwd, 'compiled');                  % absolute path to /mex/compiled
outputFile = fullfile(outputFolder, filename);             % e.g., /mex/compiled/ATG102

% Ensure the compiled output directory exists
if ~exist(outputFolder, 'dir')
    mkdir(outputFolder);
end

% Full path to .mexw64 file
mexTarget = [outputFile, '.', mexext];  % e.g., ATG102.mexw64

% Clean up old build file
if isfile(mexTarget)
    delete(mexTarget);  % <-- Will now work
end

% Compile the MEX file
mex( ...
    ['-I', fullfile('..', 'lib')], ...
    ['-I', 'C:\Program Files (x86)\Teknic\ClearView\sdk\inc'], ...
    ['-L', 'C:\Program Files (x86)\Teknic\ClearView\sdk\lib\win\Release\x64'], ...
    '-lsFoundation20.lib', ...
    '-output', outputFile, ...
    srcFile ...
);
end
