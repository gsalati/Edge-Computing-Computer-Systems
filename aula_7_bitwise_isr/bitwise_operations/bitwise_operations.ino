void exemploAnd(void);
void exemploOr(void);
void exemploXor(void);
void exemploNot(void);
void exemploLeftShift(void);
void exemploRightShift(void);

void printPrettyBin(uint8_t val, uint8_t leadingZeros);

void setup() {
 Serial.begin(9600);
 Serial.println("\n");
 Serial.println("--------------------------------------------");
}


void loop() {

    Serial.println("Operação 2&6: ");
    exemploAnd();
    Serial.println("\n--------------------------------------------\n");

    Serial.println("Operação 2|6: ");
    exemploOr();
    Serial.println("\n--------------------------------------------\n");

    Serial.println("Operação ~2: ");
    exemploNot();
    Serial.println("\n--------------------------------------------\n");

    Serial.println("Operação 2^6: ");
    exemploXor();
    Serial.println("\n--------------------------------------------\n");

    Serial.println("Operação 2 << 1: ");
    exemploLeftShift();
    Serial.println("\n--------------------------------------------\n");

    Serial.println("Operação 2 >> 1: ");
    exemploRightShift();
    Serial.println("\n--------------------------------------------\n");

    while(true);
}

void exemploAnd(void)
{
    uint8_t A = 2;
    uint8_t B = 0b0110;
    uint8_t y;

    y = A&B;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 4);
}

void exemploOr(void)
{
    uint8_t A = 2;
    uint8_t B = 0b0110;
    uint8_t y;

    y = A|B;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 4);
}

void exemploNot(void)
{
    uint8_t A = 2;
    uint8_t y;

    y = ~A;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 8);
}

void exemploXor(void)
{
    uint8_t A = 2;
    uint8_t B = 0b0110;
    uint8_t y;

    y = A^B;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 4);
}

void exemploLeftShift(void){
    uint8_t A = 2;
    uint8_t y;

    y = A << 1;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 4);
}

void exemploRightShift(void){
    uint8_t A = 2;
    uint8_t y;

    y = A >> 1;

    Serial.print("Resultado em decimal: ");
    Serial.println(y);
    Serial.print("Resultado em binario: ");
    printPrettyBin(y, 4);
}



void printPrettyBin(uint8_t val, uint8_t leadingZeros)
{
    for (int i = leadingZeros-1; i >= 0; i--) {
        Serial.print((val >> i) & 1);
    }

}
typedef char uint_8;

uint_8 x, n;

void padroes(void)
{
    /*
    * Verifica se o n-ésimo bit está ligado
    */
    if (x & (1 << n)) {
   
    }


    /*
    * Seta como 1 o n-ésimo bit
    */
    x |= (1 << n);
    
    /*
    * Seta como 0 o n-ésimo bit
    */
    x &= ~(1 << n);
   
   /*
   * Alterna (toggle) o n-ésimo bit
   */
    x ^= (1 << n);
}