 #include <Wire.h>
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>

#define WIFI_SSID "rede"
#define WIFI_PASSWORD "senha"
const char* host = "ip"; //Mesma rede do esp e pc
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* As credenciais de login */
#define AUTHOR_EMAIL "Email do Transmissor"
#define AUTHOR_PASSWORD "Senha"

/* Email do destinatário */
#define RECIPIENT_EMAIL "Email do Receptor"

/* O objeto de sessão SMTP usado para envio de e-mail */
SMTPSession smtp;

/* Função de retorno de chamada para obter o status de envio de e-mail */
void smtpCallback(SMTP_Status status);

void EnviarEmail();
void EnviarQuedaBt();
void EnviarQuedaAuto();

int Vibration_signal = 18; 
int Sensor_State = 1; 

// MMA8452Q I2C o endereço é 0x1C(28)
#define Addr 0x1C
#define btEnviar 19 //BOTÃO ENVIAR EMAIL
int ledAviso = 13;
void setup()
{

  Serial.begin(115200);
  pinMode(Vibration_signal, INPUT);
  pinMode(btEnviar, INPUT_PULLUP);
  pinMode(ledAviso, OUTPUT);
  
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  
  /* Inicializar a comunicação I2C como MASTER */
  Wire.begin();
  
 
  // Iniciar a transmissão I2C
  Wire.beginTransmission(Addr);
  // Seleciona o registro de controle
  Wire.write(0x2A);
  // Modo de espera
  Wire.write((byte)0x00);
  // Parar a transmissão I2C
  Wire.endTransmission();
 
  // Iniciar a transmissão I2C
  Wire.beginTransmission(Addr);
  // Selecione o registro de controle
  Wire.write(0x2A);
  // Modo ativo
  Wire.write(0x01);
  // Parar a transmissão I2C
  Wire.endTransmission();
 
  // Iniciar a transmissão I2C
  Wire.beginTransmission(Addr);
  // Selecione o registro de controle
  Wire.write(0x0E);
  // Seta o alcance para +/- 2g
  Wire.write((byte)0x00);
  // Parar a transmissão I2C
  Wire.endTransmission();
  delay(300);
}
 
void loop()
{
  unsigned int data[7];
 
  // Solicite 7 bytes de dados
  Wire.requestFrom(Addr, 7);
 
  // Lê 7 bytes de dados
  // staus, xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
  if(Wire.available() == 7) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
  }
 
  // Converte os dados para 12 bits
  int xAccl = ((data[1] * 256) + data[2]) / 16;
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }
 
  int yAccl = ((data[3] * 256) + data[4]) / 16;
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }
 
  int zAccl = ((data[5] * 256) + data[6]) / 16;
  if (zAccl > 2047)
  {
    zAccl -= 4096;
  }
  if ( digitalRead(btEnviar)==0){
    Serial.println("Botão pressionado");
    EnviarEmail();
    EnviarQuedaBt();
    delay(500);
  }
  
  Serial.println("===========================");
  Serial.print("Vibration status: ");
  Sensor_State = digitalRead(Vibration_signal);
  if (Sensor_State == 1) {
    Serial.println("Sensing vibration");
  }
  else {
    Serial.println("No vibration");
  }
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis : ");
  Serial.println(zAccl);
  Serial.println("===========================");
  delay(500);
  

   //DETECÇAO QUEDA 
  if(xAccl >= 1800 && Sensor_State == 1 || yAccl >= 1800 && Sensor_State == 1){
    Serial.println("===========================");
    Serial.println("QUEDA DETECTADA");
    Serial.println("QUEDA DETECTADA");
    Serial.println("QUEDA DETECTADA");
    Serial.println("==========================="); 
    EnviarEmail();
    EnviarQuedaAuto();
    delay(500);   
  }
  if(xAccl >= -1800 && Sensor_State == 1 || yAccl >= -1800 && Sensor_State == 1){
    Serial.println("===========================");
    Serial.println("QUEDA DETECTADA");
    Serial.println("QUEDA DETECTADA");
    Serial.println("QUEDA DETECTADA");
    Serial.println("==========================="); 
    EnviarEmail();
    EnviarQuedaAuto();
    delay(500);   
  }  
  
  }

  void EnviarEmail(){

  smtp.debug(1);

  /* Defina a função de retorno de chamada para obter os resultados de envio */
  smtp.callback(smtpCallback);

  /* Declarar os dados de configuração da sessão */
  ESP_Mail_Session session;

  /* Defina a configuração da sessão */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare a classe da mensagem */
  SMTP_Message message;

  /* Defina os cabeçalhos das mensagens */
  message.sender.name = "ALERTA POSSIVEL QUEDA";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Importante!";
  message.addRecipient("Senai", RECIPIENT_EMAIL);

  /* Manda mensagem HTML */
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>O USUARIO SOLICITA AJUDA</h1><p>- Sent from ESP board</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /* Conecte-se ao servidor com a configuração da sessão */
  if (!smtp.connect(&session))
    return;

  /* Comece a enviar e-mail e feche a sessão */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}
/* Função de retorno de chamada para obter o status de envio de e-mail */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Imprima o resultado do envio */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Obtenha o item de resultado */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
}
void EnviarQuedaBt(){
   Serial.print("connecting to ");
    Serial.println(host);

    // Use a classe WiFiClient para criar conexões TCP
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // Agora criamos um URI para a solicitação
    String url = "/NodeMCUProjeto/salvar.php?";
      url += "Esp32=";
      url += "O%20Usuario%20solicitou%20ajuda";


    Serial.print("Requesting URL: ");
    Serial.println(url);

    // Isso irá enviar a solicitação para o servidor
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Leia todas as linhas da resposta do servidor e imprima-as em Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        

         
         if(line.indexOf("salvo_com_sucesso") != -1 ){
           Serial.println();
           Serial.println("Salvo com sucesso");
         } else if(line.indexOf("erro_ao_salvar") != -1 ){
           Serial.println();
           Serial.println("Erro ao salvar");
         }
        
    }

    Serial.println();
    Serial.println("closing connection");
    delay(10000);
  }
  void EnviarQuedaAuto(){
   Serial.print("connecting to ");
    Serial.println(host);

    
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    
    String url = "/NodeMCUProjeto/salvar.php?";
      url += "Esp32=";
      url += "Queda%20Detectada!";


    Serial.print("Requesting URL: ");
    Serial.println(url);

    
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    
    while(client.available()) {
        String line = client.readStringUntil('\r');
       

         
         if(line.indexOf("salvo_com_sucesso") != -1 ){
           Serial.println();
           Serial.println("Salvo com sucesso");
         } else if(line.indexOf("erro_ao_salvar") != -1 ){
           Serial.println();
           Serial.println("Erro ao salvar");
         }
        
    }

    Serial.println();
    Serial.println("closing connection");
    delay(5000);
  }
