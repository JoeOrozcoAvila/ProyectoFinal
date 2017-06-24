# ProyectoFinal
Proyecto: control de fluidos de un cultivo hidroponico
El sistema se compone de un circuito hidroponico de cuatro canaletas con un sensor de
nivel de agua cada una, un tanque de almacenamiento de agua con una mezcla de nutrientes
y un sensor de nivel que mide la cantidad de solucion en el tanque de almacenamiento.
Una bomba de agua dentro del contenedor y una valvula de drenado de solucion.
Las condiciones de inicio de ciclo son que los niveles de solucion en el contenedor y
posteriormente en las canaletas se encuentren en los niveles deseados, de lo contrario
se activa una alarma con un dispositivo piezoelectrico. Una vez cumplida la condicion
anterior, se inicia un ciclo de conteo de 10 ciclos por segundo, cada vez que este se
cumpla, se activara la bomba del contenedor, con el fin de hacer circular la solucion
por el sistema y evitar el estancamiento. Despues de 6 ciclos de circulacion se activa
la valvula de drenado para reemplazar la solucion utilizada.

El ciclo de tiempo normal en el sistema es de activacion de la bomba de circulacion
cada 12 horas y el drenado de solucion cada 30 dias. Se realiza en el tiempo descrito
en el primer parrafo con fines de demostracion en clase.
