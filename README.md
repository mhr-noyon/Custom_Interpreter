main:
     int x, y = 5;
     print "Enter x=";
     scan x;
     if x < y:
          print "Max: ", y;
     elif y > x:
          print "Max: ", x;
     else:
          print "Equal";
     endif
     int size = 10;
     loop int i=1 : i<= size: i=i+1:
          if i<=5:
               print i;
          else:
               break;
          endif
     endloop
endmain

     