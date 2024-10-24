#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
const char *WIFI_SSID = "Juan";
const char *WIFI_PASSWORD = "juan1234";

const char *BOT_TOKEN = "GUNAKAN_BOT_TOKEN_KALIAN_DI_GOODFATHER";
String chatId = "GUNAKAN_IDBOT_KALIAN";

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

const int relay1 = 25; // Pin yang digunakan untuk mengendalikan lampu
const int relay2 = 26; // Pin yang digunakan untuk mengendalikan Kipas

void setup()
{
    Serial.begin(115200);

    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);

    // Menghubungkan ke WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        digitalWrite(relay1, LOW);
        digitalWrite(relay2, LOW);
    }
    Serial.println("Connected to WiFi");

    // Menginisialisasi pin untuk lampu dan kipas

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    // Memulai koneksi ke Telegram
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Ini opsional, bergantung pada versi pustaka yang digunakan
}

void loop()
{
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    for (int i = 0; i < numNewMessages; i++)
    {
        chatId = bot.messages[i].chat_id; // Menyimpan chat_id dari pesan terbaru

        String text = bot.messages[i].text;
        Serial.println(text);
        if (text == "say")
        {
            bot.sendMessage(chatId, "ApaKabar!");
            delay(100);
            bot.sendMessage(chatId, "Apa yang bisa dibantu!");
        }
        else if (text == "matikan lampu")
        {
            digitalWrite(relay1, HIGH);
            bot.sendMessage(chatId, "Lampu telah dimatikan!");
        }
        else if (text == "nyalakan lampu")
        {
            digitalWrite(relay1, LOW);
            bot.sendMessage(chatId, "Lampu telah dihidupkan!");
        }
        else if (text == "nyalakan kipas")
        {
            digitalWrite(relay2, HIGH);
            bot.sendMessage(chatId, "Kipas telah dihidupkan!");
        }
        else if (text == "matikan kipas")
        {
            digitalWrite(relay2, LOW);
            bot.sendMessage(chatId, "Kipas telah dimatikan!");
        }
    }

    delay(1000);
}
