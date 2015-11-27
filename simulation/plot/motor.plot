set term latex
set output "motor.tex"
plot \
  "motor.tsv" using "t":"velocity" with linespoints pointinterval 40,\
  "motor.tsv" using "t":"current" with linespoints pointinterval 40
