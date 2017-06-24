/* PROYECTO: Control de fluidos de un cultivo hidroponico

El sistema se compone de un circuito hidroponico de cuatro canaletas con un sensor de
nivel de agua cada una, un tanque de almacenamiento de agua con una mezcla de nutrientes
y un sensor de nivel que mide la cantidad de solucion en el tanque de almacenamiento.
Una bomba de agua dentro del contenedor y una valvula de drenado de solucion.
Las condiciones de inicio de ciclo son que los niveles de solucion en el contenedor y
posteriormente en las canaletas se encuentren en los niveles deseados, de lo contrario
se activa una alarma con un dispositivo piezoelectrico. Una vez cumplida la condicion
anterior, se inicia un ciclo de conteo de 60 ciclos por segundo, cada vez que este se
cumpla, se activara la bomba del contenedor, con el fin de hacer circular la solucion
por el sistema y evitar el estancamiento. Despues de 6 ciclos de circulacion se activa
la valvula de drenado para reemplazar la solucion utilizada.

El ciclo de tiempo normal en el sistema es de activacion de la bomba de circulacion
cada 12 horas y el drenado de solucion cada 30 dias. Se realiza en el tiempo descrito
en el primer parrafo con fines de demostracion en clase.
*/


#include<stdio.h>
#include<pigpio.h>


int main()
{
	
	//entradas - sensores de nivel de fluido
	int sens1, sens2, sens3, sens4;
	//contador de horas, contador de dias
	int cont1=0, cont2=0;
	//variables de control
	int st, c, i;
	int x=1;
	if(gpioInitialise()<0) return -1;
	gpioSetMode(26, PI_INPUT);//sensor nivel tanque
	gpioSetMode(19, PI_INPUT);//sensor nivel canaleta1
	gpioSetMode(13, PI_INPUT);//sensor nivel canaleta2
	gpioSetMode(06, PI_INPUT);//sensor nivel canaleta3
	gpioSetMode(05, PI_INPUT);//sensor nivel canaleta4
	
	gpioSetMode(21, PI_OUTPUT);//Bomba de agua/motor
	gpioSetMode(20, PI_OUTPUT);//Alarma/buzzer
	gpioSetMode(16, PI_OUTPUT);//Valvula de drenado/led
	gpioSetPWMfrequency(20, 600);
	gpioSetPWMrange(20, 255);
	gpioWrite(21, 0);
	gpioWrite(16, 0);
	gpioPWM(20, 0);
	while(x)
	{  st=gpioRead(26);
	while(st)//nivel del tanque
	{  sens1=gpioRead(19);
	sens2=gpioRead(13);
	sens3=gpioRead(06);
	sens4=gpioRead(05);
	while(sens1&&sens2&&sens3&&sens4)//nivel de canaletas
	{  st=gpioRead(26);
	cont1++;
	sleep(1);
	if(cont1>=10)//activar bomba para circulacion de solucion
	{ cont1=0;
	cont2++;
	gpioWrite(21, 1);
	sleep(5);
	gpioWrite(21, 0);
	if(cont2>=5)//activar valvula de drenado
	{  cont2=0;
	gpioWrite(16, 1);
	sleep(4);
	gpioWrite(16, 0);
	break;
	}
	}
	if(!st)
		break;
	}
	
	if(!(sens1&&sens2&&sens3&&sens4))//activar bomba para nivelar canaletas
	{  gpioWrite(21, 1);
	sleep(5);
	gpioWrite(21, 0);
	}
	}
	if(!st)//alarma de contenedor con nivel bajo de solucion
	{ for(c=0;c<4;c++)
	{ for(i=0;i<255;i++)
		gpioPWM(20, i);
	sleep(2);
	gpioPWM(20, 0);
	sleep(2);
	}
	}
	}
	
	gpioTerminate();
	return 0;
}


		
