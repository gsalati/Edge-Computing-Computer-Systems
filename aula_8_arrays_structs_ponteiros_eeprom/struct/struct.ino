typedef struct
{
    char nome[20];
    uint8_t idade;
    float nota;
} aluno_t;

void setup() {
  Serial.begin(9600);
  Serial.println("\n\n\n--------------------------------");
}

void loop() {

  aluno_t aluno[2];

  aluno_t alunoMaiorNota;

  strcpy(aluno[0].nome, "Guilherme");
  aluno[0].idade = 31;
  aluno[0].nota = 9;
  
  strcpy(aluno[1].nome, "Maria Antonia");
  aluno[1].idade = 28;
  aluno[1].nota = 10;

  if(aluno[1].nota > aluno[0].nota)
  {
    memcpy(&alunoMaiorNota, &aluno[1], sizeof(aluno_t));
  }
  else
  {
    memcpy(&alunoMaiorNota, &aluno[0], sizeof(aluno_t));
  }

  Serial.print(alunoMaiorNota.nome);
  Serial.println(" é o aluno com maior nota");

  while(1){}
}
