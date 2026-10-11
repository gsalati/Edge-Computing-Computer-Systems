/**
* Envia um valor aleatório para outro dispositivo conectado em sua porta serial
* Aguarda uma confirmação da mensagem (0x01 - OK | 0x00 - NOK)
* O LED montado na placa pisca conforme a resposta recebida
*/
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
}

/**
 * @brief Aguarda por timeoutMs millisegundos o recebimento de pktSize bytes na serial
 * 
 * @param timeoutMs tempo para aguardar antes de falhar em ms
 * @param pktSize quantidade de bytes a serem recebidos
 * @return true Em caso de recebimento
 * @return false Se timeout
 */
bool waitForSerial(unsigned long timeoutMs,size_t pktSize);

/**
 * @brief Pisca o led embarcado na placa x vezes
 * 
 * @param x 
 */
void blinkLedFast(uint8_t x);

void loop() {
  uint8_t byteTx = 20;
  uint8_t byteRx = 0x00;
  unsigned long startWait = 0;
  bool rx;

  while(1)
  {
    // Buffer que será enviado. Tamanho 1 byte
    byteTx = 20 + (int8_t)random(-5,5);
    /*
    * Função sizeof retorna o tamanho em bytes da variável passada como argumento
    * Ex: Se fosse um vetor de 4 uint8_t, retornaria 4....
    */

    /*
    * Escreve na porta serial
    * Note o use do método write e não print
    */ 
    Serial.write((char*)&byteTx, sizeof(byteTx));
    
    // Aguarda resposta de tamanho 1 byte com timeout 5000ms = 5 segundos
    rx = waitForSerial(5000, sizeof(byteRx));
    if(rx)
    {
      // Le o que foi recebido na porta serial
      Serial.readBytes(((char*)&byteRx), sizeof(byteRx));
      if(byteRx == 0x01) // Resposta OK!
      {
        blinkLedFast(1);
      }else
      {
        blinkLedFast(3);
      }
    }else
    {
      // Resposta nao recebida. Pisca o led interno para sinalizar
      blinkLedFast(5);
    }

    /**
    * Notem um problema em utilizar o delay aqui. O tempo entre envio de mensagens é totalmente não deterministico;
    * Não sabemos quanto tempo iremos esperar pela resposta.
    * Em caso de não resposta, o tempo de execução da função q pisca os leds também é adicionado ao intervalo;
    * Uma implementação com millis garante que as ações ocorrem sempre no mesmo intervalo ;)
    */
    delay(1000);
  }

}


bool waitForSerial(unsigned long timeoutMs, size_t pktSize) {
    unsigned long start = millis();

    while (Serial.available() < pktSize) {
        if (millis() - start >= timeoutMs) {
            return false;
        }
    }

    return true;
}


void blinkLedFast(uint8_t x)
{
  uint8_t i;
  for(i = 0; i < x; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}