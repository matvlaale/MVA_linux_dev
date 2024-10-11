file ./range
break range.c:22
set $iters = 28
set $itere = 35
set $iter = $iters
ignore 1 27
run -100 100 3 > /dev/null
while $iter <= $itere
  echo @@@
  print M
  echo @@@
  print N
  echo @@@
  print S
  echo @@@
  print i
  set $iter = $iter + 1
  c
end
ignore 1 34
c
quit
