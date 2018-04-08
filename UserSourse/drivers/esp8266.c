void esp_init() // настройка esp 
{
	delay_ms(50);
	
	delay_ms(500);
	reset_put(); // послть команду ресет 
	at_put(); // проверка связи 
	_delay_ms(500);
	wifi_conect();// ПОДКЛЮЧЕНИЕ К СЕТИ
	mod_put(); 
	_delay_ms(500);
	chipstart_put();
	//myx_put();
	_delay_ms(500);
	server_put_transparent_bridge();
	_delay_ms(500);
	uart_puts("ready\r\n");
	// server_put();
	//while (!uart_char_waiting()){
	// _delay_ms(100); 
	//}

sprintf(buffer_esp,"PC CONNECTED     ");


delay_ms(2000);
flag_lcd_wifi=0;
memset(buffer_esp,0,strlen(buffer_esp));
lcd_clear();
	flad_esp=1;
}

// Работа с WI-FI 
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//wi-fi ssdi conect
////////////////////////////////////////////////////////////////////////////
void wifi_conect(){ // AT+CWJAP="ssid","password"
	uart_puts("AT+CWJAP=");
	uart_puts(SSID);
	uart_puts(",");
	uart_puts(PASS_WORD);
	uart_puts("\r\n");
	_delay_ms(2000);
	if (uart_getERROR())
	{
		sprintf(buffer_esp,"WIFI N ER  ");
		flag_error=1;
		_delay_ms(2000);
		//esp_init(); // restart init
		
		return;
	}
	else{
		flag_error=0;
		sprintf(buffer_esp,"WIFI N OK  ");
		_delay_ms(1200);
		clear_uart(-1);
	}
}

////////////////////////////////////////////////////////////////////////////
void at_put(){
	uart_puts("AT\r\n");
	memset(buffer_esp,0,strlen(buffer_esp));
	_delay_ms(2000);
	uart_getsort(buffer_esp);
	
}
///////////////////////////////////////////////////////////////////////////

void mod_put(){ // AT+CIPMODE=1
	
	uart_puts("AT+CIPMODE=1\r\n");
	clear_uart(5);
	
		memset(buffer_esp,0,strlen(buffer_esp));
	_delay_ms(900);
	uart_getsort(buffer_esp);
	
	
}
/////////////////////////////////////////////////////////////////////////////

void myx_put(){
	
	uart_puts("AT+CIPMUX=1\r\n");
	clear_uart(5);
	
	memset(buffer_esp,0,strlen(buffer_esp));
	_delay_ms(2100);
	uart_getsort(buffer_esp);
	buffer_esp[strlen(buffer_esp)]=' ';
	_delay_ms(500);
	
}

/////////////////////////////////////////////////////////////////////////////
/*
void server_put(){ 
	
	uart_puts("AT+CIPSERVER=1,8888\r\n");
	clear_uart(5);
	
	memset(buffer_esp,0,strlen(buffer_esp));
	_delay_ms(2000);
	uart_getsort(buffer_esp);
	buffer_esp[strlen(buffer_esp)]=' ';
	
}*/

////////////////////////////////////////////////////////////////////////////  

void server_put_transparent_bridge(){ // AT+CIPSEND 
	
	uart_puts("AT+CIPSEND\r\n");
	
	memset(buffer_esp,0,strlen(buffer_esp));
	_delay_ms(1000);
	if (uart_getERROR())
	{
		sprintf(buffer_esp,"Con ER  ");
		flag_error=1;
		_delay_ms(2000);
		//esp_init(); // restart init
		
		return;
	}
	else{
	flag_error=0;
	sprintf(buffer_esp,"Con OK  ");
	_delay_ms(2000);
	}
	
	
}

////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
uint8_t controll_wifi_per(){ // не пашет 

char str_rull[BUFFER_SIZE+1]=" ";
int i=0;
while(uart_char_waiting()){
	str_rull[i]=uart_getchar();
	//uart_putchar(str_rull[i]);
	i++;
	
	if(i>=BUFFER_SIZE+1)
	i=0;
}
//str_rull[i]=' ';
str_rull[++i]='\0';


if (strstr(str_rull,"Motor=On") )
{
	_delay_ms(500);
	uart_puts("s-c:Motor=On");
	//temp_r=1;
	CHENL1ON;
}
if (strstr(str_rull,"Motor=Off")){
	_delay_ms(500);
	uart_puts("s-c:Motor=Off");
	CHENL1OFF;
	
}

if (strstr(str_rull,"LightAdd=On")){
	_delay_ms(500);
	uart_puts("s-c:LightAdd=On");
	CHENL2ON;
	
}

if (strstr(str_rull,"LightAdd=Off")){
	_delay_ms(500);
	uart_puts("s-c:LightAdd=Off");
	CHENL2OFF;
	
}

if (stcompare(str_rull, "auto")){//strstr(str_rull,"auto")
	_delay_ms(500);
	uart_puts("s-c:state_auto\n\r");
	
	CHENL2ON;
	CHENL1ON;
	//temp_r=1;
	}/* */
	i=0;
	
	//while(str_rull[i]){
	//	str_rull[i]=' ';
	//	i++;
	//}
	//uart_puts(str_rull);
	_delay_ms(200);
	return temp_r;
	

/*
	char str_rull[BUFFER_SIZE+1]=" ";
	int i=0;
	while(uart_char_waiting()){
		str_rull[i]=uart_getchar();
		uart_putchar(str_rull[i]);
		i++;
		
		if(i>=BUFFER_SIZE+1)
			i=0;	
			}		
	//str_rull[i]=' ';	
	str_rull[++i]='\0';
	
	
	if (strstr(str_rull,"Motor=on") ) 
	{
		_delay_ms(500);
		uart_puts("s-c:Motor=on\n\r");
		//temp_r=1;
		CHENL1ON;
		}
		if (strstr(str_rull,"Motor=off")){
			_delay_ms(500);
			uart_puts("s-c:Motor=off\n\r");
			CHENL1OFF;
			
			} 
			
			if (strstr(str_rull,"Extra_light=on")){
				_delay_ms(500);
				uart_puts("s-c:Extra_light=on\n\r");
				CHENL2ON;
				
			}
			
			if (strstr(str_rull,"Extra_light=off")){
				_delay_ms(500);
				uart_puts("s-c:Extra_light=off\n\r");
				CHENL2OFF;
				
			}
		
			if (stcompare(str_rull, "auto")){//strstr(str_rull,"auto")
				_delay_ms(500);
				uart_puts("s-c:state_auto\n\r");
				
				CHENL2ON;
				CHENL1ON;
				//temp_r=1;
			}
			i=0;
			
			//while(str_rull[i]){
			//	str_rull[i]=' ';
			//	i++;
			//}
			uart_puts(str_rull);
			_delay_ms(50);
	return temp_r;
		*/
}
////////////////////////////////////////////////////////////////////////////

bool stcompare(char *srt1, char *str2){
	
	return !strncmp(srt1,str2,(strlen(str2)));
	
}

////////////////////////////////////////////////////////////////////////////
void chipstart_put(){ // AT+CIPSTART="TCP","192.168.43.119",8080
	//char temp[BUFFER_SIZE]="";
	 //sprintf(temp,"AT+CIPSTART=\"TCP\",%s,%d\r\n",IP_con,PORT_CON);
	//uart_puts(temp);
	uart_puts("AT+CIPSTART=\"TCP\",");
	uart_puts(IP_con);
	uart_puts(",");
	uart_puts(PORT_CON);
	uart_puts("\r\n");
	_delay_ms(500);
}

////////////////////////////////////////////////////////////////////////////
/*
void data_ready_put(){
	
	uart_puts("AT+CIPSEND=0,7\r\n");
	_delay_ms(1000);
	uart_puts("ready\r\n");
	_delay_ms(1000);
	clear_uart(-1);
	
}*/
//////////////////////////////////////////////////////////////////////////////
/*
void data_put(char *str){
	
	char temp[BUFFER_SIZE]="";
	sprintf(temp,"AT+CIPSEND=0,%d\r\n",strlen(str));
	uart_puts(temp);
	delay_ms(100);
	//clear_uart(-1);
	if (uart_getERROR()) // изменено
	{
		flag_lcd_wifi=1;
		sprintf(buffer_esp,"WI-FI ER");
		delay_ms(2000);
		memset(buffer_esp,0,strlen(buffer_esp));
		esp_init();
		return;
	}
	////////////////// думать 
	uart_puts(str);
	delay_ms(100);
	clear_uart(0);


	if (uart_getERROR())
	{

		flag_lcd_wifi=1;
			sprintf(buffer_esp,"WI-FI ER");
			delay_ms(2000);
			memset(buffer_esp,0,strlen(buffer_esp));
			flag_error=0;
			delay_ms(200);
			esp_init();
		
	}
	
	
}
*/
/////////////////////////////////////////////////////////////////////////////
void reset_put(){
	sprintf(buffer_esp,"WI-FI RESET");
	uart_puts("+++");
	_delay_ms(500);
	uart_puts(" \r\n");
	_delay_ms(500);
	uart_puts("AT+RST\r\n");
	_delay_ms(10);
	cli();
	_delay_ms(10000);
	sei();
	
	_delay_ms(500);
	clear_uart(-1);
	///
	memset(buffer_esp,0,strlen(buffer_esp));
}
