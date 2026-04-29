#include <arduinoPins.h>


/**
 * @brief Inicializa o conversor AD. Essa função deve ser chamado apenas vez durante a execução do Firmware
 * 
 */
void ADCInit(void);

/**
 * @brief Faz uma leitura do conversor AD
 * 
 * @param channel 
 * @return uint16_t 
 */
uint16_t ADCRead(uint8_t channel);