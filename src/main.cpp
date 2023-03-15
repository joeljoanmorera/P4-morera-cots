#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "MiFibra-F392"; // Enter your SSID here
const char* password = "5QUisHGE"; //Enter your Password here

WebServer server(80);// Object of WebServer(HTTP port, 80 is default)

void handle_root();

void setup() 
{
    Serial.begin(115200);
    Serial.print("Try Connecting to ");
    Serial.println(ssid);
    // Connect to your wi-fi modem
    WiFi.begin(ssid, password);
    // Check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP()); //Show ESP32 IP on serial
    server.on("/", handle_root);
    server.begin();
    Serial.println("HTTP server started");
    delay(100);
}

void loop() 
{
    server.handleClient();
}

// HTML & CSS contents which display on web server
char* HTML = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Generación de una página web con conexión STA</title>"
"<meta http-equiv='Content-type' content='text/html;charset=UTF-8'>"

"<style>"

"body {"
"	font-family: var(--vscode-markdown-font-family, -apple-system, BlinkMacSystemFont, 'Segoe WPC', 'Segoe UI', 'Ubuntu', 'Droid Sans', sans-serif);"
"	font-size: var(--vscode-markdown-font-size, 14px);"
"	padding: 0 26px;"
"	line-height: var(--vscode-markdown-line-height, 22px);"
"	word-wrap: break-word;"
"}"

"#code-csp-warning {"
"	position: fixed;"
"	top: 0;"
"	right: 0;"
"	color: white;"
"	margin: 16px;"
"	text-align: center;"
"	font-size: 12px;"
"	font-family: sans-serif;"
"	background-color:#444444;"
"	cursor: pointer;"
"	padding: 6px;"
"	box-shadow: 1px 1px 1px rgba(0,0,0,.25);"
"}"

"#code-csp-warning:hover {"
"	text-decoration: none;"
"	background-color:#007acc;"
"	box-shadow: 2px 2px 2px rgba(0,0,0,.25);"
"}"

"body.scrollBeyondLastLine {"
"	margin-bottom: calc(100vh - 22px);"
"}"

"body.showEditorSelection .code-line {"
"	position: relative;"
"}"

"body.showEditorSelection .code-active-line:before,"
"body.showEditorSelection .code-line:hover:before {"
"	content: '';"
"	display: block;"
"	position: absolute;"
"	top: 0;"
"	left: -12px;"
"	height: 100%;"
"}"

"body.showEditorSelection li.code-active-line:before,"
"body.showEditorSelection li.code-line:hover:before {"
"	left: -30px;"
"}"

".vscode-light.showEditorSelection .code-active-line:before {"
"	border-left: 3px solid rgba(0, 0, 0, 0.15);"
"}"

".vscode-light.showEditorSelection .code-line:hover:before {"
"	border-left: 3px solid rgba(0, 0, 0, 0.40);"
"}"

".vscode-light.showEditorSelection .code-line .code-line:hover:before {"
"	border-left: none;"
"}"

".vscode-dark.showEditorSelection .code-active-line:before {"
"	border-left: 3px solid rgba(255, 255, 255, 0.4);"
"}"

".vscode-dark.showEditorSelection .code-line:hover:before {"
"	border-left: 3px solid rgba(255, 255, 255, 0.60);"
"}"

".vscode-dark.showEditorSelection .code-line .code-line:hover:before {"
"	border-left: none;"
"}"

".vscode-high-contrast.showEditorSelection .code-active-line:before {"
"	border-left: 3px solid rgba(255, 160, 0, 0.7);"
"}"

".vscode-high-contrast.showEditorSelection .code-line:hover:before {"
"	border-left: 3px solid rgba(255, 160, 0, 1);"
"}"

".vscode-high-contrast.showEditorSelection .code-line .code-line:hover:before {"
"	border-left: none;"
"}"

"img {"
"	max-width: 100%;"
"	max-height: 100%;"
"}"

"a {"
"	text-decoration: none;"
"}"

"a:hover {"
"	text-decoration: underline;"
"}"

"a:focus,"
"input:focus,"
"select:focus,"
"textarea:focus {"
"	outline: 1px solid -webkit-focus-ring-color;"
"	outline-offset: -1px;"
"}"

"hr {"
"	border: 0;"
"	height: 2px;"
"	border-bottom: 2px solid;"
"}"

"h1 {"
"	padding-bottom: 0.3em;"
"	line-height: 1.2;"
"	border-bottom-width: 1px;"
"	border-bottom-style: solid;"
"}"

"h1, h2, h3 {"
"	font-weight: normal;"
"}"

"table {"
"	border-collapse: collapse;"
"}"

"table > thead > tr > th {"
"	text-align: left;"
"	border-bottom: 1px solid;"
"}"

"table > thead > tr > th,"
"table > thead > tr > td,"
"table > tbody > tr > th,"
"table > tbody > tr > td {"
"	padding: 5px 10px;"
"}"

"table > tbody > tr + tr > td {"
"	border-top: 1px solid;"
"}"

"blockquote {"
"	margin: 0 7px 0 5px;"
"	padding: 0 16px 0 10px;"
"	border-left-width: 5px;"
"	border-left-style: solid;"
"}"

"code {"
"	font-family: Menlo, Monaco, Consolas, 'Droid Sans Mono', 'Courier New', monospace, 'Droid Sans Fallback';"
"	font-size: 1em;"
"	line-height: 1.357em;"
"}"

"body.wordWrap pre {"
"	white-space: pre-wrap;"
"}"

"pre:not(.hljs),"
"pre.hljs code > div {"
"	padding: 16px;"
"	border-radius: 3px;"
"	overflow: auto;"
"}"

"pre code {"
"	color: var(--vscode-editor-foreground);"
"	tab-size: 4;"
"}"

".vscode-light pre {"
"	background-color: rgba(220, 220, 220, 0.4);"
"}"

".vscode-dark pre {"
"	background-color: rgba(10, 10, 10, 0.4);"
"}"

".vscode-high-contrast pre {"
"	background-color: rgb(0, 0, 0);"
"}"

".vscode-high-contrast h1 {"
"	border-color: rgb(0, 0, 0);"
"}"

".vscode-light table > thead > tr > th {"
"	border-color: rgba(0, 0, 0, 0.69);"
"}"

".vscode-dark table > thead > tr > th {"
"	border-color: rgba(255, 255, 255, 0.69);"
"}"

".vscode-light h1,"
".vscode-light hr,"
".vscode-light table > tbody > tr + tr > td {"
"	border-color: rgba(0, 0, 0, 0.18);"
"}"

".vscode-dark h1,"
".vscode-dark hr,"
".vscode-dark table > tbody > tr + tr > td {"
"	border-color: rgba(255, 255, 255, 0.18);"
"}"

"</style>"

"<style>"
".hljs-comment,"
".hljs-quote {"
"	color: #8e908c;"
"}"

"/* Tomorrow Red */"
".hljs-variable,"
".hljs-template-variable,"
".hljs-tag,"
".hljs-name,"
".hljs-selector-id,"
".hljs-selector-class,"
".hljs-regexp,"
".hljs-deletion {"
"	color: #c82829;"
"}"

".hljs-number,"
".hljs-built_in,"
".hljs-builtin-name,"
".hljs-literal,"
".hljs-type,"
".hljs-params,"
".hljs-meta,"
".hljs-link {"
"	color: #f5871f;"
"}"

".hljs-attribute {"
"	color: #eab700;"
"}"

".hljs-string,"
".hljs-symbol,"
".hljs-bullet,"
".hljs-addition {"
"	color: #718c00;"
"}"

".hljs-title,"
".hljs-section {"
"	color: #4271ae;"
"}"

".hljs-keyword,"
".hljs-selector-tag {"
"	color: #8959a8;"
"}"

".hljs {"
"	display: block;"
"	overflow-x: auto;"
"	color: #4d4d4c;"
"	padding: 0.5em;"
"}"

".hljs-emphasis {"
"	font-style: italic;"
"}"

".hljs-strong {"
"	font-weight: bold;"
"}"
"</style>"

"<style>"

" body {"
"	font-family: -apple-system, BlinkMacSystemFont, 'Segoe WPC', 'Segoe UI', 'Ubuntu', 'Droid Sans', sans-serif, 'Meiryo';"
"	padding: 0 12px;"
"}"

"pre {"
"	background-color: #f8f8f8;"
"	border: 1px solid #cccccc;"
"	border-radius: 3px;"
"	overflow-x: auto;"
"	white-space: pre-wrap;"
"	overflow-wrap: break-word;"
"}"

"pre:not(.hljs) {"
"	padding: 23px;"
"	line-height: 19px;"
"}"

"blockquote {"
"	background: rgba(127, 127, 127, 0.1);"
"	border-color: rgba(0, 122, 204, 0.5);"
"}"

".emoji {"
"	height: 1.4em;"
"}"

"code {"
"	font-size: 14px;"
"	line-height: 19px;"
"}"

":not(pre):not(.hljs) > code {"
"	color: #C9AE75; "
"	font-size: inherit;"
"}"

".page {"
"	page-break-after: always;"
"}"

"</style>"

"<script src='https://unpkg.com/mermaid/dist/mermaid.min.js'></script>"
"</head>"
"<body>"
"  <script>"
"    mermaid.initialize({"
"      startOnLoad: true,"
"      theme: document.body.classList.contains('vscode-dark') || document.body.classList.contains('vscode-high-contrast')"
"          ? 'dark'"
"          : 'default'"
"    });"
"  </script>"
"<h1 id='practica-4-gerard-cots-y-joel-j-morera'>Práctica 4. Gerard Cots y Joel J. Morera</h1>"
"<h2 id='generacion-de-una-pagina-web'>Generación de una página web</h2>"
"<h3 id='funcionamento'><strong>Funcionamento</strong></h3>"
"<p>El programa en cuestión realiza la tarea"
"si sigo el texto aqui deberia salir no?"
"Total que esto tambien deberia salir</p>"
"<h3 id='codigo-del-programa'><strong>Código del programa</strong>  </h3>"
"<pre class='hljs'><code><div><span class='hljs-meta'> #<span class='hljs-meta-keyword'>include</span> <span class='hljs-meta-string'>&lt;WiFi.h&gt;</span></span> \n "
"<span class='hljs-meta'>#<span class='hljs-meta-keyword'>include</span> <span class='hljs-meta-string'>&lt;WebServer.h&gt;</span></span> \n \n "

"<span class='hljs-comment'>// SSID &amp; Password </span> \n "
"<span class='hljs-keyword'>const</span> <span class='hljs-keyword'>char</span>* ssid = <span class='hljs-string'>'*****'</span>; <span class='hljs-comment'>// Enter your SSID here \n </span>"
"<span class='hljs-keyword'>const</span> <span class='hljs-keyword'>char</span>* password = <span class='hljs-string'>'*****'</span>; <span class='hljs-comment'>//Enter your Password here \n </span>"

"<span class='hljs-function'>WebServer <span class='hljs-title'>server</span><span class='hljs-params'>(<span class='hljs-number'>80</span>)</span></span>;<span class='hljs-comment'>// Object of WebServer(HTTP port, 80 is default) \n \n </span>"

"<span class='hljs-function'><span class='hljs-keyword'>void</span> <span class='hljs-title'>setup</span><span class='hljs-params'>() \n</span> "
"</span>{\n "
"    Serial.begin(<span class='hljs-number'>115200</span>); \n "
"    Serial.print(<span class='hljs-string'>'Try Connecting to '</span>); \n "
"    Serial.println(ssid);  \n"
"    <span class='hljs-comment'>// Connect to your wi-fi modem</span> \n "
"    WiFi.begin(ssid, password); \n "
"    <span class='hljs-comment'>// Check wi-fi is connected to wi-fi network</span> \n "
"    <span class='hljs-keyword'>while</span> (WiFi.status() != WL_CONNECTED) \n "
"    {\n"
"        delay(<span class='hljs-number'>1000</span>); \n "
"        Serial.print(<span class='hljs-string'>'.'</span>); \n "
"    } \n\n "
"    Serial.println(<span class='hljs-string'>''</span>); \n "
"    Serial.println(<span class='hljs-string'>'WiFi connected successfully'</span>); \n "
"    Serial.print(<span class='hljs-string'>'Got IP: '</span>); \n "
"    Serial.println(WiFi.localIP()); <span class='hljs-comment'>//Show ESP32 IP on serial</span> \n "
"    server.on(<span class='hljs-string'>'/'</span>, handle_root); \n "
"    server.begin(); \n "
"    Serial.println(<span class='hljs-string'>'HTTP server started'</span>); \n "
"    delay(<span class='hljs-number'>100</span>); \n "
"} \n\n "

"<span class='hljs-function'><span class='hljs-keyword'>void</span> <span class='hljs-title'>loop</span><span class='hljs-params'>()</span> \n "
"</span>{ \n "
"    server.handleClient(); \n "
"} \n\n "

"<span class='hljs-comment'>// HTML &amp; CSS contents which display on web server</span> \n "
"String HTML = <span class='hljs-string'>' &lt;!DOCTYPE html&gt;\n "
"                &lt;html&gt;\n "
"                    &lt;body&gt;\n "
"                        &lt;h1&gt;My Primera Pagina con ESP32 - Station Mode &amp;#128522;&lt;/h1&gt;\n "
"                    &lt;/body&gt;\n "
"                &lt;/html&gt;'</span>; \n\n "

"<span class='hljs-comment'>// Handle root url (/)</span> \n "
"<span class='hljs-function'><span class='hljs-keyword'>void</span> <span class='hljs-title'>handle_root</span><span class='hljs-params'>()</span> \n "
"</span>{ \n "
"    server.send(<span class='hljs-number'>200</span>, <span class='hljs-string'>'text/html'</span>, HTML); \n "
"}"
"</div></code></pre>"
"<h3 id='salida-por-terminal'><strong>Salida por terminal</strong></h3>"
"<pre class='hljs'><code><div>Try Connecting to "
"MiFibra-XXXX"
"... \n"
"WiFi connected successfully \n"
"Got IP: 192.168.1.145\n"
"HTTP server started"
"</div></code></pre>"
"<h6 id='visualizaci%C3%B3n-de-la-connexi%C3%B3n-a-la-p%C3%A1gina-web'><strong>Visualización de la connexión a la página web</strong></h6>"
"<p><img src='https://github.com/joeljoanmorea/P4-morera-cots/blob/master/images/web_STA.png' alt='&quot;Página web&quot;'></p>"
"<h3 id='diagrama-de-flujo'><strong>Diagrama de flujo</strong></h3>"

"</body>"
"</html>";

// Handle root url (/)"
void handle_root()
{
    server.send(200, "text/html", HTML);
}