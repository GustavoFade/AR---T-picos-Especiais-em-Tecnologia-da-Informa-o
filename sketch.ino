#define ECHO_PIN 2 
#define TRIG_PIN 3
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
float obterDistanciaEmMetros() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int duration = pulseIn(ECHO_PIN, HIGH);
  float distanciaCm = duration * 0.034 / 2;
  float distanciaMetros = distanciaCm/100;
  return distanciaMetros;
}
void delayDeAcordoSeEstaAtivo(bool temAlguem){
  if(temAlguem){
    Serial.println(" Próxima verificação em 5 minutos !");
    delay(300000);
  } else {
    delay(100);
  }
}
void loop() {
  float distanciaEmMetros = obterDistanciaEmMetros();
  int METROS_PARA_ACENDER_LUZ = 2;

  bool chegouAlguem = distanciaEmMetros < METROS_PARA_ACENDER_LUZ;
  digitalWrite(LED_BUILTIN, chegouAlguem);

  String mensagemSeEstaLigado = chegouAlguem == true ? "sim ! " : "não ! ";
  Serial.print("Lâmpada está ligada: " + mensagemSeEstaLigado);
  Serial.print(obterDistanciaEmMetros());
  Serial.println(" metros !");

  delayDeAcordoSeEstaAtivo(chegouAlguem);
}
