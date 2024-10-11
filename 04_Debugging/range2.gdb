file ./range
break range.c:22
run -100 100 3 > /dev/null
set $iters = 28
set $itere = 35
set $iter = $iters
set $count = 1
set $endi = 100 - 2
while $count < $iters
  set $count = $count + 1
  c
end
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
while i < $endi
  c
end
c
quit
