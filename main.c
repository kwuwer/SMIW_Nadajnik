/* ----------------------------------------------------------
 * 10_LED_WIFI_RX
 * ----------------------------------------------------------
 */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


#include "src/oled/u8g.h"		// Obsługa wyświetlacza
#include "src/nrf24/nrf24.h"

/*
 * 	Zmienne globalne
 */
u8g_t u8g;
uint8_t rx_mac[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};	// To urządzenie ma 0xE7
uint8_t tx_mac[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};  // Zdalne urządzenie
uint8_t packet[3];								// Pakiet z danymi
uint8_t localStates[2] = {0,0};
uint8_t status;

/*
 * Inicjalizacja wyświetlacza SH1106 po protokole IIC (AVR: TWI)
 */
void u8g_setup(){
	u8g_InitI2C(&u8g, &u8g_dev_sh1106_128x64_i2c, U8G_I2C_OPT_NONE);
}
/*
 * Inicjalizacja modułu nRF24L01 (Wireless)
 */
void wifi_setup(){
	nrf24_init();
	nrf24_config(4,3);
	nrf24_rx_address(rx_mac);
	nrf24_tx_address(tx_mac);
}
/*
 * Wyświetla komunikat na środku ekranu:
 * buffer - ciąg znaków do wyświetlenia
 */
void oprint(char * buffer){
	u8g_FirstPage(&u8g);
	do{
		u8g_SetFont(&u8g, u8g_font_6x13r);
		u8g_DrawStr(&u8g, 0, 35, buffer);
	} while(u8g_NextPage(&u8g));
	u8g_Delay(100);
}
/*
 * Wyświetla obecne stany na wyświetlaczu OLED
 */
void printStates(){
	char b1[12];
	char b2[12];
	itoa(localStates[0],b1,10);
	itoa(localStates[1],b2,10);
	u8g_FirstPage(&u8g);
	do{
		u8g_DrawFrame(&u8g, 70,3,30,13);
		u8g_DrawFrame(&u8g, 70,23,30,13);
		if (localStates[0] == 0x01){
			u8g_DrawBox(&u8g, 72,5 ,10,9);
		} else {
			u8g_DrawBox(&u8g, 88,5 ,10,9);
		}
		if (localStates[1] == 0x01){
					u8g_DrawBox(&u8g, 72,25 ,10,9);
				} else {
					u8g_DrawBox(&u8g, 88,25 ,10,9);
				}
		u8g_SetFont(&u8g, u8g_font_6x13r);
		u8g_DrawStr(&u8g, 0, 15, "Kanal 1:");
		u8g_DrawStr(&u8g, 55, 15, "ON");
		u8g_DrawStr(&u8g, 105, 15, "OFF");
		u8g_DrawStr(&u8g, 0, 35, "Kanal 2:");
		u8g_DrawStr(&u8g, 55, 35, "ON");
		u8g_DrawStr(&u8g, 105, 35, "OFF");
	} while(u8g_NextPage(&u8g));
	u8g_Delay(50);
}
/*
 * Funkcja wysyła pakiet i zwraca kod 1 jeśli wystąpił błąd podczas wysyłania pakietu
 */
uint8_t sendPacket(){
	nrf24_send(packet);
		while(nrf24_isSending());
		status = nrf24_lastMessageStatus();

		if(status != NRF24_TRANSMISSON_OK)
		{
			oprint("Blad transmisji!");
			_delay_ms(1000);
			return 1;
		}
		nrf24_powerUpRx();
		return 0;
}

/*
 * Inicjalizacja urządzenia:
 * Komunikacja z odbiornikiem i odpytanie o stany początkowe
 */
void init(){

	PORTD |= (1<<PD6) | (1<<PD7);
	DDRD = 0x00;

	oprint("Inicjalizacja...");

	packet[0]=0x00;
	packet[1]=0x00;
	packet[2]=0xFF;
	status = sendPacket();
	_delay_ms(50);

	while(1){
		if (nrf24_dataReady()){
			nrf24_getData(packet);
			if (packet[2] == 0xFE){
				localStates[0] = packet[0];
				localStates[1] = packet[1];
				printStates();
				break;
			} else {
				oprint("Blad transmisji!");
				return;
			}
		}
	}
}

/*
 * Zmień status 1-go kanału [0]
 */
void buttonOne(){
	localStates[0] ^= 0x01;
	packet[0] = localStates[0];
	packet[1] = localStates[1];
	packet[2] = 0xEF;
	status = sendPacket();
	if (status){
		localStates[0] ^= 0x01;
	}
}

/*
 * Zmień status 2-go kanału [0]
 */
void buttonTwo(){
	localStates[1] ^= 0x01;
	packet[0] = localStates[0];
	packet[1] = localStates[1];
	packet[2] = 0xEF;
	status = sendPacket();
	if (status){
		localStates[1] ^= 0x01;
	}
}

int main(){

	u8g_setup();
	wifi_setup();
	init();
	while(1){
		printStates();
		// Naciśnięty guzik
		if (!(PIND & (1<<PD6))){
		buttonOne();
		_delay_ms(40); // Debounce
		}
		if (!(PIND & (1<<PD7))){
		buttonTwo();
		_delay_ms(40); // Debounce
		}

	}

	return 0;
}


