function [t] = build_sp_from_factor(fact, lambda)
%builds a sparse tensor from a factor list and lambdas

    %build an all zero sparse tensor
    t = sptensor([], [], size(fact{1}));
    
    %add all the factors
    for i = 1:size(fact, 1)
        t = t + lambda(i) * fact{i};
    end
end