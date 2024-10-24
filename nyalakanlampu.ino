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

void setup()
{
    Serial.begin(115200);

    pinMode(relay1, OUTPUT);

    // Menghubungkan ke WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        digitalWrite(relay1, LOW);
    }
    Serial.println("Connected to WiFi");

    // Menginisialisasi pin untuk lampu
    digitalWrite(relay1, LOW);

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
        if (text == "matikan lampu")
        {
            digitalWrite(relay1, HIGH);
            bot.sendMessage(chatId, "Lampu telah dimatikan!");
        }
        else if (text == "nyalakan lampu")
        {
            digitalWrite(relay1, LOW);
            bot.sendMessage(chatId, "Lampu telah dihidupkan!");
        }
    }

    delay(1000);
}
