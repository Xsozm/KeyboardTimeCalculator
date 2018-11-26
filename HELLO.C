#include <REG52.H>                                              
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
unsigned int counter0=0;

char key[10] = {
	'.','t','i','e','5','R','o','n','a','l'};
unsigned char  start=1;
unsigned long ans[9] ;
unsigned long ans2[9];
unsigned int test[9];
//unsigned int Btest[9];
unsigned char  idx= 0;
unsigned long DA = 0 ;
unsigned long DB= 0 ;
unsigned char c = 0;
sbit trainAndTest =P0^1;
sbit current = P0^0;
sbit LED=P1^0;
unsigned char ledDelay=0;
	void msdelay(unsigned int value){
 
unsigned int x,y;
for(x=0;x<value;x++)
for(y=0;y<1275;y++);
}
void timer0_isr(void) interrupt 1 {
if(ledDelay==1){
		LED=!LED;
			LED=!LED;
}
TH0=0xFC;
TL0=0x66;
TF0 = 0; // Reset the interrupt request
counter0+=1;
}

void main (void) {
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x21;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = 0xF3;                /* TH1:  reload value for 1200 baud @ 16MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;                  /* TI:   set TI to send first char of UART    */
		EA=1;
		ET0=1;
		TH0=0xFC;
		TL0=0x66;
		P0=0xFF;
		
  while (trainAndTest==0) {
		char x;
				//printf("phase 1");
		if(RI){
			 x=SBUF;
			RI=0;
			//printf("x is %c key of %d is %c \n",x,idx,key[idx]);
		}
		
	if(start==1 && x=='.'){
		//printf("case . \n");
		counter0=0;
		TR0=1;
		start=0;
		idx++;
		
	}
	else if(x==key[idx]){
		//printf("case normal \n");
		if(current==0)
		ans[(idx-1)%10]+=counter0;
		if(current==1)
		ans2[(idx-1)%10]+=counter0;
		//printf("counter between %c and %c is %d \n",key[idx-1],key[idx],counter0);
		TR0=0;
		counter0=0;
		TR0=1;
		idx++;
		//printf("next letter is %c \n",key[idx]);
	}
	if(idx%10==0 && idx!=0){
		start=1;
		TR0=0;
		idx=0;
		counter0=0;
		c++;
	//	printf("counter of words is now %d \n",c);
		if(c>=1 && current==0){
			current=1;
			idx=0;
			counter0=0;
			TR0=0;
			c=0;
		//	printf("current:%d \n",current);
		}
		else if(c>=1 && current==1){
			start=1;
			idx=0;
			counter0=0;
			TR0=0;
			trainAndTest=1;
		
		}
	}
}

while(idx<9){
		ans[idx]=ans[idx]/5;
		idx++;
	}
idx=0;
while(idx<9){
		ans2[idx]=ans2[idx]/5;
		idx++;
	}
idx=0;
//current = rand()% 1;
while(trainAndTest==1){
	
		char x;
		//printf("p2 \n");
		if(RI){
			 x=SBUF;
			RI=0;
			//printf("x is %c key of %d is %c \n",x,idx,key[idx]);
		}
	if(start==1 && x=='.'){
	//	printf("case . \n");
		counter0=0;
		TR0=1;
		start=0;
		idx++;
		
	}
	else if(x==key[idx]){
		//printf("case normal \n");
		test[(idx)]+=counter0;
		//printf("counter between %c and %c is %d \n",key[idx-1],key[idx],counter0);
		TR0=0;
		counter0=0;
		TR0=1;
		idx++;
		//printf("next letter is %c \n",key[idx]);
	}
	//else{
		//idx=0;
	//	counter0=0;
	//	TR0=0;
	//}
	if(idx==9){
		
		unsigned char i;
		TR0=0;
		for (i = 0; i < 9; i++){
			DA=DA+((test[i]-ans[i])*(test[i]-ans[i]));
		}
		//DA=sqrt(DA);
		for (i = 0; i < 9; i++){
			DB=DB+((test[i]-ans2[i])*(test[i]-ans2[i]));
		}
		//DB=sqrt(DB);
		if(DB>DA){
			LED=!LED;
			msdelay(300);
			LED=!LED;
		}
		else{
			LED=!LED;
				msdelay(300);
			LED=!LED;
				msdelay(1000);
			LED=!LED;
				msdelay(300);
			LED=!LED;
			//TR0=0;
			//ledDelay=1;
			//TH0=0xFF;
			//TL0=0xFF;
			//TR0=1;
			//LED=!LED;
		}
		TR0=0;
		idx=0;
		counter0=0;
		

}

		

	}
}
