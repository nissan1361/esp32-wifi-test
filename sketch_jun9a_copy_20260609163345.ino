#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  // Настройка WiFi в режиме ожидания (неактивного)
  WiFi.mode(WIFI_STA);
  Serial.println("Поиск доступных WiFi точек доступа...");
}

void loop() {
  int numberOfNetworks = WiFi.scanNetworks();
  
  if (numberOfNetworks == 0) {
    Serial.println("Нет доступных сетей");
  } else {
    Serial.print(numberOfNetworks);
    Serial.println(" обнаруженные сети:");
    
    for (int i = 0; i < numberOfNetworks; ++i) {
      // Вывод SSID каждой сети
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID(i));
      
      // Дополнительные параметры можно получить, используя функции WiFi.RSSI(), WiFi.BSSID() и т.д.
      // Например, RSSI (сигнальная сила) сети:
      Serial.print("Сила сигнала: ");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm");
      
      // MAC-адрес точки доступа:
      byte* b = WiFi.BSSID(i);
      char macStr[18];
      sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", b[0], b[1], b[2], b[3], b[4], b[5]);
      Serial.print("BSSID: ");
      Serial.println(macStr);
      
      // Канал сети:
      Serial.print("Канал: ");
      Serial.println(WiFi.channel(i));
      
      // Шифрование:
      Serial.print("Шифрование: ");
      String encryptionType;
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:
          encryptionType = "Открытый";
          break;
        case WIFI_AUTH_WEP:
          encryptionType = "WEP";
          break;
        case WIFI_AUTH_WPA_PSK:
          encryptionType = "WPA PSK";
          break;
        case WIFI_AUTH_WPA2_PSK:
          encryptionType = "WPA2 PSK";
          break;
        case WIFI_AUTH_WPA_WPA2_PSK:
          encryptionType = "WPA/WPA2 PSK";
          break;
        default:
          encryptionType = "Неизвестно";
      }
      Serial.println(encryptionType);
      
      // Разделитель между сетями
      Serial.println("-----------------------------");
    }
  }
  
  // Пауза перед следующим сканированием (необязательно)
  delay(10000);
}