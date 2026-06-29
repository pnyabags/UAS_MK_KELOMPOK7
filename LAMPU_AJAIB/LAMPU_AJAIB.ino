#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "pai";
const char* password = "123456789";

#define RELAY_PIN 27

WebServer server(80);

bool lampState = false;

//===========================
// Halaman Web
//===========================

void handleRoot()
{
  String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta charset="UTF-8">

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Lampu Ajaib</title>

<style>

body{

font-family:Arial;
background:#f5f5f5;
text-align:center;
margin-top:60px;

}

.card{

background:white;
width:320px;
margin:auto;
padding:30px;
border-radius:15px;
box-shadow:0 0 15px rgba(0,0,0,.2);

}

button{

width:120px;
height:45px;
font-size:18px;
margin:10px;
border:none;
border-radius:10px;
cursor:pointer;

}

.on{

background:#2ecc71;
color:white;

}

.off{

background:#e74c3c;
color:white;

}

.status{

font-size:22px;
margin:20px;

}

</style>

</head>

<body>

<div class="card">

<h2>Lampu Ajaib</h2>
)rawliteral";

  html += "<div class='status'>Status : ";

  if (lampState)
    html += "<b style='color:green;'>ON</b>";
  else
    html += "<b style='color:red;'>OFF</b>";

  html += "</div>";

  html += R"rawliteral(

<a href="/on">
<button class="on">ON</button>
</a>

<a href="/off">
<button class="off">OFF</button>
</a>

</div>

</body>
</html>

)rawliteral";

  server.send(200, "text/html", html);
}

//===========================

void lampON()
{
  lampState = true;

  digitalWrite(RELAY_PIN, LOW);      // Relay Active LOW

  server.sendHeader("Location", "/");
  server.send(303);
}

void lampOFF()
{
  lampState = false;

  digitalWrite(RELAY_PIN, HIGH);

  server.sendHeader("Location", "/");
  server.send(303);
}

//===========================

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);

  WiFi.begin(ssid,password);

  Serial.print("Connecting");

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  Serial.print("IP Address : ");

  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);

  server.on("/on",lampON);

  server.on("/off",lampOFF);

  server.begin();

  Serial.println("Web Server Started");
}

void loop()
{
  server.handleClient();
}