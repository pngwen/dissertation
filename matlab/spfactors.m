function [factors] = spfactors(k)
%this function converts the ktensor into a list of sparse tensor factors

    %get the factor and mode count
    nfactors = size(k.U{1}, 2);
    nmodes = size(k.U, 1);

    %create the cells for the factors
    factors = cell(nfactors, 1);

    %loop over each factor
    for i = 1:nfactors
        %start off with the sparse tensor from the first mode
        factors{i} = tospvect(k.U{1}(:,i));
        
        %take the outer product of each remaining mode
        for j = 2:nmodes
            factors{i} = ttt(factors{i}, tospvect(k.U{j}(:,i)));
            
            %force the retention of a sparse tensor
            if isa(factors{i}, 'tensor')
               factors{i} = sptensor(factors{i}); 
            end
        end
    end
end


function [spt] = tospvect(v)
    %Extract the index list and the values
    [spi, ~, spval] = find(v);

    %create the sparse tensor
    spt = sptensor(spi, spval, size(v,1));
end