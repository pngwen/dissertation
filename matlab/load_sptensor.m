function [tns] = load_sptensor(file, dim)
    data = dlmread(file, '\t');
    modes = size(dim, 2);
    tns = sptensor(data(:,1:modes), data(:,modes+1), dim);
end