#!/usr/bin/env python
import sys

#check the command line
if len(sys.argv) != 4:
  print("Usage: %s n vocabulary docfile"%(sys.argv[0],))
  sys.exit(1)

#read the vocabulary in
v = {}
file = open(sys.argv[2])
for line in file:
  line = line.split('\t')
  v[line[0]] = int(line[1])
file.close()

#load the array of words up
file = open(sys.argv[3])
doc = []
for line in file:
  doc = doc + line.split()
file.close()

#count the ngrams
tns = {}
n = int(sys.argv[1])
for i in range(0, len(doc)-n):
  #build the ngram and index
  ngram = doc[i:i+n]
  idx = []
  for w in ngram:
    idx.append(v[w])
  idx = tuple(idx)

  #increment the count for this ngram
  if idx in tns:
    tns[idx] += 1
  else:
    tns[idx] = 1
    
#print out the ngrams
for idx in tns:
  for i in idx:
    print(i, end="\t")
  print(tns[idx])
