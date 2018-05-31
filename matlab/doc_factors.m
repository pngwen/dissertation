function [factors, ktns, scree, info] = doc_factors(tns)
% Returns the optimum factorization of a sparse document tensor.
% Input: tns - The sparse document tensor to factor
% Output: factors - List of sparse tensor factors
%         ktns - The kruskal tensor of the factorization
%         scree - The scree list for the optimization attempts
%         info - the ncp info struct

%get the factorization
[ktns, scree, info] = sptensor_optimum_ncp(tns);

%build the factors
factors = spfactors(ktns);

end