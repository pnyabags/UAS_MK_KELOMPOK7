#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
WebServer server(80);

// WIFI
const char* ssid = "pai";
const char* password = "123456789";

#define RELAY_PIN 27

bool lampState = false;
bool autoMode = false;

String lampStatus()
{
    if(lampState)
        return "ON";

    return "OFF";
}

String modeStatus()
{
    if(autoMode)
        return "AUTO";

    return "MANUAL";
}

String relayColor()
{
    if(lampState)
        return "#2ecc71";

    return "#e74c3c";
}

String getTime()
{
    DateTime now = rtc.now();

    char waktu[25];

    sprintf(
        waktu,
        "%02d/%02d/%04d %02d:%02d:%02d",
        now.day(),
        now.month(),
        now.year(),
        now.hour(),
        now.minute(),
        now.second()
    );

    return String(waktu);
}

void handleRoot()
{

String html = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta charset="UTF-8">

<meta name="viewport"
content="width=device-width, initial-scale=1">

<meta http-equiv="refresh" content="1">

<title>Lampu Ajaib</title>

<style>

*{

margin:0;
padding:0;
box-sizing:border-box;

}

body{

background:#ecf0f1;
font-family:Arial;
padding:30px;

}

.container{

max-width:420px;
margin:auto;

}

.card{

background:white;

border-radius:20px;

padding:25px;

box-shadow:0 5px 20px rgba(0,0,0,.2);

}

h1{

text-align:center;
color:#2c3e50;

margin-bottom:8px;

}

.subtitle{

text-align:center;

color:gray;

margin-bottom:20px;

}

.info{

background:#f8f9fa;

padding:15px;

border-radius:12px;

margin-top:12px;

}

.label{

font-weight:bold;

color:#555;

}

.value{

margin-top:5px;

font-size:22px;

font-weight:bold;

}

.status{

font-size:28px;

font-weight:bold;

margin-top:5px;

}

.button{

width:100%;

padding:15px;

font-size:18px;

margin-top:12px;

border:none;

border-radius:12px;

cursor:pointer;

color:white;

}

.green{

background:#2ecc71;

}

.red{

background:#e74c3c;

}

.blue{

background:#3498db;

}

.orange{

background:#f39c12;

}

.footer{

margin-top:20px;

text-align:center;

font-size:12px;

color:gray;

}

</style>

</head>

<body>

<div class="container">

<div class="card">

<h1>Lampu Ajaib</h1>

<p class="subtitle">

Smart Lighting System

</p>

<div class="info">

<div class="label">

Tanggal & Jam

</div>

<div class="value">
)rawliteral";

html += getTime();

html += R"rawliteral(
</div>

</div>

<div class="info">

<div class="label">

Status Lampu

</div>
<div class="status" style="color:
)rawliteral";

html += relayColor();

html += R"rawliteral(
">
)rawliteral";

html += lampStatus();

html += R"rawliteral(
</div>

</div>

<div class="info">

<div class="label">

Mode

</div>

<div class="value">
)rawliteral";

html += modeStatus();

html += R"rawliteral(
</div>

</div>

<div class="info">

<div class="label">

WiFi

</div>

<div class="value">

Connected

</div>

</div>

<div class="info">

<div class="label">

IP Address

</div>

<div class="value">
)rawliteral";

html += WiFi.localIP().toString();

html += R"rawliteral(
</div>

</div>

<a href="/on">

<button class="button green">

HIDUPKAN

</button>

</a>

<a href="/off">

<button class="button red">

MATIKAN

</button>

</a>

<a href="/auto">

<button class="button blue">

MODE AUTO

</button>

</a>

<a href="/manual">

<button class="button orange">

MODE MANUAL

</button>

</a>

<div class="footer">

Lampu Ajaib v1.0<br>

ESP32 Web Server + RTC DS3231

</div>

</div>

</div>

</body>

</html>

)rawliteral";

server.send(200,"text/html",html);

}

void lampON()
{
    lampState = true;
    autoMode = false;              // Keluar dari mode otomatis

    digitalWrite(RELAY_PIN, LOW);  // Relay Active LOW

    server.sendHeader("Location","/");
    server.send(303);
}

void lampOFF()
{
    lampState = false;
    autoMode = false;           

    digitalWrite(RELAY_PIN, HIGH);

    server.sendHeader("Location","/");
    server.send(303);
}

void autoON()
{
    autoMode = true;

    server.sendHeader("Location","/");
    server.send(303);
}

void manualON()
{
    autoMode = false;

    server.sendHeader("Location","/");
    server.send(303);
}
void setup()
{

    Serial.begin(115200);

    pinMode(RELAY_PIN,OUTPUT);

    // Relay OFF saat boot
    digitalWrite(RELAY_PIN,HIGH);

    // RTC
    Wire.begin();

    if(!rtc.begin())
    {
        Serial.println("RTC DS3231 Tidak Ditemukan!");

        while(1);
    }

    if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }


    // WIFI
    Serial.println();

    Serial.print("Connecting ");

    Serial.println(ssid);

    WiFi.begin(ssid,password);

    while(WiFi.status()!=WL_CONNECTED)
    {
        delay(500);

        Serial.print(".");
    }

    Serial.println();

    Serial.println("WiFi Connected");

    Serial.print("IP : ");

    Serial.println(WiFi.localIP());

    // ROUTING
    server.on("/",handleRoot);

    server.on("/on",lampON);

    server.on("/off",lampOFF);

    server.on("/auto",autoON);

    server.on("/manual",manualON);

    server.begin();

    Serial.println("Web Server Started");

}

// LOOP
void loop()
{
    // Handle Web Client
    server.handleClient();

    // MODE OTOMATIS
    if(autoMode)
    {
        DateTime now = rtc.now();

        /*
        18:00 -> Lampu ON
        06:00 -> Lampu OFF
        */
        if(now.hour() >= 18 || now.hour() < 6)
        {
            if(!lampState)
            {
                lampState = true;
                digitalWrite(RELAY_PIN, LOW);

                Serial.println("AUTO : Lampu ON");
            }
        }
        else
        {
            if(lampState)
            {
                lampState = false;
                digitalWrite(RELAY_PIN, HIGH);

                Serial.println("AUTO : Lampu OFF");
            }
        }
    }

    delay(100);
}