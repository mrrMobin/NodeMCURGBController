#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "SSid";
const char *password = "password";

ESP8266WebServer server(80);

int redPin = D1;   
int greenPin = D2;
int bluePin = D3; 

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void handleRoot() {
String content = "<!DOCTYPE html>";
content += "<head>";
content += "    <meta charset=\"UTF-8\">";
content += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
content += "    <style>";
content += "        body {";
content += "            background: #333;";
content += "            display: flex;";
content += "            justify-content: space-around;";
content += "            align-items: center;";
content += "            height: 100vh;";
content += "            margin: 0; /* Remove default body margin */";
content += "        }";
content += "";
content += "        .slider-container {";
content += "            position: relative;";
content += "            max-width: 300px; /* Set a maximum width for each container */";
content += "            height: 50vh; /* Set a percentage of the viewport height */";
content += "        }";
content += "";
content += "        .slider::before {";
content += "            background: linear-gradient(0deg, #525252 0%, #373737 100%);";
content += "            width: 10em;";
content += "            height: 10em;";
content += "            border-radius: 50%;";
content += "            box-shadow: 0px -20px 20px #757575,";
content += "                        0px 20px 35px #111111,";
content += "                        inset 0px 5px 6px #979797,";
content += "                        inset 0px -5px 6px #242424;";
content += "        }";
content += "";
content += "        .slider::before, .knob {";
content += "            width: 10em;";
content += "            height: 10em;";
content += "            position: relative;";
content += "        }";
content += "";
content += "        .knob::before, .knob::after, .slider::before {";
content += "            content: \"\";";
content += "            position: absolute;";
content += "            border-radius: 50%;";
content += "        }";
content += "";
content += "        .knob::before {";
content += "            top: 15px;";
content += "            left: 50%;";
content += "            transform: translate(-50%);";
content += "            width: 10px;";
content += "            height: 10px;";
content += "            background: #fff;";
content += "        }";
content += "";
content += "        .knob::after {";
content += "            top: 50%;";
content += "            left: 50%;";
content += "            transform: translate(-50%, -50%);";
content += "            border: 3px solid #fff;";
content += "            width: 130%;";
content += "            height: 130%;";
content += "        }";
content += "";
content += "        .red::before {";
content += "            box-shadow: 0px 0px 10px #fc160a;";
content += "        }";
content += "";
content += "        .red::after {";
content += "            box-shadow: 0px 0px 10px #eb4634,";
content += "                        inset 0px 0px 10px #eb4634;";
content += "        }";
content += "";
content += "        .blue::before {";
content += "            box-shadow: 0px 0px 10px #346beb;";
content += "        }";
content += "";
content += "        .blue::after {";
content += "            box-shadow: 0px 0px 10px #349beb,";
content += "                        inset 0px 0px 10px #349beb;";
content += "        }";
content += "";
content += "        .green::before {";
content += "            box-shadow: 0px 0px 10px #40da03;";
content += "        }";
content += "";
content += "        .green::after {";
content += "            box-shadow: 0px 0px 10px #34eb65,";
content += "                        inset 0px 0px 10px #34eb65;";
content += "        }";
content += "";
content += "        .slider-value {";
content += "            position: absolute;";
content += "            top: 70%;";
content += "            left: 50%;";
content += "            transform: translateX(-50%);";
content += "            color: #fff;";
content += "        }";
content += "";
content += "        @media only screen and (max-width: 600px) {";
content += "            body {";
content += "                flex-direction: column;";
content += "            }";
content += "";
content += "            .slider-container {";
content += "                max-width: 100%; ";
content += "                height: 30vh; ";
content += "            }";
content += "";
content += "            .slider::before,";
content += "            .knob {";
content += "                width: 5em;";
content += "                height: 5em;";
content += "            }";
content += "";
content += "            .knob::before {";
content += "                width: 5px;";
content += "                height: 5px;";
content += "            }";
content += "";
content += "            .knob::after {";
content += "                width: 65%;";
content += "                height: 65%;";
content += "                border-width: 1.5px;";
content += "            }";
content += "        }";
content += "    </style>";
content += "</head>";
content += "<body>";
content += "    <div class=\"slider-container\">";
content += "        <div class=\"slider\" id=\"redSlider\">";
content += "            <div class=\"knob red\"></div>";
content += "        </div>";
content += "    </div>";
content += "    <div class=\"slider-container\">";
content += "        <div class=\"slider\" id=\"greenSlider\">";
content += "            <div class=\"knob green\"></div>";
content += "        </div>";
content += "    </div>";
content += "    <div class=\"slider-container\">";
content += "     <div class=\"slider\" id=\"blueSlider\">";
content += "            <div class=\"knob blue\"></div>";
content += "        </div>";
content += "    </div>";
content += "    <script>";
content += "var red=0;";
content += "var green=0;";
content += "var blue=0;";
content += "function updateSliderValue(sliderId, value) {";
content += "    console.log(value);";
content += "    if (sliderId==\"redSlider\"){";
content += "        red=value;";
content += "    } else if (sliderId==\"greenSlider\"){";
content += "        green=value;";
content += "    } else if (sliderId==\"blueSlider\"){";
content += "        blue=value;";
content += "    }";
content += "    var xhr = new XMLHttpRequest();";
content += "    xhr.open('GET', '/setRGB?red=' + red + '&green=' + green + '&blue=' + blue, true);";
content += "    xhr.send();";
content += "}";
content += "";
content += "        function calculateDegree(e, knob) {";
content += "            const rect = knob.getBoundingClientRect();";
content += "            const x1 = rect.left + rect.width / 2;";
content += "            const y1 = rect.top + rect.height / 2;";
content += "            const x2 = e.clientX;";
content += "            const y2 = e.clientY;";
content += "            const deltaX = x2 - x1;";
content += "            const deltaY = y2 - y1;";
content += "            const rad = Math.atan2(deltaY, deltaX);";
content += "            let deg = rad * (180 / Math.PI);";
content += "            return deg;";
content += "        }";
content += "";
content += "        function addSliderEvents(sliderId) {";
content += "            const knob = document.getElementById(sliderId).querySelector(\".knob\");";
content += "";
content += "            knob.addEventListener(\"pointerdown\", function (e) {";
content += "                e.preventDefault();";
content += "                knob.addEventListener(\"pointermove\", rotate);";
content += "";
content += "                function rotate(e) {";
content += "                    const result = Math.floor(calculateDegree(e, knob) + 90);";
content += "                    document.getElementById(sliderId).style.transform = `rotate(${result}deg)`;";
content += "                    const scaledValue = Math.floor(((result + 360) % 360) / 360 * 255);";
content += "                    updateSliderValue(sliderId, scaledValue);";
content += "                }";
content += "";
content += "                knob.addEventListener(\"pointerup\", function () {";
content += "                    knob.removeEventListener(\"pointermove\", rotate);";
content += "                });";
content += "            });";
content += "        }";
content += "";
content += "        addSliderEvents(\"redSlider\");";
content += "        addSliderEvents(\"greenSlider\");";
content += "        addSliderEvents(\"blueSlider\");";
content += "    </script>";
content += "</body>";
content += "</html>";
  server.send(200, "text/html", content);
}

void handleRGB() {
  String redParam = server.arg("red");
  String greenParam = server.arg("green");
  String blueParam = server.arg("blue");

  redValue = redParam.toInt();
  greenValue = greenParam.toInt();
  blueValue = blueParam.toInt();

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  server.send(200, "text/plain", "RGB values set");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Port: 80");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/setRGB", HTTP_GET, handleRGB);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
