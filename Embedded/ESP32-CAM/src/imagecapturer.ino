#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include "base64.h"

//
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at
//            least 3MB APP space. Face Recognition is DISABLED for ESP32 and
//            ESP32-S2, because it takes up from 15 seconds to process single
//            frame. Face Detection is ENABLED if PSRAM is enabled as well

// ===================
// Select camera model
// ===================
// #define CAMERA_MODEL_WROVER_KIT // Has PSRAM
// #define CAMERA_MODEL_ESP_EYE // Has PSRAM
// #define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
// #define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
// #define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
// #define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
// #define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
// #define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
// #define CAMERA_MODEL_M5STACK_CAMS3_UNIT  // Has PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
// #define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
// #define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
//  ** Espressif Internal Boards **
// #define CAMERA_MODEL_ESP32_CAM_BOARD
// #define CAMERA_MODEL_ESP32S2_CAM_BOARD
// #define CAMERA_MODEL_ESP32S3_CAM_LCD
// #define CAMERA_MODEL_DFRobot_FireBeetle2_ESP32S3 // Has PSRAM
// #define CAMERA_MODEL_DFRobot_Romeo_ESP32S3 // Has PSRAM
#include "camera_pins.h"

#define flashLight 4

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "SWORD";
const char* password = "sword1998";

WiFiClientSecure client;

// String ServerName = "https://panel.xsarj.com/";
// String ServerPath = "pr/send_img";

String ServerName
  = "www.circuitdigest.cloud"; // Replace with your server domain
String ServerPath
  = "/readnumberplate"; // API endpoint path "/readqrcode" "/readnumberplate"
const int ServerPort = 443;

String apiKey = "KUHF438Ujdbp";

int count = 0; // Counter for image uploads

void startCameraServer();
void setupLedFlash(int pin);

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    pinMode(flashLight, OUTPUT);
    digitalWrite(flashLight, LOW);

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_UXGA;
    config.pixel_format = PIXFORMAT_JPEG; // for streaming
    // config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //                      for larger pre-allocated frame buffer.
    if (config.pixel_format == PIXFORMAT_JPEG)
        {
            if (psramFound())
                {
                    config.jpeg_quality = 10;
                    config.fb_count = 2;
                    config.grab_mode = CAMERA_GRAB_LATEST;
                }
            else
                {
                    // Limit the frame size when PSRAM is not available
                    config.frame_size = FRAMESIZE_SVGA;
                    config.fb_location = CAMERA_FB_IN_DRAM;
                }
        }
    else
        {
            // Best option for face detection/recognition
            config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
            config.fb_count = 2;
#endif
        }

#if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
#endif

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
        {
            Serial.printf("Camera init failed with error 0x%x", err);
            return;
        }

    sensor_t* s = esp_camera_sensor_get();
    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID)
        {
            s->set_vflip(s, 1);       // flip it back
            s->set_brightness(s, 1);  // up the brightness just a bit
            s->set_saturation(s, -2); // lower the saturation
        }
    // drop down frame size for higher initial frame rate
    if (config.pixel_format == PIXFORMAT_JPEG)
        {
            s->set_framesize(s, FRAMESIZE_QVGA);
        }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
    s->set_vflip(s, 1);
#endif

// Setup LED FLash if LED pin is defined in camera_pins.h
#if defined(LED_GPIO_NUM)
    setupLedFlash(LED_GPIO_NUM);
#endif

    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
    Serial.println("");
    Serial.println("WiFi connected");

    // startCameraServer();

    // Serial.print("Camera Ready! Use 'http://");
    // Serial.print(WiFi.localIP());
    // Serial.println("' to connect");
}

// Base64 encoding table
const char base64_enc_map[]
  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
// Custom base64 encoding function
String base64_encode(const unsigned char* data, size_t length)
{
    size_t encoded_length = 4 * ((length + 2) / 3);
    String encoded;
    encoded.reserve(encoded_length);

    for (size_t i = 0; i < length; i += 3)
        {
            uint32_t octet_a = i < length ? data[i] : 0;
            uint32_t octet_b = i + 1 < length ? data[i + 1] : 0;
            uint32_t octet_c = i + 2 < length ? data[i + 2] : 0;

            uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

            encoded += base64_enc_map[(triple >> 18) & 0x3F];
            encoded += base64_enc_map[(triple >> 12) & 0x3F];
            encoded += base64_enc_map[(triple >> 6) & 0x3F];
            encoded += base64_enc_map[triple & 0x3F];
        }

    if (length % 3 == 1)
        {
            encoded[encoded_length - 1] = '=';
            encoded[encoded_length - 2] = '=';
        }
    else if (length % 3 == 2)
        {
            encoded[encoded_length - 1] = '=';
        }

    return encoded;
}

// Function to extract a JSON string value by key
String extractJsonStringValue(const String& jsonString, const String& key)
{
    int keyIndex = jsonString.indexOf(key);
    if (keyIndex == -1)
        {
            return "";
        }

    int startIndex = jsonString.indexOf(':', keyIndex) + 2;
    int endIndex = jsonString.indexOf('"', startIndex);

    if (startIndex == -1 || endIndex == -1)
        {
            return "";
        }

    return jsonString.substring(startIndex, endIndex);
}

bool captured = false;

void loop()
{
    delay(5000);
    if (!captured)
        {
            capture();
            captured = true;
        }

    // Do nothing. Everything is done in another task by the web server
    delay(10000);
}

int capture()
{
    camera_fb_t* fb = nullptr;

    // digitalWrite(flashLight, HIGH);
    delay(100);
    fb = esp_camera_fb_get();
    delay(100);

    if (!fb)
        {
            Serial.println("Camera capture failed");
            return -1;
        }
    // Display success message
    Serial.print("Image Capture Success");
    delay(300);
    digitalWrite(flashLight, LOW);

    // Connect to server
    Serial.println("Connecting to server:" + ServerName);
    client.setInsecure(); // Skip certificate validation for simplicity

    if (client.connect(ServerName.c_str(), ServerPort))
        {
            Serial.println("Connection successful!");
            delay(300);

            // Increment count and prepare file name
            count++;
            Serial.println(count);
            String filename = apiKey + ".jpeg";

            // Prepare HTTP POST request
            String head = "--CircuitDigest\r\nContent-Disposition: form-data; "
                          "name=\"imageFile\"; filename=\""
                          + filename + "\"\r\nContent-Type: image/jpeg\r\n\r\n";
            String tail = "\r\n--CircuitDigest--\r\n";
            uint32_t imageLen = fb->len;
            uint32_t extraLen = head.length() + tail.length();
            uint32_t totalLen = imageLen + extraLen;

            client.println("POST " + ServerPath + " HTTP/1.1");
            client.println("Host: " + ServerName);
            client.println("Content-Length: " + String(totalLen));
            client.println(
              "Content-Type: multipart/form-data; boundary=CircuitDigest");
            client.println("Authorization:" + apiKey);
            client.println();
            client.print(head);

            // Send image data in chunks
            uint8_t* fbBuf = fb->buf;
            size_t fbLen = fb->len;
            for (size_t n = 0; n < fbLen; n += 1024)
                {
                    if (n + 1024 < fbLen)
                        {
                            client.write(fbBuf, 1024);
                            fbBuf += 1024;
                        }
                    else
                        {
                            size_t remainder = fbLen % 1024;
                            client.write(fbBuf, remainder);
                        }
                }

            client.print(tail);

            // Clean up
            esp_camera_fb_return(fb);

            // Wait for server response
            String response;
            long startTime = millis();
            while (client.connected() && millis() - startTime < 5000)
                { // Modifify the Waiting time as per the response time
                    if (client.available())
                        {
                            char c = client.read();
                            response += c;
                        }
                }

            // Extract and display NPR data from response
            String NPRData
              = extractJsonStringValue(response, "\"number_plate\"");
            String imageLink
              = extractJsonStringValue(response, "\"view_image\"");

            Serial.print("Response: ");
            Serial.println(response);
            client.stop();
            esp_camera_fb_return(fb);
            return 0;
        }

    else
        {
            Serial.println("Connection to server failed");
            esp_camera_fb_return(fb);
            return -2;
        }

    // if (WiFi.status() == WL_CONNECTED)
    //     {
    //         HTTPClient http;

    //         String serverPath = ServerName + ServerPath;

    //         http.begin(serverPath);
    //         http.addHeader("Content-Type", "application/json");

    //         JsonDocument doc; // Adjust size based on your needs
    //         doc["master_mac"] = WiFi.macAddress();

    //         // Base64 encode the image
    //         String base64Image = base64_encode(fb->buf, fb->len);
    //         doc["image"] = base64Image;

    //         String requestBody;
    //         serializeJson(doc, requestBody);

    //         int httpResponseCode = http.POST(requestBody);

    //         if (httpResponseCode > 0)
    //             {
    //                 String response = http.getString();
    //                 Serial.println("HTTP Response code: "
    //                                + String(httpResponseCode));
    //                 Serial.println(response);
    //             }
    //         else
    //             {
    //                 Serial.print("Error code: ");
    //                 Serial.println(httpResponseCode);
    //             }

    //         http.end();
    //     }
    // else
    //     {
    //         Serial.println("WiFi Disconnected");
    //     }

    // esp_camera_fb_return(fb);

    return 0;
}