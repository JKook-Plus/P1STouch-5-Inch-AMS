#ifndef _XLCD_WEBSERVER
#define _XLCD_WEBSERVER

#include <Arduino.h>
#include <ArduinoJson.h>
#include "ESPmDNS.h"
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SD.h"
#include "xtouch/cloud.hpp"
#include "xtouch/mqtt.h"

AsyncWebServer server(80);

unsigned char h2int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return ((unsigned char)c - '0');
    }
    if (c >= 'a' && c <= 'f')
    {
        return ((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <= 'F')
    {
        return ((unsigned char)c - 'A' + 10);
    }
    return (0);
}

String urldecode(String str)
{

    String encodedString = "";
    char c;
    char code0;
    char code1;
    for (int i = 0; i < str.length(); i++)
    {
        c = str.charAt(i);
        if (c == '+')
        {
            encodedString += ' ';
        }
        else if (c == '%')
        {
            i++;
            code0 = str.charAt(i);
            i++;
            code1 = str.charAt(i);
            c = (h2int(code0) << 4) | h2int(code1);
            encodedString += c;
        }
        else
        {

            encodedString += c;
        }

        yield();
    }

    return encodedString;
}
void xtouch_webserver_end()
{
    server.reset();
    server.end();
    MDNS.end();
}
void sendError(AsyncWebServerRequest *request, String desc)
{

    String action = request->arg("action");
    String path = request->arg("path");

    DynamicJsonDocument jsonDoc(256);
    jsonDoc["error"] = action.c_str();
    jsonDoc["desc"] = desc.c_str();
    jsonDoc["path"] = path.c_str();
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    request->send(500, "application/json", jsonString);
}

void xtouch_webserver_begin()
{
    Serial.println("Starting webserver...");
    if (!MDNS.begin("xtouch"))
    {
        Serial.println("Error starting mDNS");
        return;
    }

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance()
        .addHeader("Access-Control-Allow-Methods", "DELETE, POST, GET, OPTIONS");
    DefaultHeaders::Instance()
        .addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");

    // Handle form submission
    server.on(
        "/provision",
        HTTP_POST,
        [](AsyncWebServerRequest *request) {},
        NULL,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
        {
            StaticJsonDocument<2048> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, data, len);
            serializeJsonPretty(jsonDoc, Serial);

            xtouch_filesystem_writeJson(SD, xtouch_paths_config, jsonDoc);

            request->send(200, "application/json", "{\"status\":\"ok\"}");

            delay(3000);
            ESP.restart();
            //
        });

    server.on(
        "/",
        HTTP_GET,
        [](AsyncWebServerRequest *request)
        {
            const char *html = R"rawliteral(<html lang="en"><head><meta charset="UTF-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><meta name="viewport" content="width=device-width,initial-scale=1"><title>XTouch Web Installer</title><style>:root{--color-black:black;--color-cod-gray:#101010;--color-white:white;--color-error:rgb(191, 95, 95);--color-primary-rgba:0,192,251;--color-primary:#666666;--color-secondary-rgba:234,182,56;--color-secondary:#eab638;--esp-tools-button-color:#cccccc;--esp-tools-button-text-color:#101010;--improv-primary-color:#484}esp-web-install-button :host{--mdc-theme-primary:#2aff00}ewt-install-dialog:host{--mdc-theme-primary:#2aff00}body,html{background-color:var(--color-cod-gray);padding:0;margin:0;overflow:hidden}.tiles{display:flex;flex-direction:column;justify-content:center;left:50%;position:fixed;top:50%;-webkit-transform:translateX(-50%) translateY(-50%) rotate(22.5deg)}.tiles__line{-webkit-animation:runner 20s linear infinite;display:flex;transform:translateX(25%)}.tiles__line:nth-child(2){-webkit-animation-duration:64s}.tiles__line:nth-child(3){-webkit-animation-duration:44s}@keyframes runner{to{-webkit-transform:translateX(-25%)}}.tiles__line-img{--tile-margin:3vw;background-position:50% 50%;background-size:cover;border-radius:50%;flex:none;height:30vh;margin:var(--tile-margin);width:30vh;background-color:var(--color-primary);opacity:.3}.tiles__line-img--large{border-radius:20vh;width:100vh;opacity:.1}.xhost__webusb{position:relative;background-color:#fff;padding:64px;display:table-cell;border-radius:16px;text-align:center;font-family:"Segoe UI",Tahoma,Geneva,Verdana,sans-serif;font-weight:700}.xhost__webusb svg{display:block;margin-top:32px}.xhost__webusb-container{display:flex;justify-content:center;align-items:center;height:100vh}</style></head><body><div class="tiles"><div class="tiles__line"><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div></div><div class="tiles__line"><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div><div class="tiles__line-img"></div><div class="tiles__line-img tiles__line-img--large"></div><div class="tiles__line-img"></div></div></div><div class="xhost__webusb-container"><div class="xhost__webusb">P1STouch</div></div></body></html>)rawliteral";
            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", html);
            request->send(response);
            //
        });

    server.begin();

    MDNS.addService("http", "tcp", 80);
    Serial.println("Webserver started");
    Serial.println("http://ps1touch.local");
    Serial.println(WiFi.localIP());
}

#endif