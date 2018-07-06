function [tns] = load_sptensor(file)
    data = dlmread(file, '\t');
    modes = data(1,1);
    dim = data(1,2:modes+1);
    nrows = size(data,1);	
    tns = sptensor(data(2:nrows,1:modes), data(2:nrows,modes+1), dim);
end
