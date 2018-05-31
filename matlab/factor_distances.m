function [dm] = factor_distances(flist)
%generate a distance matrix from the tensor factor list
    n = size(flist, 1);
    dm = zeros(n,n);
    
    for i = 1:n
        for j = 1:n
            dm(i,j) = l1dist(flist{i}, flist{j});
            %dm(i,j) = l2dist(flist{i}, flist{j});
        end
    end
end

function [d] = l1dist(x, y)
    [~,dt] = find(x - y);
    d = sum(abs(dt));
end

function [d] = l2dist(x,y)
    [~,dt] = find(x-y);
    d = sqrt(sum(dt.^2));
end