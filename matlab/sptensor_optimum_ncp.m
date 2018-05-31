function [F, scree, info] = sptensor_optimum_ncp(tns)
% Returns the optimum non-negative factorization of a sparse tensor.
% Input: tns - the sparse tensor to decompose
% Output: F - The ktensor containing the factor matrices
%         scree - A list of the error of each attempted decomposition.
%         info - The information struct from the ncp function.
% This function works by trying all factorizations from 2 factors up to 
% n factors where n is the number of non-zero elements in tns
    
%Get the number of non-zero elements
n = nnz(tns);

%allocate the scree matrix
scree = zeros(n, 2);
scree(1,:) = [1 1];

%get ready for the best (2 is not every in the running!)
best_error = 2;

%run through all the possible outcomes
for nf = 2:n
    %run the decomposition
    disp(nf)
    evalc("[tf, iter, r] = ncp(tns, nf)");
    
    %remember it if it is the best
    if r.final.rel_Error < best_error 
        F = tf;
        info = r;
        best_error = r.final.rel_Error;
    end
    
    %record the scree value
    scree(nf, :) = [ nf r.final.rel_Error ];
end

end