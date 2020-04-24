myservo.write(180);
delay(500);
myservo.write(0);
delay(500);

¿Es eso lo que quieres?
También podría ser que lo quisieras hacer por pasos. En ese caso es tan sencillo como abrir los ejemplos del IDE y concretamente "Sweep"

for(pos = 0; pos < 180; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for(pos = 180; pos>=1; pos-=1)
  {
    myservo.write(pos);
    delay(15);
  }
