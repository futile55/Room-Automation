#include <ESP8266WiFi.h>

const char* ssid = "saurabh";
const char* password = "1234567890";
//int bulbstate = 0;
int ledPin = 13; // GPIO13
int tem=0;
int hu=0;
WiFiServer server(80);
int val=0;
int value1 = LOW, value2 = LOW, value3 = LOW, value4 = LOW;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("...");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {


  //if(Serial.available())
  //{
 //   int local = Serial.read();
   // if(val==0){ tem=local; /*Serial.print("tem=");Serial.println(tem);*/ val++;}
   //else { hu=local;/* Serial.print("humiditiy=");Serial.println(hu);*/ val=0;}
    
 //   }
    // Check if a client has connected
      WiFiClient client = server.available();
    if (!client) {
      return;
    }

    // Wait until the client sends some data
    // Serial.println("new client");

    while (!client.available()) {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    client.flush();

    // Match the request
    if (request.indexOf("/LED=1ON") != -1)  {
      Serial.println('a');
      value1 = HIGH;
    }
    if (request.indexOf("/LED=1OFF") != -1) {
      Serial.println('A');
      value1 = LOW;
    }

    if (request.indexOf("/LED=2ON") != -1)  {
      Serial.println('b');
      value2 = HIGH;
    }
    if (request.indexOf("/LED=2OFF") != -1)  {
      Serial.println('B');
      value2 = LOW;
    }

    if (request.indexOf("/FAN-ON") != -1)  {
      Serial.println('c');
      value3 = HIGH;
    }
    if (request.indexOf("/FAN-OFF") != -1)  {
      Serial.println('C');
      value3 = LOW;
    }

/*
    if (request.indexOf("/LED=4ON") != -1 && bulbstate < 3)  {
      bulbstate++;
      Serial.println(bulbstate);
    }
    if (request.indexOf("/LED=4OFF") != -1 && bulbstate > 0) {
      bulbstate--;
      Serial.println(bulbstate);
    }
 */

    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
   // client.println("Refresh: 15");  // refresh the page automatically every 5 sec
    client.println();
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");  
  client.println("<head>");
  client.println("<title>Room Automation System</title>");
  client.println("<style type='text/css'>");
  client.println("body{");
    client.println("margin: 0;background-color: yellow;}");
  client.println("header{");
    client.println("border:1px black solid;");
    client.println("padding: 20px;}");
  client.println("footer{");
    client.println("height: 100px;");
    client.println("border:1px black solid;}");
  client.println("section{");
    client.println("overflow: auto;}");
  client.println("div{");
  client.println("background-color: yellow;}");
  client.println("#mainmenu2{}");
    /*border:1px solid green;*/
  client.println("#mainmenu2 li{");
    client.println("display: inline;}");
  client.println("#mainmenu li a{");
    client.println("margin: 30px;");

    client.println("padding: 10px 10px;");

    client.println("text-decoration: none;}");
  client.println("#mainmenu li a:hover{");
    client.println("color: white;");
    client.println("background-color: black;");
    client.println("cursor: pointer;}");
  client.println("#leftContentArea{float: left;}");
  client.println("#rightContentArea{float: right;  }");
client.println("</style>");
client.println("</head>");
client.println("<body>");
client.println("<div>");
  client.println("<header>");
 client.println(" <table border='0' width='100%'>");
 client.println(" <tr>");
      client.println("<td><img src='nw.jpg' height='50'></td>");
      client.println("<td><h1>Room Automation System</h1></td>");
    client.println("</tr><td><h2>Controls</h2></td>");
    client.println("</table>");
  
 client.println(" <ul id='mainmenu2'>");
    client.println("<li><a href=\"/LED=1ON\"\"><button>Turn 1 On </button></a></li>");
    client.println(" <li><a href=\"/LED=1OFF\"\"><button>Turn 1 Off </button></a><br /></li>");
    client.println("<li><a href=\"/LED=2ON\"\"><button>Turn 2 On</button></a></li>");
    client.println("<li><a href=\"/LED=2OFF\"\"><button>Turn 2 Off </button></a><br /></li>");
    client.println("<li><a href=\"/FAN-ON\"\"><button>Turn 3 On</button></a></li>");
    client.println("<li><a href=\"/FAN-OFF\"\"><button>Turn 3 Off </button></a><br /></li>");
    client.println(" </ul> ");
    client.println("</header>");
    client.println(" <section>");
    client.println("<div id='leftContentArea'>");
    client.println("<h2>Activities</h2>");
    client.println("<h3>Now:</h3>");

   if (value1 == HIGH) client.println("1 On ");
    else client.print("1 Off ");
    if (value2 == HIGH) client.println("2 On ");
    else client.print("2 Off ");
    if (value3 == HIGH) client.println("3 On ");
    else client.print("3 Off ");
    client.println("</div>");
    client.println("<div id='rightContentArea'>");
    client.println("<img src='images.jpg'>");
    client.println("</div>");
    client.println("</section>");
 // client.println("<footer>");
 // client.println("  footer part");
  //client.println("</footer>");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    delay(1);
}
